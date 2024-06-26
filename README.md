# Line Tracking Robot

**Task**

● Program a robot to follow the line.

● The path of the robot must cover the entire track.

● Line MUST BE between robot tracks at ALL times.

● Start and end behind the start line.

● Bonus points if the robot can automatically restart another run.

● Judged based on performance in speed, smoothness and robustness.


### The Robot Platform

Actuators
* Zumo Shield
* Pan-Tilt Servos

Sensor
* Pixy2 Camera

Microprocessor
* Arduino Uno R3

## Observations

# Observations

| **P**  | **I**  | **D**  | **Observation**                         |
|--------|--------|--------|-----------------------------------------|
| 5000   | 10000  | 1000   | very tight turns                        |
| 5000   | 1000   | 10000  | stops at 1st and 2nd turn (likely due to reverse vector) |
| 5000   | 0      | 0      | stops at 1st turn                       |
| 5000   | 0      | 1000   | stops at 3rd turn                       |
| 5000   | 0      | 10     | stops at 1st turn                       |
| 1000   | 0      | 0      | stops at 1st turn                       |
| 10000  | 0      | 0      | stops at 2nd turn (when robot is put on the outer edge) |
| 5000   | 10     | 0      | stops at 2nd turn, wobbly               |
| 5000   | 1000   | 0      | wobbly                                  |
| 5000   | 1000   | 1000   | it turns too early, still wobbly        |
| 5000   | 10     | 1000   | -                                       |
| 5000   | 500    | 1000   | PIDLoop headingLoop(5000, 500, 1000, false) |
| 5000   | 50     | 1000   | PIDLoop headingLoop(5000, 50, 1000, false) |



## Final Version
https://github.com/yeoxiongyun/zumoline/assets/84406436/cc6931ea-3cf6-41cc-90f0-8584d673d2b1
