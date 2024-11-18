#ifndef BELT_HPP
#define BELT_HPP

#define BELT_VOLTAGE 90 // Determine speed, from 0-127

enum BeltState {
    OFF,
    INTAKE,
    OUTTAKE,
    FORCE_INTAKE,
    FORCE_OUTTAKE
};

void startBeltTask();
void setBeltState(BeltState state);

#endif