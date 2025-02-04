#include "auton.hpp"
#include "devices/belt.hpp"
#include "devices/devices.hpp"
#include "auton/match.hpp"
#include "auton/skills.hpp"
#include "auton/debug.hpp"

// Currently selected auton
Auton selected_auton = {"None", nullptr, AutonCategory::AUTON_DEBUG};

// List of all autons
Auton autons[] = {
    // Red
    {"Left Side (4-1+A)", blueLeft, AutonCategory::AUTON_RED},
    {"Right Side (3-2)", blueRight, AutonCategory::AUTON_RED},

    // Blue
    {"Left Side (3-2) ", redLeft, AutonCategory::AUTON_BLUE},
    {"Right Side (4-1+A)", redRight, AutonCategory::AUTON_BLUE},

    // Skills
    {"Skills", skillsAuton, AutonCategory::AUTON_SKILLS},

    // Debug
    {"Angular Tuning", angular_tuning, AutonCategory::AUTON_DEBUG},
    {"Lateral Tuning", lateral_tuning, AutonCategory::AUTON_DEBUG},
    {"Diamond", diamond, AutonCategory::AUTON_DEBUG},
};

Auton* getSelectedAuton()
{
    return &selected_auton;
}

Auton* getAutons(int* count)
{
    *count = sizeof(autons) / sizeof(Auton);;
    return autons;
}

void setAuton(Auton* auton)
{
    selected_auton = *auton;
}

void runAuton()
{
    // Check if auton is selected
    if (selected_auton.function == nullptr)
    {
        return;
    }

    // Configure auton
    if (selected_auton.category != AutonCategory::AUTON_DEBUG)
    {
        setAntiLockState(AntiLockState::ANTI_LOCK_ON);
        if (selected_auton.category == AutonCategory::AUTON_SKILLS || selected_auton.category == AutonCategory::AUTON_RED)
        {
            // Set color sort to red
            setColorSortState(ColorSortState::COLOR_SORT_BLUE);
        }
        else
        {
            // Set color sort to blue
            setColorSortState(ColorSortState::COLOR_SORT_RED);
        }
    }

    // Run the selected auton
    selected_auton.function();
}