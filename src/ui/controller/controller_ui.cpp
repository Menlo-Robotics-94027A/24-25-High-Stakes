#include "controller_ui.hpp"
#include "../../devices/devices.hpp"

void startControllerUITask() {
  pros::Task odom_task([=]() {
    while (true) {
      // Clear the controller screen
      controller.clear();

      // Write odometry data to controller screen
      controller.print(0, 0, "X: %f", chassis.getPose().x);
      controller.print(1, 0, "Y: %f", chassis.getPose().y);
      controller.print(2, 0, "Heading: %f", chassis.getPose().theta);

      // Delay to prevent spamming the controller
      pros::delay(250);
    }
  });
}