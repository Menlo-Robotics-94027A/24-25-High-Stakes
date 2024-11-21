#include "belt.hpp"
#include "devices.hpp"

BeltState belt_state = BeltState::OFF;

int stuck_count = 0;

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
            intake_belt.move(0);
            pros::delay(500);
            stuck_count = 0;
          }
        } else {
          stuck_count = 0;
        }
      } else {
        stuck_count = 0;
      }

      pros::delay(50);
    }
  });
}

void setBeltState(BeltState state) { belt_state = state; }