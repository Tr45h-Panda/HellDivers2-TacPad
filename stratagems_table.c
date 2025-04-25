#include "stratagems_table.h"
#include "ui.h"

const StratagemMapping stratagems[] = {
    { 0, "Stratagem_Background", "D", "stratagem_textured_1.png", &ui_img_textured_bg_png },
    { 1, "Commando", "DLUDR", "commando.svg", &ui_img_commando_stratagem_icon_png },
};
    
const int stratagems_count = sizeof(stratagems) / sizeof(stratagems[0]);