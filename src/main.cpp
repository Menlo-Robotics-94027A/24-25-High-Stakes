#include "main.h"
#include "auton/auton.hpp"
#include "devices/devices.hpp"
#include "driver/driver.hpp"
#include "ui/brain/ui.h"
#include "ui/controller/controller_ui.hpp"

void initialize() {
  // Initialize Brain UI
  ui_init();

  // Initialize the controller UI
  startControllerUITask();

  // Calibrate Sensors
  chassis.calibrate(true);

  // Reset pose
  chassis.setPose(0, 0, 0);
  pros::delay(50);
}

void disabled() {}
void competition_initialize() {}
void autonomous() { runAuton(); }
void opcontrol() { runDriverControl(); }