#include "skills.hpp"
#include "devices/belt.hpp"
#include "devices/devices.hpp"

void runSkillsAuton() {
    chassis.setPose(0, 0, 180);
    pros::delay(50);

    // Enable conveyor & rollers
    setBeltState(INTAKE); // Not forced, so the jam prevention will work
    intake_rollers.move(127);
    
    // Wait a sec to score preload on allience stake
    // chassis.waitUntilDone();

    // Move forwards and turn 90 degrees to line up to grab goal
    chassis.moveToPoint(0, 18, 5000, {.maxSpeed = 50});
    chassis.waitUntilDone();
    chassis.turnToHeading(90, 5000, {.maxSpeed = 100});


    return;
}