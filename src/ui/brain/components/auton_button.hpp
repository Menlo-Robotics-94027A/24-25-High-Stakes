#pragma once

#include "main.h"
#include "liblvgl/lvgl.h"
#include "auton/auton.hpp"
#include <functional>


class AutonButton {
private:
    Auton* auton;
    lv_obj_t* btn;
    std::function<void()> callback;
    bool is_selected;

public:
    AutonButton(lv_obj_t* parent, Auton* auton, std::function<void()> callback);
    void set_selected(bool selected);
    bool is_button_selected();
    lv_obj_t* get_button();
    Auton* get_auton();
};
