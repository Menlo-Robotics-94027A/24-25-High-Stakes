#include "main.h"
#include "devices.h"
#include "driver.h"
#include "opcontrol.h"
#include "pros/motors.h" 
#include "pros/rtos.hpp"
#include "ui/ui.h"
#include "auton.h"

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
  chassis.setPose(0, 0, 180);

  // Reset grabber
  grabber_piston.set_value(LOW);
  pros::delay(50);

  // PID tuning
  chassis.moveToPoint(0, 28, 5000, {.forwards = false, .maxSpeed = 50}, false);

  // Grab pole
  grabber_piston.set_value(HIGH);
  pros::delay(50);

  // Move back a little (to settle pole)
  chassis.moveToPoint(0, 2, 5000, {.maxSpeed = 50}, false);

  // Run conveyor (& start rollers for later)
  intake_belt.move(127);
  pros::delay(50);
  intake_rollers.move(127);

  // Wait 2s for conveyor to move
  pros::delay(2000);

  // Release pole
  grabber_piston.set_value(LOW);
  pros::delay(50);

  // Grab pole
  grabber_piston.set_value(HIGH);

  // Move to the ring
  if (auton_selected) {
  chassis.turnToHeading(90, 5000, {}, false);
  chassis.moveToPoint(20, 28, 5000, {.maxSpeed = 50}, false);
  } else {
  chassis.turnToHeading(270, 5000, {}, false);
  chassis.moveToPoint(-20, 28, 5000, {.maxSpeed = 50}, false);
  }

  // Delay 250ms to not pick up blue ring
  pros::delay(200);
  intake_rollers.move(-127);

  // Delay 1500ms to ensure ring is on pole
  pros::delay(1500);

  // Disable intake & Drop pole
  pros::delay(50);
  intake_belt.move(0);
  pros::delay(50);
  grabber_piston.set_value(LOW);
  pros::delay(50);
  intake_rollers.move(0);

  // Move to center
  if (auton_selected) {
  chassis.turnToHeading(215, 500);
  chassis.moveToPoint(-20, 28, 5000, {.maxSpeed = 50}, false);
  } else {
  chassis.turnToHeading(145, 500);
  chassis.moveToPoint(20, 28, 5000, {.maxSpeed = 50}, false);
  }
}
void opcontrol() { runOpcontrol(); }