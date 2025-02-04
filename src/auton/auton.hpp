#ifndef AUTON_HPP
#define AUTON_HPP

enum AutonCategory {
    AUTON_RED,
    AUTON_BLUE,
    AUTON_SKILLS,
    AUTON_DEBUG
};

struct Auton {
    const char* name;
    void (*function)();
    AutonCategory category;
};

Auton* getSelectedAuton();
Auton* getAutons(int* count);
void setAuton(Auton* auton);
void runAuton();

#endif