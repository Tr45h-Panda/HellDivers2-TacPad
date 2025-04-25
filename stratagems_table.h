#pragma once
#include "lvgl.h"

typedef struct {
    int id;
    const char* name;
    const char* sequence;
    const char* icon_filename;
    const lv_img_dsc_t* icon_symbol;    
} StratagemMapping;


extern const StratagemMapping stratagems[];
extern const int stratagems_count;

// Image forward declarations
// extern const lv_img_dsc_t ui_img_commando_stratagem_icon_png;
// extern const lv_img_dsc_t ui_img_reinforce_stratagem_icon_png;
// extern const lv_img_dsc_t ui_img_resupply_stratagem_icon_png;
// ... add others here


