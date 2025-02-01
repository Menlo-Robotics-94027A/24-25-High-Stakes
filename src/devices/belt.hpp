#ifndef BELT_HPP
#define BELT_HPP

// General Belt Config
#define BELT_VOLTAGE 100 // Determine speed, from 0-127 (90/127 seems to be optimal for high stake, 100/127 for mobile goals)

// Color Sorting Config
#define TRIGGER_THRESHOLD 5 // Number of consecutive positive readings from vision sensor to trigger rejection
#define LAUNCH_DISTANCE 290 // Time belt runs at 100% speed before launch
#define LAUNCH_SLEEP 300 // Time to stop belt after launch

// Auto-Hold Config
#define HOLD_THRESHOLD 5 // Number of consecutive ticks below threshold to trigger auto-hold
#define HOLD_REVERSE_TIME 260 // Time to reverse belt when auto-hold is triggered

// Anti-Lock Config
#define ANTI_LOCK_THRESHOLD 5 // Number of consecutive ticks below threshold to trigger anti-lock
#define ANTI_LOCK_VELOCITY 1 // Velocity threshold to trigger anti-lock
#define REVERSE_TIME 500 // Time to reverse belt when stuck

// Belt States
enum BeltState {
    BELT_OFF,
    BELT_INTAKE,
    BELT_OUTTAKE
};

enum ColorSortState {
    COLOR_SORT_NONE,
    COLOR_SORT_RED,
    COLOR_SORT_BLUE
};

enum AntiLockState {
    ANTI_LOCK_OFF,
    ANTI_LOCK_ON,
    ANTI_LOCK_STUCK
};

enum AutoHoldState {
    AUTO_HOLD_OFF,
    AUTO_HOLD_ANY,    
    AUTO_HOLD_ON
};

// Setters
void setBeltState(BeltState state);
void setColorSortState(ColorSortState state);
void setAntiLockState(AntiLockState state);
void setAutoHoldState(AutoHoldState state);

// Getters
BeltState getBeltState();
ColorSortState getColorSortState();
AntiLockState getAntiLockState();
AutoHoldState getAutoHoldState();

// Main Belt Task
void startBeltTask();

#endif