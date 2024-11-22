#include "match.hpp"
#include "devices/belt.hpp"
#include "devices/devices.hpp"

void runMatchAuton(AutonMode mode) {
    chassis.setPose(0, 0, 180);
    pros::delay(50);

    // Move forward to first goal (~3ft)
    chassis.moveToPoint(0, 33, 5000, {.forwards = false, .maxSpeed = 75});
    chassis.waitUntil(30);

    // Pick up goal
    grabber_piston.set_value(HIGH);
    pros::delay(750);

    // Enable conveyor & rollers
    setBeltState(INTAKE); // Not forced, so the jam prevention will work
    intake_rollers.move(127);

    // Rotate to face ring stack
    chassis.turnToHeading(mode == MATCH_RIGHT ? 90 : 270, 5000, {.maxSpeed = 100});
    chassis.waitUntilDone();
    chassis.setPose(0, 0, 0); // Relative coordinates rather than absolute

    // Move to ring stack (a little over a foot)
    chassis.moveToPoint(0, 15, 5000, {.maxSpeed = 75});
    chassis.waitUntilDone();

    // Reset pose
    chassis.setPose(0, 0, 180); // Relative coordinates rather than absolute

    // Move to ladder
    chassis.moveToPoint(mode == MATCH_RIGHT ? 10 : -10, 30, 5000, {.forwards = false, .maxSpeed = 50}); // Move right a little to avoid the cones at the base
    
    // Disable conveyor & rollers on way to ladder
    chassis.waitUntil(15);
    setBeltState(OFF);
    intake_rollers.move(0);

    return;
}