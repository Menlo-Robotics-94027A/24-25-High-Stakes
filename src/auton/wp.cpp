#include "wp.hpp"
#include "auton.hpp"
#include "devices/belt.hpp"
#include "devices/devices.hpp"

void runMatchAutonWP(AutonMode mode) {
    chassis.setPose(0, 0, 180);
    pros::delay(50);

    // Move forward to first goal (~3ft)
    chassis.moveToPoint(0, 29, 5000, {.forwards = false, .maxSpeed = 75});
    chassis.waitUntil(26);

    // Pick up goal
    grabber_piston.set_value(HIGH);
    pros::delay(250);

    // Enable conveyor & rollers
    setBeltState(INTAKE); // Not forced, so the jam prevention will work
    intake_rollers.move(127);

    // Rotate to face ring stack
    chassis.turnToHeading(mode == MATCH_RIGHT_WP ? 90 : 270, 5000, {.maxSpeed = 100});
    chassis.waitUntilDone();
    chassis.setPose(0, 0, 0); // Relative coordinates rather than absolute

    // Move to ring stack (a little over a foot)
    chassis.moveToPoint(0, 15, 5000, {.maxSpeed = 100});
    chassis.waitUntilDone();

    // Reset pose
    chassis.setPose(0, 0, 0); // Relative coordinates rather than absolute

    // Wait for rings to score
    pros::delay(1000);

    // Stop rollers & drop goal
    intake_rollers.move(0);
    grabber_piston.set_value(LOW);
    pros::delay(250);

    // Line up with mobile goal
    chassis.moveToPoint(0, 8, 5000, {.forwards = true, .maxSpeed = 100});
    chassis.waitUntilDone();

    // Turn to face mobile goal
    chassis.turnToHeading( mode == MATCH_RIGHT_WP ? 90 : -90, 5000, {.maxSpeed = 100});
    chassis.waitUntilDone();

    // Reset pose
    chassis.setPose(0, 0, 0); // Relative coordinates rather than absolute

    // Move back and pickup goal
    chassis.moveToPoint(0, -14, 5000, {.forwards = false, .maxSpeed = 100});
    chassis.waitUntil(10);

    // Pick up goal
    grabber_piston.set_value(HIGH);
    pros::delay(500);

    // Reset pose
    chassis.setPose(0, 0, 0); // Relative coordinates rather than absolute

    // Move to line up with ring stack
    chassis.moveToPoint(0, 40, 5000, {.maxSpeed = 100});
    chassis.waitUntilDone();

    // Turn towards ring stack
    chassis.turnToHeading(mode == MATCH_RIGHT_WP ? 90 : -90, 5000, {.maxSpeed = 100});
    chassis.waitUntilDone();

    // Turn on rollers
    intake_rollers.move(127);

    // Reset pose
    chassis.setPose(0, 0, 0); // Relative coordinates rather than absolute

    // Move to ring stack
    chassis.moveToPoint(0, 40, 5000, {.maxSpeed = 75, .earlyExitRange = 20});
    chassis.moveToPoint(0, 70, 5000 , {.maxSpeed = 50});
    chassis.waitUntilDone();


    // Reset pose
    chassis.setPose(0, 0, 0); // Relative coordinates rather than absolute

    // Turn towards ladder
    chassis.turnToHeading(mode == MATCH_RIGHT_WP ? -75 : 75, 5000);
    chassis.waitUntilDone();

    // Reset pose
    chassis.setPose(0, 0, 0); // Relative coordinates rather than absolute

    // Ram into ladder
    chassis.moveToPoint(0, -30, 5000, {.forwards = false});
}