#include "belt.hpp"
#include "devices.hpp"

BeltState belt_state = BeltState::OFF;

int stuck_count = 0;
int trigger_count = 0;

#define TRIGGER_THRESHOLD 5
#define LAUNCH_DELAY 250
#define LAUNCH_SLEEP 1000

void startBeltTask() {
  pros::Task belt_task([=]() {
    while (true) {
      // Set movement direction
      if (belt_state == BeltState::INTAKE ||
          belt_state == BeltState::FORCE_INTAKE) {
        intake_belt.move(BELT_VOLTAGE);
      } else if (belt_state == BeltState::OUTTAKE ||
                 belt_state == BeltState::FORCE_OUTTAKE) {
        intake_belt.move(-BELT_VOLTAGE);
      } else {
        intake_belt.move(0);
      }

      // Check if intake is stuck - if not forced
      if (belt_state == BeltState::INTAKE || belt_state == BeltState::OUTTAKE) {
        if (intake_belt.get_actual_velocity() < 0.1) {
          stuck_count++;

          if (stuck_count > 5) {
            intake_belt.move(-BELT_VOLTAGE);
            pros::delay(500);
            stuck_count = 0;
          }
        } else {
          stuck_count = 0;
        }
      } else {
        stuck_count = 0;
      }

      // Check if intake detects wrong color ring
      if (belt_state == BeltState::INTAKE) {
        // Ensure ring is in front of the sensor
        if (optical_sensor.get_proximity() > 200) {
          std::cout << "Hue: " << optical_sensor.get_hue() << std::endl;
          // Check if color is red
          if ((optical_sensor.get_hue() > 0 && optical_sensor.get_hue() < 50) || (optical_sensor.get_hue() > 300)) {
            trigger_count++;
            if (trigger_count >= TRIGGER_THRESHOLD) {
              // Log trigger
            std::cout << "Triggered by: " << optical_sensor.get_hue() << std::endl;
            
            // Full speed until delay
            intake_belt.move(127);
            pros::delay(LAUNCH_DELAY);

            // Stop for launch
            intake_belt.move(0);
            pros::delay(LAUNCH_SLEEP);

            // // Resume normal speed
            // intake_belt.move(BELT_VOLTAGE);

            trigger_count = 0;

            }
          } else {
            trigger_count = 0;
          }
        } else {
          trigger_count = 0;
        }
      }
      pros::delay(10);
    }
  });
}

void setBeltState(BeltState state) { belt_state = state; }