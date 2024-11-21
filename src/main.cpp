#include "main.h"
#include "auton/auton.hpp"
#include "auton/match.hpp"
#include "auton/skills.hpp"
#include "devices/belt.hpp"
#include "devices/devices.hpp"
#include "driver/driver.hpp"
#include "ui/brain/ui.h"
#include "ui/controller/controller_ui.hpp"

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


void initialize() {
  // Initialize Brain UI 
  ui_init();

  // Initialize the controller UI
  startControllerUITask();

  // Start belt task
  startBeltTask();

  // Calibrate Sensors
  chassis.calibrate(true);

  // Reset pose
  chassis.setPose(0, 0, 0);
  pros::delay(50);
}

void disabled() {}
void competition_initialize() {}
void autonomous() { runAuton(); }
void opcontrol() { 
  chassis.setPose(0, 0, 0);
  // angular_tuning();
  // lateral_tuning();
  // runSkillsAuton();
  runMatchAuton(MATCH_LEFT);
  // runDriverControl(); 
  }

