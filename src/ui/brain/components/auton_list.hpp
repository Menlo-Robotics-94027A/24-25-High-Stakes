#pragma once

#include "main.h"
#include "liblvgl/lvgl.h"
#include "auton/auton.hpp"
#include "auton_button.hpp"
#include <vector>
#include <functional>

class AutonButtonList {
private:
    lv_obj_t* container;
    lv_obj_t* list;
    std::vector<AutonButton*> buttons;
    int current_scroll;
    const int SCROLL_AMOUNT;

    void scroll_up();
    void scroll_down();
    void select_auton(Auton* selected);

public:
    AutonButtonList(lv_obj_t* parent, std::vector<Auton*> autons, std::function<void(Auton*)> on_select);
    ~AutonButtonList();
};
