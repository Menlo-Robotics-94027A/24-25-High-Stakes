#include "devices.h"
#include "skills.h"

int auton_selected = 0;

void new_auton() {
  // Reset, start rollers
  chassis.setPose(0, 0, 0);
  grabber_piston.set_value(LOW);
  pros::delay(50);

  // Move to first stake
  chassis.moveToPoint(0, 16, 2000,
                      {.forwards = true, .maxSpeed = 50, .earlyExitRange = 0},
                      false);
  
  // Rotate 90
  chassis.turnToHeading(90, 2000, {.earlyExitRange = 0}, false);

  // Reset pose
  chassis.setPose(0, 0, 0);
  pros::delay(50);

  // Move backwards 3 inches
  chassis.moveToPoint(0, -10, 1000,
                      {.forwards = false, .maxSpeed = 15, .earlyExitRange = 0},
                      false);
  
  // Move forward 1.7 inches
  chassis.moveToPoint(0, 1.7, 1000,
                      {.forwards = true, .maxSpeed = 50, .earlyExitRange = 0},
                      false);
  
  // Score preload
  intake_belt.move(90);
}

void runAutonomous() {
  if (auton_selected == 2) {
    runSkills();
    return;
  }

  // Reset Pose
  chassis.setPose(0, 0, 180);
  grabber_piston.set_value(LOW);
  pros::delay(50);

  // Move towards first stake
  chassis.moveToPoint(0, 31, 5000,
                      {.forwards = false, .maxSpeed = 50, .earlyExitRange = 27},
                      false);

  // Begin scoring preload
  grabber_piston.set_value(HIGH);
  pros::delay(250);
  intake_belt.move(90);

  // Wait 1000ms for preload to score
  pros::delay(1000);

  // Rotate robot towards 2nd ring (side-dependent)
  if (auton_selected) {
    chassis.turnToHeading(90, 2000, {.earlyExitRange = 250}, false);
  } else {
    chassis.turnToHeading(270, 2000, {.earlyExitRange = 250}, false);
  }

  // Reset pose (to use relative movement)
  chassis.setPose(0, 0, 0);

  // Enable rollers
  intake_rollers.move(127);

  // Move forward towards 2nd ring
  chassis.moveToPoint(0, 25, 5000,
                      {.forwards = true, .maxSpeed = 75, .earlyExitRange = 25},
                      false);

  // Wait 1500ms for ring to be collected and scored
  pros::delay(1500);

  // Turn towards ladder
  if (auton_selected) {
    chassis.turnToHeading(30, 2000, {.earlyExitRange = 180}, false);
  } else {
    chassis.turnToHeading(-30, 2000, {.earlyExitRange = 180}, false);
  }

  // Reset pose (to use relative movement)
  chassis.setPose(0, 0, 0);

  // Disable all intake stages to prevent damage (when ramming into ladder)
  intake_rollers.move(0);
  intake_belt.move(0);

  // Ram into ladder
  chassis.moveToPoint(0, -40, 5000,
                      {.forwards = false, .maxSpeed = 75, .earlyExitRange = 25},
                      false);
}