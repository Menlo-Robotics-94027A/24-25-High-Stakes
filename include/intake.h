#include "devices.h"

#define BELT_OFF 0
#define BELT_FORWARDS 1
#define BELT_BACKWARDS 2
#define BELT_FORWARDS_BYPASS 3
#define BELT_BACKWARDS_BYPASS 4

// 0 = Off
// 1 = On - Forwards
// 2 = On - Backwards
int belt_enabled = 0;
int belt_failure_count = 0;

void start_intake_task() {
  pros::Task odom_task([=]() {
    while (true) {
      // If the intake is enabled
      if (belt_enabled == 1) {
        // Log current
        printf("Current: %d\n", intake_belt.get_current_draw());

        intake_belt.move(90);

        // Check if intake is stuck
        if (intake_belt.get_actual_velocity() < 0.1) {
          belt_failure_count++;

          if (belt_failure_count > 5) {
            intake_belt.move(-90);
            pros::delay(500);
            belt_failure_count = 0;
          }
        } else {
            belt_failure_count = 0;
        }

        intake_belt.move(90);
      } else if (belt_enabled == 2) {
        intake_belt.move(-90);
      } else if (belt_enabled == 3) {
        intake_belt.move(90);
      } else if (belt_enabled == 4) {
        intake_belt.move(-90);
      } else {
        intake_belt.move(0);
      }

      pros::delay(50);
    }
  });
}