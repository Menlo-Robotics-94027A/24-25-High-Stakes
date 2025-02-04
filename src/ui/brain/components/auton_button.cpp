#include "main.h"
#include "liblvgl/lvgl.h"
#include "auton/auton.hpp"

class AutonButton
{
private:
    Auton *auton;
    lv_obj_t *btn;
    std::function<void()> callback;
    bool is_selected = false;

public:
    AutonButton(lv_obj_t *parent, Auton *auton, std::function<void()> callback)
    {
        this->auton = auton;
        this->callback = callback;

        // Create button
        btn = lv_btn_create(parent);
        lv_obj_set_size(btn, 200, 50);

        // Set default border style (no border)
        lv_obj_set_style_border_width(btn, 0, 0);
        lv_obj_set_style_border_color(btn, lv_color_hex(0x000000), 0);

        // Create label
        lv_obj_t *label = lv_label_create(btn);
        lv_label_set_text(label, auton->name);
        lv_obj_center(label);

        // Set button color based on auton type
        if (auton->category == AutonCategory::AUTON_BLUE)
            lv_obj_set_style_bg_color(btn, lv_color_hex(0x0000FF), 0);
        else if (auton->category == AutonCategory::AUTON_RED)
            lv_obj_set_style_bg_color(btn, lv_color_hex(0xFF0000), 0);
        else if (auton->category == AutonCategory::AUTON_SKILLS)
            lv_obj_set_style_bg_color(btn, lv_color_hex(0x00FF00), 0);
        else if (auton->category == AutonCategory::AUTON_DEBUG) {
            lv_obj_set_style_bg_color(btn, lv_color_hex(0xCCCCCC), 0);
        }

        // Add click event
        lv_obj_add_event_cb(btn, [](lv_event_t *e)
                            {
            AutonButton* self = (AutonButton*)e->user_data;
            self->callback(); }, LV_EVENT_CLICKED, this);
    }

    void set_selected(bool selected) {
        is_selected = selected;
        lv_obj_set_style_border_width(btn, selected ? 4 : 0, 0);
    }

    bool is_button_selected() {
        return is_selected;
    }

    lv_obj_t *get_button()
    {
        return btn;
    }

    Auton* get_auton() {
        return auton;
    }
};
