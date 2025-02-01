#include "main.h"
#include "auton/auton.hpp"
#include "devices/belt.hpp"
#include "devices/devices.hpp"
#include "driver/driver.hpp"
#include "ui/brain/brain_ui.hpp"
#include "ui/controller/controller_ui.hpp"

ASSET(path_jerryio_txt);

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


void initialize() {
  // Initialize Brain UI 
  startBrainUI();

  // Initialize the controller UI
  startControllerUITask();

  // Start belt task
  startBeltTask();

  // Calibrate Sensors
  chassis.calibrate(true);
  pros::delay(1500);
  optical_sensor.set_integration_time(20.0);

  // Reset pose
  chassis.setPose(0, 0, 0);
}

void disabled() {}
void competition_initialize() {}
void autonomous() { runAuton(); }
void opcontrol() { 
  chassis.setPose(0, 0, 0);
  // chassis.follow(path_jerryio_txt, 15, 20000);
  // angular_tuning();
  // lateral_tuning();
  // runSkillsAuton();
  // diamond();
  runAuton();
  // runMatchAuton(MATCH_LEFT);
  // runMatchAutonWP(MATCH_LEFT_WP);
  // setBeltState(BeltState::BELT_INTAKE);
  // grabber_piston.set_value(HIGH);
  // setColorSortState(ColorSortState::COLOR_SORT_RED);
  // runDriverControl(); 
    // setColorSortState(ColorSortState::COLOR_SORT_RED);
    // setAutoHoldState(AutoHoldState::AUTO_HOLD_ANY);
    // setBeltState(BeltState::BELT_INTAKE);
    // pros::delay(5000);
    // setBeltState(BeltState::BELT_INTAKE);
  }

