#include "skills.hpp"
#include "devices/belt.hpp"
#include "devices/devices.hpp"

void skillsAuton()
{
    // Set starting position
    chassis.setPose(-60, 0.5, 90); // 0.5 inch offset for the belt not being perfectly aligned

    // Score match load
    setBeltState(BeltState::BELT_INTAKE);
    pros::delay(1000);
    setBeltState(BeltState::BELT_OFF);

    // Move to mobile goal #1
    chassis.moveToPoint(-45, 0.5, 10000);
    chassis.turnToPoint(-48, -24, 10000, {.forwards = false}, false);
    chassis.moveToPoint(-48, -24, 10000, {.forwards = false, .maxSpeed = 50});

    // Grab mobile goal #1
    chassis.waitUntilDone();
    grabber_piston.set_value(HIGH);
    pros::delay(250);

    // Enable belt and rollers
    setBeltState(BeltState::BELT_INTAKE);
    intake_rollers.move(127);

    // Move towards close right-side ring #1
    chassis.moveToPoint(-24, -24, 10000);

    // Move to close right-side ring #2
    chassis.moveToPose(0, -60, 180, 10000);

    // Line up for close right-side rings #3, #4, #5
    chassis.moveToPoint(0, -45, 10000, {.forwards = false});

    // Turn towards close right-side rings #3, #4, #5
    chassis.turnToPoint(-24, -45, 10000);

    // Collect close right-side rings #3, #4, #5
    chassis.moveToPoint(-36, -45, 10000, {.maxSpeed = 70, .minSpeed = 70});
    chassis.moveToPoint(-60, -45, 10000, {.maxSpeed = 30});

    // Collect close right-side ring #6
    chassis.turnToPoint(-48, -60, 10000, {.maxSpeed = 75});
    chassis.moveToPoint(-48, -60, 10000);

    // Drop mobile goal #1
    chassis.turnToPoint(-72, -72, 10000, {.forwards = false});
    chassis.moveToPoint(-56, -56, 10000, {.forwards = false});
    chassis.waitUntilDone();
    grabber_piston.set_value(LOW);

    // Move forward to grab mobile goal #2
    chassis.moveToPoint(-48, -48, 10000);
    chassis.turnToPoint(-48, 24, 10000, {.forwards = false});
    chassis.moveToPoint(-48, 24, 10000, {.forwards = false, .maxSpeed = 50});

    // Grab mobile goal #2
    chassis.waitUntilDone();
    grabber_piston.set_value(HIGH);
    pros::delay(250);

    // Move towards close left-side ring #1
    chassis.moveToPoint(-24, 24, 10000);

    // Move to close left-side ring #2
    chassis.moveToPose(0, 60, 0, 10000);

    // Line up for close left-side rings #3, #4, #5
    chassis.moveToPoint(0, 45, 10000, {.forwards = false});

    // Turn towards close left-side rings #3, #4, #5
    chassis.turnToPoint(-24, 45, 10000);

    // Collect close left-side rings #3, #4, #5
    chassis.moveToPoint(-36, 45, 10000, {.maxSpeed = 70, .minSpeed = 70});
    chassis.moveToPoint(-60, 45, 10000, {.maxSpeed = 30});

    // Collect close left-side ring #6
    chassis.turnToPoint(-48, 60, 10000, {.maxSpeed = 75});
    chassis.moveToPoint(-48, 60, 10000);

    // Drop mobile goal #2
    chassis.turnToPoint(-72, 72, 10000);
    chassis.moveToPoint(-56, 56, 10000);
    chassis.waitUntilDone();
    grabber_piston.set_value(LOW);
}
