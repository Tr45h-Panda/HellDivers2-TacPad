    #ifndef STRATAGEM_SELECTION_H
    #define STRATAGEM_SELECTION_H

    #ifdef __cplusplus
    extern "C" {
    #endif

    #include <stdint.h>
    #include "stratagems_table.h"
    #include "lvgl.h"

    #define STRAT_SLOT_COUNT 4

    typedef struct {
        int slot_selected;
        int strat_selected[STRAT_SLOT_COUNT];
        int screen_strat_index;
    } MyStrat;

    extern MyStrat myLoadOut;
    void StoreToLoadout(lv_event_t* e);
    void ButtonStrategemtoPick(int iButtonPos);
    void ButtonSelectedStrategramSlot(int index);
    void EventsSwipeLeft(void);
    void EventsSwipeRight(void);

    #ifdef __cplusplus
    }
    #endif

    #endif // STRATAGEM_SELECTION_H
