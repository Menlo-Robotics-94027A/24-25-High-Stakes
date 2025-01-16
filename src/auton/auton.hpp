#ifndef AUTON_HPP
#define AUTON_HPP

// Allows this C++ header to be used in C code, which is the default language used by SquareLine Studio
#ifdef __cplusplus
extern "C" {
#endif

enum AutonMode {
    MATCH_LEFT,
    MATCH_RIGHT,
    MATCH_LEFT_WP,
    MATCH_RIGHT_WP,
    SKILLS
};

void setAutonMode(enum AutonMode mode);
void runAuton();

#ifdef __cplusplus
}
#endif

#endif