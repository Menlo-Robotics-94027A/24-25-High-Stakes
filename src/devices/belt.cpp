#include "belt.hpp"

#include "devices.hpp"

// Current Belt State
BeltState belt_state = BeltState::BELT_OFF;
ColorSortState color_sort_state = ColorSortState::COLOR_SORT_NONE;
AntiLockState anti_lock_state = AntiLockState::ANTI_LOCK_OFF;

// Setters
void setBeltState(BeltState state)
{
  belt_state = state;
}
void setColorSortState(ColorSortState state)
{
  color_sort_state = state;
}
void setAntiLockState(AntiLockState state)
{
  anti_lock_state = state;
}

// Getters
BeltState getBeltState()
{
  return belt_state;
}
ColorSortState getColorSortState()
{
  return color_sort_state;
}
AntiLockState getAntiLockState()
{
  return anti_lock_state;
}

// Anti-Lock & Color Sort Thresholds
int belt_stuck_count = 0;
int color_sort_count = 0;

// Anti-Lock
void antiLock()
{
  // Check velocity (should be low if belt is stuck)
  if (intake_belt.get_actual_velocity() < ANTI_LOCK_VELOCITY)
  {
    belt_stuck_count++;

    // If stuck for too long, attempt fix
    if (belt_stuck_count > ANTI_LOCK_THRESHOLD)
    {
      // Notify user
      setAntiLockState(AntiLockState::ANTI_LOCK_STUCK);

      // Reverse belt
      intake_belt.move(-BELT_VOLTAGE);
      pros::delay(REVERSE_TIME);

      // Resume normal operation (make sure anti-lock wasn't toggled off)
      if (getAntiLockState() == AntiLockState::ANTI_LOCK_STUCK)
      {
        setAntiLockState(AntiLockState::ANTI_LOCK_ON);
      }

      // Reset stuck count
      belt_stuck_count = 0;
    }
  }
  else
  {
    belt_stuck_count = 0;
  }
}

// Color Sort
void colorSort()
{
  // Run only if intake is running
  if (getBeltState() == BeltState::BELT_INTAKE)
  {
    // Make sure a ring is detected
    if (optical_sensor.get_proximity() > 200)
    {
      // Check the color
      pros::c::optical_rgb_s_t rgb = optical_sensor.get_rgb();

      if ((getColorSortState() == ColorSortState::COLOR_SORT_RED && rgb.red > rgb.blue) ||
          (getColorSortState() == ColorSortState::COLOR_SORT_BLUE && rgb.blue > rgb.red))
      {
        color_sort_count++;
      }
      else
      {
        color_sort_count = 0;
      }

      // Check if threshold has been met
      if (color_sort_count > TRIGGER_THRESHOLD)
      {
        // Set speed to 100% for LAUNCH_DELAY ms
        intake_belt.move(127);
        pros::delay(LAUNCH_DELAY);

        // Stop belt for LAUNCH_SLEEP ms
        intake_belt.move(0);
        pros::delay(LAUNCH_SLEEP);

        // Resume normal operation
        color_sort_count = 0;
        intake_belt.move(BELT_VOLTAGE);
      }
    }
  }
}

// Belt Task
void startBeltTask()
{
  pros::Task belt_task([=]()
                       {
    // Main Loop
    while (true) {
      // 1. Configure movement direction
      if (getBeltState() == BeltState::BELT_INTAKE) {
        intake_belt.move(BELT_VOLTAGE);
      } else if (getBeltState() == BeltState::BELT_OUTTAKE) {
        intake_belt.move(-BELT_VOLTAGE);
      } else {
        intake_belt.move(0);
      }

      // 2. Check if intake is stuck - if enabled
      antiLock();

      // 3. Check if color sort is enabled
      if (getColorSortState() != ColorSortState::COLOR_SORT_NONE) {
        // Enable optical LED
        optical_sensor.set_led_pwm(100);

        // Run Color Sort
        colorSort();
      } else {
        // Turn off optical LED
        optical_sensor.set_led_pwm(0);
      }
    } });
}