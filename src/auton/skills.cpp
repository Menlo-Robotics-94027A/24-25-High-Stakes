#include "skills.hpp"
#include "devices/belt.hpp"
#include "devices/devices.hpp"

void runSkillsAuton() {
    chassis.setPose(0, 0, 0);
    pros::delay(50);

    // Enable conveyor & rollers
    setBeltState(INTAKE); // Not forced, so the jam prevention will work
    intake_rollers.move(127);
    
    // Wait 1000ms to score preload on allience stake
    pros::delay(1000);

    // Move forwards and turn 90 degrees to line up to grab goal
    chassis.moveToPoint(0, 14, 5000, {.maxSpeed = 50});
    chassis.waitUntilDone();
    chassis.turnToHeading(-90, 5000, {.maxSpeed = 75});
    chassis.waitUntilDone();

    // Reset Pose
    chassis.setPose(0, 0, 0); // Relative coordinates rather than absolute
    
    // Move towards mobile goal #1
    chassis.moveToPoint(0, -24, 5000, {.forwards = false, .maxSpeed = 50});
    chassis.waitUntil(22);

    // Pick up goal
    grabber_piston.set_value(HIGH);
    intake_rollers.move(127);
    pros::delay(500);

    // Turn towards first ring
    chassis.turnToHeading(90, 5000, {.maxSpeed = 75});
    chassis.waitUntilDone();
    
    // Reset Pose
    chassis.setPose(0, 0, 0); // Relative coordinates rather than absolute

    // Collect first right side ring
    chassis.moveToPoint(0, 24, 5000, {.maxSpeed = 50});
    chassis.waitUntilDone();

    // Reset Pose
    chassis.setPose(0, 0, 0); // Relative coordinates rather than absolute

    // Move to 2nd ring (turn 1/2)
    chassis.turnToHeading(40, 5000, {.maxSpeed = 75});
    chassis.waitUntilDone();
    chassis.setPose(0, 0, 0); // Relative coordinates rather than absolute
    chassis.moveToPoint(0, 29, 5000, {.maxSpeed = 50});
    chassis.waitUntilDone();

    // Reset Pose
    chassis.setPose(0, 0, 0); // Relative coordinates rather than absolute

    // Move to 2nd ring (turn 2/2)
    chassis.turnToHeading(50, 5000, {.maxSpeed = 75});
    chassis.waitUntilDone();
    chassis.setPose(0, 0, 0); // Relative coordinates rather than absolute
    chassis.moveToPoint(0, 10, 5000, {.maxSpeed = 50});
    chassis.waitUntilDone();

    // Reset Pose
    chassis.setPose(0, 0, 0); // Relative coordinates rather than absolute

    // Move back and turn to face 3 ring line
    chassis.moveToPoint(0, -5, 5000, {.forwards = false, .maxSpeed = 50});
    chassis.waitUntilDone();
    chassis.turnToHeading(90, 5000, {.maxSpeed = 75});
    chassis.waitUntilDone();

    // Reset Pose
    chassis.setPose(0, 0, 0); // Relative coordinates rather than absolute

    // Collect 3 ring line (~4.5ft)
    chassis.moveToPoint(0, 54, 5000, {.maxSpeed = 50});
    chassis.waitUntilDone();

    // Reset Pose
    chassis.setPose(0, 0, 0); // Relative coordinates rather than absolute

    // Rotate towards last right side ring
    chassis.turnToHeading(-135, 5000, {.maxSpeed = 75});
    chassis.waitUntilDone();

    // Reset Pose
    chassis.setPose(0, 0, 0); // Relative coordinates rather than absolute

    // Grab last right side ring
    chassis.moveToPoint(0,  12, 5000, {.maxSpeed = 50});
    chassis.waitUntilDone();

    // Reset Pose
    chassis.setPose(0, 0, 0); // Relative coordinates rather than absolute

    // Move mobile goal #1 to corner
    chassis.turnToHeading(-65, 5000, {.maxSpeed = 75});
    chassis.waitUntilDone();
    chassis.setPose(0, 0, 0); // Relative coordinates rather than absolute
    chassis.moveToPoint(0, -12, 5000, {.forwards = false, .maxSpeed = 50});
    chassis.waitUntilDone();

    // Drop mobile goal #1
    grabber_piston.set_value(LOW);
    setBeltState(OUTTAKE);
    pros::delay(500);
    setBeltState(INTAKE);

    // Reset Pose
    chassis.setPose(0, 0, 0); // Relative coordinates rather than absolute

    // Move forwards and line up to grab mobile goal #2
    chassis.moveToPoint(0, 8, 5000, {.maxSpeed = 50});
    chassis.waitUntilDone();
    chassis.turnToHeading(107, 5000, {.maxSpeed = 75});
    chassis.waitUntilDone();

    // Reset Pose
    chassis.setPose(0, 0, 0); // Relative coordinates rather than absolute

    // Move towards mobile goal #2 & pick it up
    chassis.moveToPoint(0, -75, 5000, {.forwards = false, .maxSpeed = 50});
    chassis.waitUntil(70);
    grabber_piston.set_value(HIGH);

    // Reset Pose
    chassis.waitUntilDone();
    chassis.setPose(0, 0, 0); // Relative coordinates rather than absolute

    // Rotate towards first ring on left side
    chassis.turnToHeading(-90, 5000, {.maxSpeed = 75});
    chassis.waitUntilDone();

    // Reset Pose
    chassis.setPose(0, 0, 0); // Relative coordinates rather than absolute

    // Collect first left side ring
    chassis.moveToPoint(0, 24, 5000, {.maxSpeed = 50});
    chassis.waitUntilDone();

    // Reset Pose
    chassis.setPose(0, 0, 0); // Relative coordinates rather than absolute

    // Move to 2nd ring (turn 1/2)
    chassis.turnToHeading(-40, 5000, {.maxSpeed = 75});
    chassis.waitUntilDone();
    chassis.setPose(0, 0, 0); // Relative coordinates rather than absolute
    chassis.moveToPoint(0, 29, 5000, {.maxSpeed = 50});
    chassis.waitUntilDone();

    // Reset Pose
    chassis.setPose(0, 0, 0); // Relative coordinates rather than absolute

    // Move to 2nd ring (turn 2/2)
    chassis.turnToHeading(-50, 5000, {.maxSpeed = 75});
    chassis.waitUntilDone();
    chassis.setPose(0, 0, 0); // Relative coordinates rather than absolute
    chassis.moveToPoint(0, 10, 5000, {.maxSpeed = 50});
    chassis.waitUntilDone();

    // Reset Pose
    chassis.setPose(0, 0, 0); // Relative coordinates rather than absolute

    // Move back and turn to face 3 ring line
    chassis.moveToPoint(0, -5, 5000, {.forwards = false, .maxSpeed = 50});
    chassis.waitUntilDone();
    chassis.turnToHeading(-90, 5000, {.maxSpeed = 75});
    chassis.waitUntilDone();

    // Reset Pose
    chassis.setPose(0, 0, 0); // Relative coordinates rather than absolute

    // Collect 3 ring line (~4.5ft)
    chassis.moveToPoint(0, 54, 5000, {.maxSpeed = 50});
    chassis.waitUntilDone();

    // Reset Pose
    chassis.setPose(0, 0, 0); // Relative coordinates rather than absolute

    // Rotate towards last right side ring
    chassis.turnToHeading(135, 5000, {.maxSpeed = 75});
    chassis.waitUntilDone();

    // Reset Pose
    chassis.setPose(0, 0, 0); // Relative coordinates rather than absolute

    // Grab last right side ring
    chassis.moveToPoint(0,  12, 5000, {.maxSpeed = 50});
    chassis.waitUntilDone();

    // Reset Pose
    chassis.setPose(0, 0, 0); // Relative coordinates rather than absolute

    // Move mobile goal #1 to corner
    chassis.turnToHeading(65, 5000, {.maxSpeed = 75});
    chassis.waitUntilDone();
    chassis.setPose(0, 0, 0); // Relative coordinates rather than absolute
    chassis.moveToPoint(0, -12, 5000, {.forwards = false, .maxSpeed = 50});
    chassis.waitUntilDone();

    // Drop mobile goal #1
    grabber_piston.set_value(LOW);
    setBeltState(OUTTAKE);
    pros::delay(500);
    setBeltState(INTAKE);

    // Reset Pose
    chassis.setPose(0, 0, 0); // Relative coordinates rather than absolute

    // Raise lift mechanism
    lift_piston.set_value(HIGH);

    // Turn towards ladder
    chassis.turnToHeading(90, 5000, {.maxSpeed = 75});
    chassis.waitUntilDone();
    return;
}