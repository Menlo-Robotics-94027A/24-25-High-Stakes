#include "match.hpp"
#include "devices/belt.hpp"
#include "devices/devices.hpp"

void runMatchAuton(AutonMode mode) {
    chassis.setPose(0, 0, 180);
    pros::delay(50);

    // Move forward to first goal (~3ft)
    chassis.moveToPoint(0, 32, 5000, {.forwards = false, .maxSpeed = 50});
    chassis.waitUntil(30);

    // Pick up goal
    grabber_piston.set_value(HIGH);
    pros::delay(500);

    // Enable conveyor & rollers
    setBeltState(INTAKE); // Not forced, so the jam prevention will work
    intake_rollers.move(127);

    // Rotate to face ring stack
    chassis.turnToHeading(90, 5000, {.maxSpeed = 100});
    chassis.waitUntilDone();
    chassis.setPose(0, 0, 0); // Relative coordinates rather than absolute

    // Move to ring stack (2ft)
    chassis.moveToPoint(0, 24, 5000, {.maxSpeed = 50});
    chassis.waitUntilDone();

    // Rotate to face ladder
    chassis.turnToHeading(180, 5000, {.maxSpeed = 100});
    chassis.waitUntilDone();
    chassis.setPose(0, 0, 0);

    // Move to ladder
    chassis.moveToPoint(5, 30, 5000, {.maxSpeed = 50}); // Move right a little to avoid the cones at the base

    return;
}