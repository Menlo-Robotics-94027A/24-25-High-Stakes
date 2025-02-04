#include "match.hpp"
#include "devices/belt.hpp"
#include "devices/devices.hpp"

void blueLeft()
{
    // Set pose to start position
    chassis.setPose(54, -21, -135);

    // Turn on rollers
    intake_rollers.move(127);

    // Move to ring stack @ 24, -48 (1.5" offset for turning)
    chassis.moveToPoint(24, -49.5, 5000);
    chassis.waitUntilDone();

    // Turn towards mobile goal #1
    chassis.turnToHeading(-270, 5000);

    // Move backwards towards mobile goal #1 @ 0, -48 (10" away)
    chassis.moveToPoint(10, -48, 5000, {.forwards = false, .maxSpeed = 50});
    chassis.waitUntilDone();

    // Pickup mobile goal #1
    grabber_piston.set_value(HIGH);
    pros::delay(250);

    // Run belt & rollers to score rings
    setBeltState(BELT_INTAKE);

    // Move to next set of rings @ 48, 0
    chassis.moveToPoint(24, -48, 5000, {.earlyExitRange = 10});
    chassis.moveToPose(48, 12, 0, 5000);
    chassis.waitUntil(40);

    // Enable Auto Hold
    setAutoHoldState(AUTO_HOLD_ANY);

    // Drop goal (early),
    grabber_piston.set_value(LOW);

    // Wait until done picking up rings
    chassis.waitUntilDone();

    // Turn towards goal @ 24, -24
    chassis.turnToPoint(24, -24, 1000, {.forwards = false});

    // Move to second goal @ 24, -24 (extra 2" to ensure grab)
    chassis.moveToPoint(20, -28, 5000, {.forwards = false, .maxSpeed = 75});
    chassis.waitUntilDone();

    // Pickup goal
    grabber_piston.set_value(HIGH);
    pros::delay(250);

    // Start scoring
    setBeltState(BELT_INTAKE);

    // Run until ladder @ 24, 0
    chassis.moveToPose(24, 0, 0, 10000);
    chassis.waitUntilDone();

    // Stop scoring
    setBeltState(BELT_OFF);
    intake_rollers.move(0);
}

void blueRight()
{
    // Set pose to start position
    chassis.setPose(59, 15, 0); // maybe 58, 15, 0

    // Move to alliance stake (2.5" offset for wonky turning)
    chassis.moveToPoint(59, 2.5, 10000, {.forwards = false});

    // Turn towards alliance stake
    chassis.turnToHeading(-90, 10000);

    // Move back to start position
    chassis.moveToPoint(62.5, 0, 5000);

    // Wait until done to score
    chassis.waitUntilDone();
    setBeltState(BeltState::BELT_INTAKE);

    // Wait for scoring
    pros::delay(1000);

    // Back away from wall
    chassis.moveToPoint(54, 0, 10000);

    // Turn towards mobile goal
    chassis.turnToPoint(24, 24, 1000, {.forwards = false});

    // Move to mobile goal (extra 4" to ensure grab)
    chassis.moveToPoint(28, 20, 10000, {.forwards = false, .maxSpeed = 75});
    chassis.waitUntilDone();

    // Pickup goal
    grabber_piston.set_value(HIGH);
    pros::delay(250);

    // Move torward rings @ 0,0 (extra 4" for target, extra 12" for grab)
    chassis.turnToPoint(4, 44, 1000);
    chassis.moveToPoint(12, 36, 10000);

    // Run rollers
    intake_rollers.move(127);
    chassis.waitUntilDone();

    // Collect additional rings in center stack
    chassis.moveToPose(12, 50, 0, 10000);

    // Turn towards second ring stack
    chassis.turnToHeading(90, 1000);

    // Collect second ring stack
    chassis.moveToPoint(36, 48, 10000);
    chassis.waitUntilDone();

    // Wait 1s to score
    pros::delay(1000);

    // Move to ladder
    chassis.moveToPoint(12, 12, 10000);

    // Turn off belt
    chassis.waitUntil(24);
    setBeltState(BeltState::BELT_OFF);
    intake_rollers.move(0);

    // Move to center slowly
    chassis.moveToPoint(0, 0, 10000, {.maxSpeed = 30});
}

void redRight()
{
    // Set pose to start position
    chassis.setPose(-55, -24, 135);

    // Turn on rollers
    intake_rollers.move(127);

    // Move to ring stack @ 24, -48 (1.5" offset for turning)
    chassis.moveToPoint(-24, -46.5, 5000);
    chassis.waitUntilDone();

    // Turn towards mobile goal #1
    chassis.turnToHeading(270, 5000);

    // Move backwards towards mobile goal #1 @ 0, -48 (10" away)
    chassis.moveToPoint(-10, -48, 5000, {.forwards = false, .maxSpeed = 50});
    chassis.waitUntilDone();

    // Pickup mobile goal #1
    grabber_piston.set_value(HIGH);
    pros::delay(250);

    // Run belt & rollers to score rings
    setBeltState(BELT_INTAKE);

    // Move to next set of rings @ 48, 0
    chassis.moveToPoint(-24, -48, 5000, {.earlyExitRange = 10});
    chassis.moveToPose(-48, 12, 0, 5000);
    chassis.waitUntil(40);

    // Enable Auto Hold
    setAutoHoldState(AUTO_HOLD_ANY);

    // Drop goal (early),
    grabber_piston.set_value(LOW);

    // Wait until done picking up rings
    chassis.waitUntilDone();

    // Turn towards goal @ 24, -24
    chassis.turnToPoint(-24, -24, 1000, {.forwards = false});

    // Move to second goal @ 24, -24 (extra 2" to ensure grab)
    chassis.moveToPoint(-22, -26, 5000, {.forwards = false, .maxSpeed = 75});
    chassis.waitUntilDone();

    // Pickup goal
    grabber_piston.set_value(HIGH);
    pros::delay(250);

    // Start scoring
    setBeltState(BELT_INTAKE);

    // Run until ladder @ 24, 0
    chassis.moveToPose(-24, 0, 0, 10000);
    chassis.waitUntilDone();

    // Stop scoring
    setBeltState(BELT_OFF);
    intake_rollers.move(0);
}

void redLeft()
{
    // Set pose to start position
    chassis.setPose(-59, 15, 0);

    // Move to alliance stake
    chassis.moveToPoint(-59, 1, 10000, {.forwards = false});

    // Turn towards alliance stake
    chassis.turnToHeading(90, 10000);

    // Move back to start position
    chassis.moveToPoint(-62.5, 0, 5000);

    // Wait until done to score
    chassis.waitUntilDone();
    setBeltState(BeltState::BELT_INTAKE);

    // Wait for scoring
    pros::delay(1000);

    // Back away from wall
    chassis.moveToPoint(-56, 0, 10000);

    // Turn towards mobile goal
    chassis.turnToPoint(-24, 24, 1000, {.forwards = false});

    // Move to mobile goal (extra 4" to ensure grab)
    chassis.moveToPoint(-26, 22, 10000, {.forwards = false, .maxSpeed = 75});
    chassis.waitUntilDone();

    // Pickup goal
    grabber_piston.set_value(HIGH);
    pros::delay(250);

    // Move torward rings @ 0,0 (extra 4" for target, extra 12" for grab)
    chassis.turnToPoint(-4, 44, 1000);
    chassis.moveToPoint(-11, 36, 10000);

    // Run rollers
    intake_rollers.move(127);
    chassis.waitUntilDone();

    // Collect additional rings in center stack
    chassis.moveToPose(-11, 50, 0, 10000);

    // Turn towards second ring stack
    chassis.turnToHeading(-90, 1000);

    // Collect second ring stack
    chassis.moveToPoint(-36, 48, 10000);
    chassis.waitUntilDone();

    // Wait 1s to score
    pros::delay(1000);

    // Move to ladder
    chassis.moveToPoint(-12, 12, 10000);

    // Turn off belt
    chassis.waitUntil(24);
    setBeltState(BeltState::BELT_OFF);
    intake_rollers.move(0);

    // Move to center slowly
    chassis.moveToPoint(0, 0, 10000, {.maxSpeed = 50});
}
