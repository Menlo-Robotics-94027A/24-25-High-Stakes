#include "auton.hpp"
#include "devices/belt.hpp"
#include "devices/devices.hpp"
#include "skills.hpp"
#include "match.hpp"

enum AutonMode selected_mode = MATCH_LEFT;

void setAutonMode(enum AutonMode mode) {
    selected_mode = mode;
}

void runAuton() {
    setBeltState(OFF);
    intake_rollers.move(0);

    if (selected_mode == SKILLS) {
        runSkillsAuton();
        return;
    } else if (selected_mode == MATCH_LEFT || selected_mode == MATCH_RIGHT) {
        runMatchAuton(selected_mode);
        return;
    }
}