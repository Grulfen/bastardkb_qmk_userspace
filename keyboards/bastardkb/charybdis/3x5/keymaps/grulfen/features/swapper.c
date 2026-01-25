#include "swapper.h"

void update_swapper(
    bool *active,
    uint16_t altish,
    uint16_t tabish,
    uint16_t shiftish,
    uint16_t trigger,
    uint16_t shift_trigger,
    uint16_t keycode,
    keyrecord_t *record
) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            *active = true;
            unregister_code(shiftish);
            register_code(altish);
            register_code(tabish);
        } else {
            unregister_code(tabish);
            // Don't unregister altish until some other key is hit or released.
        }
    } else if (keycode == shift_trigger) {
        if (record->event.pressed) {
            *active = true;
            register_code(altish);
            register_code(shiftish);
            register_code(tabish);
        } else {
            unregister_code(tabish);
            // Don't unregister altish until some other key is hit or released.
        }
    } else if (*active) {
        unregister_code(altish);
        unregister_code(shiftish);
        *active = false;
    }
}
