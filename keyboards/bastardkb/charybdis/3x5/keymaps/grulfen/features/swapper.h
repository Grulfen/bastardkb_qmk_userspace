#pragma once

#include QMK_KEYBOARD_H

// Implements alt-tab like behaviour on a single key. On first tap of trigger
// altish is held and tabish is tapped -- altish then remains held until some
// other key is hit or released. For example:
//
//     trigger, trigger, a -> alt down, tab, tab, alt up, a
//     nav down, trigger, nav up -> nav down, alt down, tab, alt up, nav up
//
// This behaviour is useful for more than just cmd-tab, hence: cmdish, tabish.
// clang-format off
void update_swapper(
    bool *active,
    uint16_t altish,
    uint16_t tabish,
    uint16_t shiftish,
    uint16_t trigger,
    uint16_t shift_trigger,
    uint16_t keycode,
    keyrecord_t *record
);
// clang-format on
