#include "skills.h"
#include "intake.h"

void runSkills() {
start_intake_task();
intake_rollers.move(127);

    // Reset pose
  chassis.setPose(0, 0, 0);

  // Start running belt (and wait 1s) to score preload onto alliance stake
  belt_enabled = BELT_FORWARDS;
  pros::delay(1000);

  // Move to first turning point and turn 90 degrees left (87.5 after correction)
  chassis.moveToPoint(0, 14.5, 5000, {.maxSpeed = 75, .earlyExitRange = 10},
                      false);
  chassis.turnToHeading(-92.5, 1500, {.maxSpeed = 50, .earlyExitRange = 90,}, false);

  // Reset heading (makes programming the robot easier)
  chassis.setPose(0, 0, 180);
  pros::delay(50);

  // Move forward 15 inches and grab the right side stake
  chassis.moveToPoint(0, 22, 5000, {.forwards = false, .maxSpeed = 50, .earlyExitRange = 22},
                      false);
  grabber_piston.set_value(HIGH);
  pros::delay(250);

  // Turn towards first ring
  chassis.turnToHeading(270, 1000, {.maxSpeed = 50, .earlyExitRange = 90}, false);

  // Reset heading & enable rollers in preparation for ring-collection
  chassis.setPose(0, 0, 0);
  pros::delay(50);

  // Move forward 10 inches to grab first ring
  chassis.moveToPoint(0, 25, 5000, {.maxSpeed = 75, .earlyExitRange = 25},
                      false);

  // Turn 35 (step 1 of 2nd ring) and move forward
  chassis.turnToHeading(45, 1000, {.maxSpeed = 50, .earlyExitRange = 52.5}, false);
  chassis.setPose(0, 0, 0);
  pros::delay(50);
  chassis.moveToPoint(0, 25, 5000, {.maxSpeed = 75, .earlyExitRange = 37},
                      false);
  
  // Turn 55 degrees more
  chassis.turnToHeading(57.5, 1000, {.maxSpeed = 50, .earlyExitRange = 90}, false);
  chassis.setPose(0, 0, 0);
  pros::delay(50);
  chassis.moveToPoint(0, 12, 5000, {.maxSpeed = 75, .earlyExitRange = 20},
                      false);

  // Move backwards 10 inches and turn towards line of 3 rings
  chassis.setPose(0, 0, 0);
  pros::delay(50);
  chassis.moveToPoint(0, -5, 5000, {.forwards = false, .maxSpeed = 50, .earlyExitRange = 30},
                      false);
  chassis.turnToHeading(90, 1250, {.maxSpeed = 50, .earlyExitRange = 180}, false);

  // Reset heading 
  chassis.setPose(0, 0, 0);
  pros::delay(50);

  // Go forward (slowly) and collect 3 rings
  chassis.moveToPoint(0, 80, 4250, {.maxSpeed = 35, .earlyExitRange = 100},
                      false);
  
  // Reset pose at wall (to align the robot)
  chassis.setPose(0, 0, 0);
  pros::delay(50);

  // Move back 10 inches & turn towards final right-side ring
  chassis.moveToPoint(0, -20, 5000, {.forwards = false, .maxSpeed = 75},
                      false);
  chassis.turnToHeading(-50, 1000, {.maxSpeed = 50, .earlyExitRange = 90}, false);

  // Reset pose
  chassis.setPose(0, 0, 0);
  pros::delay(50);

  // Collect ring & move back slowly
  chassis.moveToPoint(0, 10, 5000, {.maxSpeed = 75, .earlyExitRange = 10},
                      false);
        pros::delay(500);
  chassis.moveToPoint(0, 5, 1000, {.forwards = false, .maxSpeed = 25, .earlyExitRange = 5},
                      false);
  
  // Rotate to position portable stake towards corner
  chassis.turnToHeading(190, 2000, {.maxSpeed = 50, .earlyExitRange = 135}, false);

  // Reset pose
  chassis.setPose(0, 0, 0);

  // Move back to position stake on top of corner
  chassis.moveToPoint(0, -22.5, 5000, {.forwards = false, .maxSpeed = 75},
                      false);

  // Reverse intake (to prevent jamming) and drop stake
  belt_enabled = BELT_BACKWARDS;
  grabber_piston.set_value(LOW);
  pros::delay(250);

  // Align robot for next stake
  chassis.moveToPoint(0, -15, 5000, {.maxSpeed = 75, .earlyExitRange = 10},
                      false);
  belt_enabled = BELT_FORWARDS;
  chassis.turnToHeading(125, 2000, {.maxSpeed = 50, .earlyExitRange = 90}, false);

  // Reset pose
  chassis.setPose(0, 0, 0);
  pros::delay(50);

  // Move towards stake and grab stake (slowly)
  chassis.moveToPoint(0, -64.5, 5000, {.forwards = false, .maxSpeed = 75, .earlyExitRange = 5});
  chassis.moveToPoint(0, -74.5, 5000, {.forwards = false, .maxSpeed = 25, .earlyExitRange = 0},
                      false);
  grabber_piston.set_value(HIGH);
  pros::delay(100);

  // Turn 90 degrees and collect first ring on left side
  chassis.turnToHeading(-90, 1000, {.maxSpeed = 50, .earlyExitRange = 90}, false);
  chassis.setPose(0, 0, 0);
  pros::delay(50);
  chassis.moveToPoint(0, 25, 5000, {.maxSpeed = 75, .earlyExitRange = 20},
                      false);
  
  // Turn 45 (step 1 of 2nd ring) and move forward
  chassis.turnToHeading(-47.5, 1000, {.maxSpeed = 50, .earlyExitRange = 52.5}, false);
  chassis.setPose(0, 0, 0);
  pros::delay(50);
  chassis.moveToPoint(0, 27.5, 5000, {.maxSpeed = 75, .earlyExitRange = 37},
                      false);
  
  // Turn 45 degrees more
  chassis.turnToHeading(-47.5, 1000, {.maxSpeed = 50, .earlyExitRange = 90}, false);
  chassis.setPose(0, 0, 0);
  pros::delay(50);
  chassis.moveToPoint(0, 15, 5000, {.maxSpeed = 75, .earlyExitRange = 20},
                      false);

                      // Backup and turn 90 to collect 3 rings
    chassis.moveToPoint(0, 5, 5000, {.forwards = false, .maxSpeed = 75, .earlyExitRange = 10},
                        false);
    chassis.turnToHeading(-90, 1000, {.maxSpeed = 50, .earlyExitRange = 90}, false);
    chassis.setPose(0, 0, 0);
    pros::delay(50);

      // Go forward (slowly) and collect 3 rings
  chassis.moveToPoint(0, 80, 4250, {.maxSpeed = 35, .earlyExitRange = 100},
                      false);


// Reset pose at wall (to align the robot)
  chassis.setPose(0, 0, 0);
  pros::delay(50);

  // Move back 10 inches & turn towards final right-side ring
  chassis.moveToPoint(0, -15, 5000, {.forwards = false, .maxSpeed = 75},
                      false);
  chassis.turnToHeading(85, 1000, {.maxSpeed = 50, .earlyExitRange = 90}, false);

  // Reset pose
  chassis.setPose(0, 0, 0);
  pros::delay(50);

  // Collect ring & move back slowly
  chassis.moveToPoint(0, 12.5, 5000, {.maxSpeed = 75, .earlyExitRange = 10},
                      false);
        pros::delay(500);
chassis.moveToPoint(0, 5, 5000, {.forwards = false, .maxSpeed = 25, .earlyExitRange = 5},
                      false);
  
  // Rotate to position portable stake towards corner
  chassis.turnToHeading(120, 2000, {.maxSpeed = 50, .earlyExitRange = 135}, false);

  // Reset pose
  chassis.setPose(0, 0, 0);

  // Move back to position stake on top of corner
  chassis.moveToPoint(0, -20, 5000, {.forwards = false, .maxSpeed = 75},
                      false);

  // Reverse intake (to prevent jamming) and drop stake
  belt_enabled = BELT_BACKWARDS;
  grabber_piston.set_value(LOW);
  pros::delay(250);

  // Move forward to no longer contact stake
  chassis.setPose(0, 0, 0);
    pros::delay(50);
    chassis.moveToPoint(0, 10, 5000, {.maxSpeed = 75, .earlyExitRange = 10},
                        false);
}