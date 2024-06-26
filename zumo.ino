#include <Pixy2.h>
#include <PIDLoop.h>
#include <ZumoMotors.h>
#include <ZumoBuzzer.h>
#include <avr/sleep.h>

#define ZUMO_FAST        400              // -400 < v < 400 250,100
#define ZUMO_SLOW        200               // 250 too high 200 okay
#define X_CENTER         (pixy.frameWidth/2)

Pixy2 pixy;
ZumoMotors motors;

PIDLoop headingLoop(10000, 1000, 5000, false); // 10k 5k .5 ok (15k bad turns)

void setup() {
//  set_sleep_mode(SLEEP_MODE_PWR_DOWN);

  Serial.begin(115200);
  motors.setLeftSpeed(0);
  motors.setRightSpeed(0);

  pixy.init();
  pixy.setLamp(1, 1);                    // turn on upper & lower lamps for max exposure
  pixy.setServos(500, 1000);             // look straight and down
  
  pixy.changeProg("line");            // change to the line_tracking program. changeProg can use partial strings,
                                      // e.g. change to LTP by calling changeProg("line") instead of changeProg("line_tracking")
}


void loop() {
  int left, right, UTURN; UTURN = 0;
  int8_t res;
  int32_t error;
  char buf[96];

  res = pixy.line.getMainFeatures();   // get latest data from Pixy: main vector, intersections and barcodes

  
  if (res<=0) {                          // if error or nothing detected, stop motors
    
         //if (res<=0) { pixy.setServos(380, 800); }  // look right
    //else if (res<=0) { pixy.setServos(620, 900); }  // look left

    if (UTURN == 0) {
      motors.setLeftSpeed(-300);
      motors.setRightSpeed(300);
      UTURN++;
    }
 
  }

 // if vector found...
  if (res&LINE_VECTOR) {
    // calculate heading error w/ respect to m_x1 (the arrowhead of vector)
    error = (int32_t)pixy.line.vectors->m_x1 - (int32_t)X_CENTER;
    
    headingLoop.update(error);          // perform PID calcs on heading error
    left = headingLoop.m_command;       // separate heading into left & right wheel velocities
    right -= headingLoop.m_command;

    if (pixy.line.vectors->m_y0 > pixy.line.vectors->m_y1) {            // if vector is heading away from us (arrow pointing up)

      if (pixy.line.vectors->m_flags&LINE_FLAG_INTERSECTION_PRESENT) {   // ... but slow down if intersection is present, so we don't miss it.
        left += ZUMO_SLOW;
        right += ZUMO_SLOW;
      }
      else {                            // else, pedal to the metal! 
        pixy.setServos(500, 1000);
        left += ZUMO_FAST;
        right += ZUMO_FAST;
      }
    }
    else {                              // if vector is pointing down-ish, UNO REVERSE 
      pixy.line.reverseVector();
      left += ZUMO_SLOW;
      right += ZUMO_SLOW;  
    }
    motors.setLeftSpeed(left);
    motors.setRightSpeed(right);
  }

}
