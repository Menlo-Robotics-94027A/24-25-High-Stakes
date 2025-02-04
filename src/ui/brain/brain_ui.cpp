#include "main.h"
#include "liblvgl/lvgl.h"
#include "liblvgl/core/lv_theme.h"
#include "auton/auton.hpp"

// Config
#define BUTTON_HEIGHT 64

// Global variables
lv_obj_t *tabview;

// Button Maps (16 per tab, might expand later)
const char *red_auton_buttons[] = {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""};
const char *blue_auton_buttons[] = {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""};
const char *skills_auton_buttons[] = {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""};
const char *debug_auton_buttons[] = {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""};

int red_auton_count = 0;
int blue_auton_count = 0;
int skills_auton_count = 0;
int debug_auton_count = 0;

// Button matrixes
lv_obj_t *red_auton_button_matrix;
lv_obj_t *blue_auton_button_matrix;
lv_obj_t *skills_auton_button_matrix;
lv_obj_t *debug_auton_button_matrix;

// Scrolling button callbacks
void scroll_up_cb(lv_event_t *e)
{
    lv_obj_t *container = (lv_obj_t *)lv_event_get_user_data(e);
    lv_coord_t current_scroll = lv_obj_get_scroll_y(container);
    lv_obj_scroll_to_y(container, current_scroll - (BUTTON_HEIGHT * 2), LV_ANIM_ON);
}

void scroll_down_cb(lv_event_t *e)
{
    lv_obj_t *container = (lv_obj_t *)lv_event_get_user_data(e);
    lv_coord_t current_scroll = lv_obj_get_scroll_y(container);
    lv_obj_scroll_to_y(container, current_scroll + (BUTTON_HEIGHT * 2), LV_ANIM_ON);
}

// Auton selection callbacks
void update_selection(lv_obj_t *matrix, int selected, AutonCategory category)
{
    // Clear previous selection (matrixes)
    lv_btnmatrix_clear_btn_ctrl_all(red_auton_button_matrix, LV_BTNMATRIX_CTRL_CHECKED);
    lv_btnmatrix_clear_btn_ctrl_all(blue_auton_button_matrix, LV_BTNMATRIX_CTRL_CHECKED);
    lv_btnmatrix_clear_btn_ctrl_all(skills_auton_button_matrix, LV_BTNMATRIX_CTRL_CHECKED);
    lv_btnmatrix_clear_btn_ctrl_all(debug_auton_button_matrix, LV_BTNMATRIX_CTRL_CHECKED);

    // Set new selection (matrix)
    lv_btnmatrix_set_btn_ctrl(matrix, selected, LV_BTNMATRIX_CTRL_CHECKED);

    // Get all autons of selected type
    int autonCount;
    Auton *autons = getAutons(&autonCount);
    std::vector<Auton *> filtered_autons;
    for (int i = 0; i < autonCount; i++)
    {
        Auton *auton = &autons[i];
        if (auton->category == category)
        {
            filtered_autons.push_back(auton);
        }
    }

    // Set selected auton
    setAuton(filtered_autons[selected]);
}
void red_auton_selected(lv_event_t *e)
{
    int selected = lv_btnmatrix_get_selected_btn(red_auton_button_matrix);
    update_selection(red_auton_button_matrix, selected, AutonCategory::AUTON_RED);
}

void blue_auton_selected(lv_event_t *e)
{
    int selected = lv_btnmatrix_get_selected_btn(blue_auton_button_matrix);
    update_selection(blue_auton_button_matrix, selected, AutonCategory::AUTON_BLUE);
}

void skills_auton_selected(lv_event_t *e)
{
    int selected = lv_btnmatrix_get_selected_btn(skills_auton_button_matrix);
    update_selection(skills_auton_button_matrix, selected, AutonCategory::AUTON_SKILLS);
}

void debug_auton_selected(lv_event_t *e)
{
    int selected = lv_btnmatrix_get_selected_btn(debug_auton_button_matrix);
    update_selection(debug_auton_button_matrix, selected, AutonCategory::AUTON_DEBUG);
}

void startBrainUI()
{
    // Loop over Auton[] array
    int autonCount;
    Auton *autons = getAutons(&autonCount);

    for (int i = 0; i < autonCount; i++)
    {
        Auton *auton = &autons[i];
        if (auton->category == AutonCategory::AUTON_RED)
        {
            red_auton_buttons[red_auton_count * 2] = auton->name;
            if (red_auton_count > 0)
            {
                red_auton_buttons[red_auton_count * 2 - 1] = "\n";
            }
            red_auton_count++;
        }
        else if (auton->category == AutonCategory::AUTON_BLUE)
        {
            blue_auton_buttons[blue_auton_count * 2] = auton->name;
            if (blue_auton_count > 0)
            {
                blue_auton_buttons[blue_auton_count * 2 - 1] = "\n";
            }
            blue_auton_count++;
        }
        else if (auton->category == AutonCategory::AUTON_SKILLS)
        {
            skills_auton_buttons[skills_auton_count * 2] = auton->name;
            if (skills_auton_count > 0)
            {
                skills_auton_buttons[skills_auton_count * 2 - 1] = "\n";
            }
            skills_auton_count++;
        }
        else if (auton->category == AutonCategory::AUTON_DEBUG)
        {
            debug_auton_buttons[debug_auton_count * 2] = auton->name;
            if (debug_auton_count > 0)
            {
                debug_auton_buttons[debug_auton_count * 2 - 1] = "\n";
            }
            debug_auton_count++;
        }
    }

    // Initialize LVGL
    lv_init();
    lv_obj_t *scr = lv_obj_create(NULL);
    lv_scr_load(scr);

    // Configure LVGL Theme
    lv_disp_t *disp = lv_disp_get_default();
    lv_theme_t *th = lv_theme_default_init(disp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
    lv_disp_set_theme(disp, th);

    // Create tabview (and 4 tabs)
    tabview = lv_tabview_create(scr, LV_DIR_TOP, 40);
    lv_obj_clear_flag(tabview, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_t *red_tab = lv_tabview_add_tab(tabview, "Red");
    lv_obj_t *blue_tab = lv_tabview_add_tab(tabview, "Blue");
    lv_obj_t *skills_tab = lv_tabview_add_tab(tabview, "Skills");
    lv_obj_t *debug_tab = lv_tabview_add_tab(tabview, "Debug");

    // Select default auton tab
    lv_tabview_set_act(tabview, 0, LV_ANIM_ON);

    // Create scrollable containers
    for (lv_obj_t *tab : {red_tab, blue_tab, skills_tab, debug_tab})
    {
        // Create scrollable container
        lv_obj_t *container = lv_obj_create(tab);

        // Configure size & alignment
        lv_obj_set_width(container, LV_PCT(85));
        lv_obj_set_height(container, LV_PCT(100));
        lv_obj_align(container, LV_ALIGN_TOP_LEFT, 0, 0);

        // Configuring style
        lv_obj_set_style_pad_all(container, 0, 0);
        lv_obj_set_style_bg_opa(container, 0, 0);
        lv_obj_set_style_border_width(container, 0, 0);
        lv_obj_set_style_shadow_width(container, 0, 0);

        // Configure scrolling
        lv_obj_add_flag(container, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_scroll_dir(container, LV_DIR_VER);
        lv_obj_set_scroll_snap_y(container, LV_SCROLL_SNAP_CENTER);
        lv_obj_clear_flag(container, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
        lv_obj_add_flag(container, LV_OBJ_FLAG_SCROLL_WITH_ARROW);
    }

    // Create scroll buttons
    for (lv_obj_t *tab : {red_tab, blue_tab, skills_tab, debug_tab})
    {
        // Create buttons
        lv_obj_t *up_button = lv_btn_create(tab);
        lv_obj_t *down_button = lv_btn_create(tab);

        // Style buttons
        lv_obj_set_size(up_button, 48, 48);
        lv_obj_set_size(down_button, 48, 48);

        // Align buttons
        lv_obj_align(up_button, LV_ALIGN_RIGHT_MID, 0, -32);
        lv_obj_align(down_button, LV_ALIGN_RIGHT_MID, 0, 32);

        // Label buttons
        lv_obj_t *up_label = lv_label_create(up_button);
        lv_obj_t *down_label = lv_label_create(down_button);

        lv_label_set_text(up_label, LV_SYMBOL_UP);
        lv_label_set_text(down_label, LV_SYMBOL_DOWN);

        // Align labels
        lv_obj_center(up_label);
        lv_obj_center(down_label);

        // Add event callbacks
        lv_obj_add_event_cb(up_button, scroll_up_cb, LV_EVENT_CLICKED, lv_obj_get_child(tab, 0));
        lv_obj_add_event_cb(down_button, scroll_down_cb, LV_EVENT_CLICKED, lv_obj_get_child(tab, 0));

        // Prevent horizontal scrolling
        lv_obj_clear_flag(tab, LV_OBJ_FLAG_SCROLLABLE);
    }

    // Create button matrices
    red_auton_button_matrix = lv_btnmatrix_create(lv_obj_get_child(red_tab, 0));
    blue_auton_button_matrix = lv_btnmatrix_create(lv_obj_get_child(blue_tab, 0));
    skills_auton_button_matrix = lv_btnmatrix_create(lv_obj_get_child(skills_tab, 0));
    debug_auton_button_matrix = lv_btnmatrix_create(lv_obj_get_child(debug_tab, 0));

    for (lv_obj_t *matrix : {red_auton_button_matrix, blue_auton_button_matrix,
                             skills_auton_button_matrix, debug_auton_button_matrix})
    {
        // Alignment & Size
        lv_obj_set_align(matrix, LV_ALIGN_TOP_LEFT);
        lv_obj_set_width(matrix, LV_PCT(100));
        lv_obj_set_style_height(matrix, LV_SIZE_CONTENT, 0);

        // Button padding
        lv_obj_set_style_pad_top(matrix, 0, 0);
        lv_obj_set_style_pad_bottom(matrix, 0, 0);
        lv_obj_set_style_pad_left(matrix, 0, 0);
        lv_obj_set_style_pad_right(matrix, 0, 0);
        lv_obj_set_style_pad_row(matrix, 8, 0);

        // Styling
        lv_obj_set_style_bg_opa(matrix, 0, 0);
        lv_obj_set_style_border_width(matrix, 0, 0);

        // Styling (selected)
        lv_obj_set_style_bg_opa(matrix, 0, LV_PART_ITEMS | LV_STATE_CHECKED);
        lv_obj_set_style_border_width(matrix, 2, LV_PART_ITEMS | LV_STATE_CHECKED);
        lv_obj_set_style_border_color(matrix, lv_palette_main(LV_PALETTE_BLUE), LV_PART_ITEMS | LV_STATE_CHECKED);
    }

    lv_obj_set_height(red_auton_button_matrix, BUTTON_HEIGHT * red_auton_count);
    lv_obj_set_height(blue_auton_button_matrix, BUTTON_HEIGHT * blue_auton_count);
    lv_obj_set_height(skills_auton_button_matrix, BUTTON_HEIGHT * skills_auton_count);
    lv_obj_set_height(debug_auton_button_matrix, BUTTON_HEIGHT * debug_auton_count);

    // Set button matrix event callbacks
    lv_obj_add_event_cb(red_auton_button_matrix, red_auton_selected, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(blue_auton_button_matrix, blue_auton_selected, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(skills_auton_button_matrix, skills_auton_selected, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(debug_auton_button_matrix, debug_auton_selected, LV_EVENT_VALUE_CHANGED, NULL);

    // Set button matrices
    lv_btnmatrix_set_map(red_auton_button_matrix, red_auton_buttons);
    lv_btnmatrix_set_map(blue_auton_button_matrix, blue_auton_buttons);
    lv_btnmatrix_set_map(skills_auton_button_matrix, skills_auton_buttons);
    lv_btnmatrix_set_map(debug_auton_button_matrix, debug_auton_buttons);
}