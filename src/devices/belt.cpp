#include "belt.hpp"

#include "devices.hpp"

// Current Belt State
BeltState belt_state = BeltState::BELT_OFF;
ColorSortState color_sort_state = ColorSortState::COLOR_SORT_NONE;
AntiLockState anti_lock_state = AntiLockState::ANTI_LOCK_OFF;
AutoHoldState auto_hold_state = AutoHoldState::AUTO_HOLD_OFF;

// Setters
void setBeltState(BeltState state)
{
  belt_state = state;
}
void setColorSortState(ColorSortState state)
{
  color_sort_state = state;
  printf("Color Sort State: %d\n", state);
}
void setAntiLockState(AntiLockState state)
{
  anti_lock_state = state;
}
void setAutoHoldState(AutoHoldState state)
{
  auto_hold_state = state;
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
AutoHoldState getAutoHoldState()
{
  return auto_hold_state;
}

// Anti-Lock & Color Sort Thresholds
int belt_stuck_count = 0;
int color_sort_count = 0;
int belt_hold_count = 0;

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
        intake_belt.tare_position();
        while (intake_belt.get_position() < LAUNCH_DISTANCE)
        {
          pros::delay(5);
        }

        // Stop belt for LAUNCH_SLEEP ms
        intake_belt.move(0);
        pros::delay(LAUNCH_SLEEP);

        // Resume normal operation
        color_sort_count = 0;
        intake_belt.move(BELT_VOLTAGE);
      }
    } else {
      color_sort_count = 0;
    }
  } else {
    color_sort_count = 0;
  }
}

// Auto-Hold
void autoHold()
{
  // Check if belt is running
  if (getBeltState() == BeltState::BELT_INTAKE)
  {
    // Check if a ring is detected (same color as color sort, or if none, either color)
    if (optical_sensor.get_proximity() > 200)
    {
      // Check the color
      pros::c::optical_rgb_s_t rgb = optical_sensor.get_rgb();

      // Log rgb blue and red
      printf("Red: %d, Blue: %d\n", rgb.red, rgb.blue);

      if ((getColorSortState() == ColorSortState::COLOR_SORT_BLUE && rgb.red > rgb.blue) ||
          (getColorSortState() == ColorSortState::COLOR_SORT_RED && rgb.blue > rgb.red) ||
          getColorSortState() == ColorSortState::COLOR_SORT_NONE || getAutoHoldState() == AutoHoldState::AUTO_HOLD_ANY)
      {
        belt_hold_count++;
      }
      else
      {
        belt_hold_count = 0;
      }

      // Check if threshold has been met
      if (belt_hold_count > HOLD_THRESHOLD)
      {
        // Reverse belt to ensure ring is fully in
        intake_belt.move(-BELT_VOLTAGE);
        pros::delay(HOLD_REVERSE_TIME);

        // Stop belt
        intake_belt.move(0);

        // Update Belt State
        setAutoHoldState(AutoHoldState::AUTO_HOLD_OFF);
        setBeltState(BeltState::BELT_OFF);

        // Reset hold count
        belt_hold_count = 0;
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
      // 0. Turn on LED
      optical_sensor.set_led_pwm(100);
      
      // 1. Configure movement direction
      if (getBeltState() == BeltState::BELT_INTAKE) {
        intake_belt.move(BELT_VOLTAGE);
      } else if (getBeltState() == BeltState::BELT_OUTTAKE) {
        intake_belt.move(-BELT_VOLTAGE);
      } else {
        intake_belt.move(0);
      }

      // 2. Check auto hold
      if (getAutoHoldState() != AutoHoldState::AUTO_HOLD_OFF) {
        autoHold();
      }

      // 3. Check if intake is stuck - if enabled
      if (getBeltState() == BeltState::BELT_INTAKE && getAntiLockState() == AntiLockState::ANTI_LOCK_ON) {
        antiLock();
      } else {
        belt_stuck_count = 0;
      }

      // 4. Check if color sort is enabled
      if (getColorSortState() != ColorSortState::COLOR_SORT_NONE) {
        // Run Color Sort
        colorSort();
      }

      // Sleep for 10ms
      pros::delay(10);
    } });
}