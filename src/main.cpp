#include "main.h"
#include "auton.h"
#include "devices.h"
#include "driver.h"
#include "opcontrol.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "ui/ui.h"

void initialize() {
  // Register LVGL Driver for SD Card
  registerDriver();

  // Initialize UI
  ui_init();

  // Calibrate Sensors
  chassis.calibrate(true);

  // Reset pose
  pros::delay(20);
  chassis.setPose(0, 0, 0);

  // Register task to log odometry to controller screen
  pros::Task odom_task([=]() {
    while (true) {
      controller.clear();
      pros::delay(50);

      // Write odometry data to controller screen
      controller.print(0, 0, "X: %f", chassis.getPose().x);
      pros::delay(50);
      controller.print(1, 0, "Y: %f", chassis.getPose().y);
      pros::delay(50);
      controller.print(2, 0, "Theta: %f", chassis.getPose().theta);
      pros::delay(200);
    }
  });
}

void disabled() {}

void competition_initialize() {}
void autonomous() {
  runAutonomous();
}
void opcontrol() { runOpcontrol(); }