#include "main.h"
#include "auton/auton.hpp"
#include "devices/belt.hpp"
#include "devices/devices.hpp"
#include "driver/driver.hpp"
#include "ui/brain/brain_ui.hpp"
#include "ui/controller/controller_ui.hpp"

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
  //runAuton();
  runDriverControl(); 
  }

