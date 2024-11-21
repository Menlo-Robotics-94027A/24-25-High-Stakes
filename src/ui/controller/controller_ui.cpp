#include "controller_ui.hpp"
#include "devices/devices.hpp"

void startControllerUITask() {
  pros::Task odom_task([=]() {
    while (true) {
      // Clear the controller screen
      controller.clear();
      pros::delay(50);

      // Write odometry data to controller screen
      controller.print(0, 0, "X: %f", chassis.getPose().x);
      pros::delay(50);

      controller.print(1, 0, "Y: %f", chassis.getPose().y);
      pros::delay(50);

      controller.print(2, 0, "Heading: %f", chassis.getPose().theta);

      // Delay to prevent spamming the controller
      pros::delay(250);
    }
  });
}