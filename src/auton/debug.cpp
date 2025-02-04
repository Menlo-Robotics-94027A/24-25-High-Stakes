#include "match.hpp"
#include "devices/belt.hpp"
#include "devices/devices.hpp"

void angular_tuning() {
    // set position to x:0, y:0, heading:0
    chassis.setPose(0, 0, 0);
    // turn to face heading 90 with a very long timeout
    chassis.turnToHeading(90, 100000);
}

void lateral_tuning() {
    // set position to x:0, y:0, heading:0
    chassis.setPose(0, 0, 0);
    // move 48" forwards
    chassis.moveToPoint(0, 48, 10000);
}

void diamond() {
  // Zero
  chassis.setPose(0, 0, 0);

  // Move to first corner (0, 96)
  chassis.moveToPose(-48, 48, -90, 10000);
  
  // Wait for 3 seconds
  pros::delay(3000);

  // Move to second corner (-96, 96)
  chassis.moveToPose(-96, 0, -180, 10000);

  // Wait for 3 seconds
  pros::delay(3000);

  // Move to third corner (-96, 0)
  chassis.moveToPose(-48, -48, -270, 10000);

  // Wait for 3 seconds
  pros::delay(3000);

  // Move to fourth corner (0, 0)
  chassis.moveToPose(0, 0, 0, 10000, {.maxSpeed = 50});
  chassis.turnToHeading(0, 10000);
}
