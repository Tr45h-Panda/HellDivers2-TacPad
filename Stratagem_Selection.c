#include "Stratagem_Selection.h"
#include "stratagems_table.h"
#include "ui.h"
extern lv_obj_t* stratagem_buttons[8];



MyStrat myLoadOut = {
    .slot_selected = 0,
    .strat_selected = {0, 0, 0, 0},
    .screen_strat_index = 0
};

void ButtonSelectedStrategramSlot(int index) {
    myLoadOut.slot_selected = index;
}

void ButtonStrategemtoPick(int buttonPos) {
    int stratIndex = myLoadOut.screen_strat_index + buttonPos;
    myLoadOut.strat_selected[myLoadOut.slot_selected] = stratagems[stratIndex].id;

    for (int i = 0; i < STRAT_SLOT_COUNT; i++) {
        if (myLoadOut.strat_selected[i] == 0) {
            myLoadOut.slot_selected = i;
            return;
        }
    }
}
int iScreenStratPerPage = 8;


void UpdateStratagemButtons() {
    for (int i = 0; i < iScreenStratPerPage; ++i) {
        int strat_index = myLoadOut.screen_strat_index + i;

        const void* img_src;
        if (strat_index < stratagems_count) {
            img_src = stratagems[strat_index].icon_symbol;  // assuming each entry has an `img` pointer
        } else {
            img_src = stratagems[0].icon_symbol;  // default background
        }

        lv_obj_set_style_bg_img_src(stratagem_buttons[i], img_src, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_user_data(stratagem_buttons[i], (void*)(uintptr_t)strat_index);  // store actual strat index
    }
}



void EventsSwipeLeft(void) {
    myLoadOut.screen_strat_index += iScreenStratPerPage;
    if (myLoadOut.screen_strat_index >= stratagems_count) {
        myLoadOut.screen_strat_index = stratagems_count - 1;
    }
    UpdateStratagemButtons();  // Call here
}

void EventsSwipeRight(void) {
    if (myLoadOut.screen_strat_index < iScreenStratPerPage) {
        myLoadOut.screen_strat_index = 0;
    } else {
        myLoadOut.screen_strat_index -= iScreenStratPerPage;
    }
    UpdateStratagemButtons();  // And here
}

void StoreToLoadout(lv_event_t* e) {
    lv_obj_t* clicked_btn = lv_event_get_target(e);
    uintptr_t strat_index = (uintptr_t)lv_obj_get_user_data(clicked_btn);
    const StratagemMapping* strat = &stratagems[strat_index];

    // Save strat ID to current slot
    myLoadOut.strat_selected[myLoadOut.slot_selected] = strat->id;


    // Declare and initialize the slot buttons at runtime
    lv_obj_t* slot_buttons[4];
    slot_buttons[0] = ui_Button21;
    slot_buttons[1] = ui_Button22;
    slot_buttons[2] = ui_Button23;
    slot_buttons[3] = ui_Button24;

    // Update the selected slot with the icon
    lv_obj_set_style_bg_img_src(
        slot_buttons[myLoadOut.slot_selected], strat->icon_symbol,
        LV_PART_MAIN | LV_STATE_DEFAULT
    );

    // Advance to next empty slot (if any)
    for (int i = 0; i < STRAT_SLOT_COUNT; i++) {
        if (myLoadOut.strat_selected[i] == 0) {
            myLoadOut.slot_selected = i;
            break;
        }
    }

    // Highlight the currently selected slot
    for (int i = 0; i < STRAT_SLOT_COUNT; i++) {
        lv_obj_set_style_border_color(
            slot_buttons[i],
            i == myLoadOut.slot_selected ? lv_color_hex(0xFFFF00) : lv_color_hex(0xFFFFFF),
            LV_PART_MAIN | LV_STATE_DEFAULT
        );
    }
}
