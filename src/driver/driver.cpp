#include "driver.hpp"
#include "devices/devices.hpp"
#include "devices/belt.hpp"

void runDriverControl() {
  while (true) {
    // Get controller inputs
    int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int leftX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    // Move the robot (with slight steering priority)
    chassis.arcade(
        rightY, leftX, false,
        0.75); // High value = prioritize steering, low value = prioritize speed

    // Pneumatics - Grabber Piston
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
      grabber_piston.set_value(HIGH);
    }
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
      grabber_piston.set_value(LOW);
    }

    // Pneumatics - Elevation Piston
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
      elevation_piston.set_value(HIGH);
    }
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
      elevation_piston.set_value(LOW);
    }

    // Pneumatics - Arm
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
      arm.set_value(HIGH);
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
      arm.set_value(LOW);
    }

    // Intake Rollers
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
      // Forwards
      intake_rollers.move(127);
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
      // Backwards
      intake_rollers.move(-127);
    } else {
      // Stop
      intake_rollers.move(0);
    }

    // Intake Belt
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
      // Forwards
      setBeltState(BeltState::FORCE_INTAKE);
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
      // Backwards
      setBeltState(BeltState::FORCE_OUTTAKE);
    } else {
      // Stop
      setBeltState(BeltState::OFF);
    }

    // Sleep for 20ms (save resources, no need to update faster)
    pros::delay(20);
  }
}