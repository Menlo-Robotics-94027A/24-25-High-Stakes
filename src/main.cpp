#include "devices.h"
#include "driver.h"
#include "ui/ui.h"

void initialize() {
  // Register LVGL Driver for SD Card
  registerDriver();

  // Initialize UI
  ui_init();

  // TODO: RE-ENABLE Calibrate Sensors
  chassis.calibrate(true);
  // Log position to screen (for debugging)
  }

void disabled() {}

void competition_initialize() {}
void autonomous() {}
void opcontrol() {
  // Arcade Style Control (speed + direction) // TODO: Choose preffered control
  // (tank, arcade, curvature)
  while (true) {
    // Get controller inputs
    int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
    int leftX = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
    // Move the robot (with steering priority)
    chassis.arcade(
        rightY, leftX, false,
        0.75); // High value = prioritize steering, low value = prioritize speed

    // Pneumatics
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
      grabber_piston.set_value(HIGH);
    }
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
      grabber_piston.set_value(LOW);
    }

    // Intake
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
      // Forwards
      intake_motors.move(127);
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
      // Backwards
      intake_motors.move(-127);
    } else {
      // Stop
      intake_motors.move(0);
    }

    // Sleep for 20ms (save resources, no need to update faster)
    pros::delay(20);
  }
}