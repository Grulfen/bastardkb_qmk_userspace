/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#include "features/casemodes.h"
#include "features/keymap_swedish_mac_ansi.h"
#include "keymap_swedish.h"

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_FUNCTION,
    LAYER_NAVIGATION,
    LAYER_MEDIA,
    LAYER_POINTER,
    LAYER_NUMERAL,
    LAYER_SYMBOLS,
};

// {{{ tap dances
enum td_keycodes {
    TD_CAPS,
    TD_SYMB,
    TD_MAC_SYMB
};

void dance_capsword(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        enable_caps_word();
        enable_xcase_with(SE_UNDS);
    } else if (state->count == 2) {
        enable_xcase_with(SE_UNDS);
    } else {
        set_oneshot_mods(MOD_LSFT);
        enable_xcase_with(OSM(MOD_LSFT));
        reset_tap_dance(state);
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_CAPS] = ACTION_TAP_DANCE_FN(dance_capsword),
};

#define TD_CPS TD(TD_CAPS)
// }}}


// {{{ layers
//
enum layers {
    _QWERTY = 0,
    _NAV,
    _SYM,
    _NUMBER,
    _MAC_QWE,
    _MAC_NAV,
    _MAC_SYM,
    _MAC_NUMBER,
    _MOUSE,
    _NUMBAR,
    _ADJUST,
};

enum custom_keycodes {
    SE_TILDE = SAFE_RANGE,
    SE_GRAVE,
    SE_HATT,
    OS_CTL,
    OS_SFT,
    OS_ALT,
    OS_GUI,
    ALT_TAB,
    SA_TAB,
    MC_TAB,
    MC_STAB,
    MC_TICK,
    MC_STICK,
};

// Aliases for readability
#define QWERTY   DF(_QWERTY)
#define SYM      MO(_SYM)
#define NAV      MO(_NAV)
#define NUMBER   MO(_NUMBER)
#define MAC_QWE  DF(_MAC_QWE)
#define MAC_SYM  MO(_MAC_SYM)
#define MAC_NAV  MO(_MAC_NAV)
#define MAC_NUM  MO(_NUMBER)
#define NUMBAR   MO(_NUMBAR)
#define ADJUST   MO(_ADJUST)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 * ,----------------------------------.  ,----------------------------------.
 * |   Q  |   W  |   E  |   R  |   T  |  |   Y  |   U  |   I  |   O  |   P  |
 * |------+------+------+------+------|  |------+------+------+------+------|
 * |   A  |   S  |   D  |   F  |   G  |  |   H  |   J  |   K  |   L  |   ;  |
 * |------+------+------+------+------|  |------+------+------+------+------|
 * |   Z  |   X  |   C  |   V  |   B  |  |   N  |   M  | ,  < | . >  | /  ? |
 * `-------------+------+------+------|  |------+------+------+-------------'
 *               |Caps- | Nav  |      |  | Space|  SYM |
 *               |Word  |      |      |  |      |      |
 *               `--------------------'  '-------------'
 */
    [_QWERTY] = LAYOUT(
     SE_Q ,  SE_W  ,  SE_E  ,   SE_R ,   SE_T ,        SE_Y,   SE_U ,   SE_I ,   SE_O ,   SE_P ,
     SE_A ,  SE_S  ,  SE_D  ,   SE_F ,   SE_G ,        SE_H,   SE_J ,   SE_K ,   SE_L , SE_SCLN,
     SE_Z ,  SE_X  ,  SE_C  ,   SE_V ,   SE_B ,        SE_N,   SE_M , SE_COMM, SE_DOT , SE_SLSH,
                     TD_CPS ,   NAV  ,_______ ,      KC_SPC,   SYM
    ),
/*
 * Nav Layer: Media, navigation, F-keys
 *
 * ,----------------------------------.  ,----------------------------------.
 * |  tab |alttab|ALTTAB|      |      |  | PgDn | PgUp | Home | End  | VolUp|
 * |------+------+------+------+------|  |------+------+------+------+------|
 * |  gui | alt  | shft | ctrl |Ctrl-b|  |  ←   |  ↓   |  ↑   |   →  | VolDn|
 * |------+------+------+------+------|  |------+------+------+------+------|
 * |PrtSc |      |      |      |      |  | Pause|M Prev|M Play|M Next|VolMut|
 * `-------------+------+------+------|  |------+------+--------------------'
 *               |      |      |      |  |      |Number|
 *               |      |      |      |  |      |      |
 *               `--------------------'  --------------'
 */
    [_NAV] = LAYOUT(
    KC_TAB , SA_TAB,  ALT_TAB, _______, _______,    KC_PGDN, KC_PGUP, KC_HOME, KC_END,  KC_VOLU,
    OS_GUI , OS_ALT , OS_SFT , OS_CTL , C(KC_B),    KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_VOLD,
    KC_PSCR, _______, _______, _______, _______,   KC_PAUSE, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE,
                      _______, _______, _______,    _______, _______
    ),
/*
 * Sym Layer: Symbols
 *
 * ,----------------------------------.  ,----------------------------------.
 * | esc  |  {   |  [   |  (   |  ~   |  |   ^  |   )  |  ]   |  }   |  `   |
 * |------+------+------+------+------|  |------+------+------+------+------|
 * |  -   |  *   |  =   |  _   |  $   |  |   #  | ctrl | shft |  alt |  gui |
 * |------+------+------+------+------|  |------+------+------+------+------|
 * |  +   |  |   |  @   |  /   |  %   |  |   '  |  \   |  &   |  ?   |   !  |
 * `-------------+------+------+------|  |------+------+--------------------'
 *               |      |      |Number|  |      |      |
 *               |      |      |      |  |      |      |
 *               `--------------------'  `-------------'
 */
    [_SYM] = LAYOUT(
     KC_ESC , SE_LCBR, SE_LBRC, SE_LPRN,SE_TILDE,    SE_HATT, SE_RPRN, SE_RBRC, SE_RCBR,SE_GRAVE,
     SE_MINS, SE_ASTR, SE_EQL , SE_UNDS, SE_DLR ,    SE_HASH, OS_CTL , OS_SFT , OS_ALT , OS_GUI ,
     SE_PLUS, SE_PIPE, SE_AT  , SE_SLSH, SE_PERC,    SE_QUOT, SE_BSLS, SE_AMPR, SE_QUES, SE_EXLM,
                       _______, _______, _______,    _______, _______
   ),
/*
 * Num Layer: Numbers
 *
 * ,----------------------------------.  ,----------------------------------.
 * |  1   |  2   |  3   |  4   |  5   |  |   6  |   7  |   8  |   9  |   0  |
 * |------+------+------+------+------|  |------+------+------+------+------|
 * | gui  | alt  | shft | ctrl | F11  |  |  F12 | ctrl | shft |  alt |  gui |
 * |------+------+------+------+------|  |------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  |  F6  |  F7  |  F8  |  F9  |  F10 |
 * `-------------+------+------+------|  |------+------+--------------------'
 *               |      |      |      |  |      |      |
 *               |      |      |      |  |      |      |
 *               `--------------------'  `-------------'
 */
    [_NUMBER] = LAYOUT(
       SE_1  ,  SE_2  ,  SE_3  ,  SE_4  ,  SE_5  ,    SE_6  ,  SE_7  ,  SE_8  ,  SE_9  ,  SE_0  ,
      OS_GUI , OS_ALT , OS_SFT , OS_CTL , KC_F11 ,   KC_F12 , OS_CTL , OS_SFT , OS_ALT , OS_GUI ,
       KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 , KC_F5  ,    KC_F6 ,  KC_F7 ,  KC_F8 ,  KC_F9 , KC_F10 ,
                        _______, _______, _______,   _______, _______
    ),
/*
 * Mac Base Layer: MAC_QWERTY
 *
 * ,----------------------------------.   ,----------------------------------.
 * |   Q  |   W  |   E  |   R  |   T  |   |   Y  |   U  |   I  |   O  |   P  |
 * |------+------+------+------+------|   |------+------+------+------+------|
 * |   A  |   S  |   D  |   F  |   G  |   |   H  |   J  |   K  |   L  |   ;  |
 * |------+------+------+------+------|   |------+------+------+------+------|
 * |   Z  |   X  |   C  |   V  |   B  |   |   N  |   M  | ,  < | . >  | /  ? |
 * `-------------+------+------+------|   |------+------+--------------------'
 *               |Caps- | Nav  |Shift |   | Space| Sym  |
 *               |Word  |      |      |   |      |      |
 *               `--------------------'   `-------------'
 */
    [_MAC_QWE] = LAYOUT(
       AP_Q ,  AP_W  ,  AP_E  ,   AP_R ,   AP_T ,       AP_Y,   AP_U ,   AP_I ,   AP_O ,   AP_P ,
       AP_A ,  AP_S  ,  AP_D  ,   AP_F ,   AP_G ,       AP_H,   AP_J ,   AP_K ,   AP_L , AP_SCLN,
       AP_Z ,  AP_X  ,  AP_C  ,   AP_V ,   AP_B ,       AP_N,   AP_M , AP_COMM, AP_DOT , AP_SLSH,
                       TD_CPS ,MAC_NAV , KC_LSFT,     KC_SPC, MAC_SYM
    ),
/*
 * Mac_Nav Layer: Mac Media, navigation, F-keys
 *
 * ,----------------------------------.   ,----------------------------------.
 * |  tab |alttab|ALTTAB|alt+` |ALT+` |   | PgDn | PgUp | Home | End  | VolUp|
 * |------+------+------+------+------|   |------+------+------+------+------|
 * |  gui | alt  | shft | ctrl |Ctrl-b|   |  ←   |  ↓   |  ↑   |   →  | VolDn|
 * |------+------+------+------+------|   +------+------+------+------+------|
 * |PrtSc |      |      |      |      |   | Pause|M Prev|M Play|M Next|VolMut|
 * `-------------+------+------+------|   +------+------+--------------------'
 *               |      |      |      |   |      |Number|
 *               |      |      |      |   |      |      |
 *               `--------------------'   `-------------'
 */
    [_MAC_NAV] = LAYOUT(
       KC_TAB , MC_STAB, MC_TAB , MC_TICK,MC_STICK,  KC_PGDN, KC_PGUP, KC_HOME, KC_END,  KC_VOLU,
       OS_GUI , OS_ALT , OS_SFT , OS_CTL , C(KC_B),  KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_VOLD,
       KC_PSCR, _______, _______, _______, _______, KC_PAUSE, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE,
                         _______, _______, _______,  _______, _______
    ),
/*
 * Mac Sym Layer: Mac Symbols
 *
 * ,----------------------------------.   ,----------------------------------.
 * | esc  |  {   |  [   |  (   |  ~   |   |   ^  |   )  |  ]   |  }   |  `   |
 * |------+------+------+------+------|   |------+------+------+------+------|
 * |  -   |  *   |  =   |  _   |  $   |   |   #  | ctrl | shft |  alt |  gui |
 * |------+------+------+------+------|   |------+------+------+------+------|
 * |  +   |  |   |  @   |  /   |  %   |   |   '  |  \   |  &   |  ?   |   !  |
 * `-------------+------+------+------|   |------+------+--------------------'
 *               |      |Number|      |   |      |      |
 *               |      |      |      |   |      |      |
 *               `--------------------'   '-------------'
 */
    [_MAC_SYM] = LAYOUT(
     KC_ESC , AP_LCBR, AP_LBRC, AP_LPRN,SE_TILDE,    SE_HATT, AP_RPRN, AP_RBRC, AP_RCBR,SE_GRAVE,
     AP_MINS, AP_ASTR, AP_EQL , AP_UNDS, AP_DLR ,    AP_HASH, OS_CTL , OS_SFT , OS_ALT , OS_GUI ,
     AP_PLUS, AP_PIPE, AP_AT  , AP_SLSH, AP_PERC,    AP_QUOT, AP_BSLS, AP_AMPR, AP_QUES, AP_EXLM,
                       _______, _______, _______,    _______, _______
   ),

/*
 * Mac Num Layer: Mac Numbers
 *
 * ,----------------------------------.   ,----------------------------------.
 * |  1   |  2   |  3   |  4   |  5   |   |   6  |   7  |   8  |   9  |   0  |
 * |------+------+------+------+------|   |------+------+------+------+------|
 * | gui  | alt  | shft | ctrl | F11  |   |  F12 | ctrl | shft |  alt |  gui |
 * |------+------+------+------+------|   |------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |   |  F6  |  F7  |  F8  |  F9  |  F10 |
 * `-------------+------+------+------|   |------+------+--------------------'
 *               |      |      |      |   |      |      |
 *               |      |      |      |   |      |      |
 *               `--------------------'   '-------------'
 */
    [_MAC_NUMBER] = LAYOUT(
      SE_1  ,  SE_2  ,  SE_3  ,  SE_4  ,  SE_5  ,     SE_6  ,  SE_7  ,  SE_8  ,  SE_9  ,  SE_0  ,
     OS_GUI , OS_ALT , OS_SFT , OS_CTL , KC_F11 ,    KC_F12 , OS_CTL , OS_SFT , OS_ALT , OS_GUI ,
      KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 , KC_F5  ,     KC_F6 ,  KC_F7 ,  KC_F8 ,  KC_F9 , KC_F10 ,
                       _______, _______, _______,    _______, _______
    ),
/*
 * Numbar
 *
 * ,----------------------------------.   ,----------------------------------.
 * |      |  F7  |  F8  |  F9  | F12  |   |      | 7 &  | 8 *  | 9 (  | - _  |
 * |------+------+------+------+------|   |------+------+------+------+------|
 * |      |  F4  |  F5  |  F6  | F11  |   |  *   | 4 $  | 5 %  | 6 ^  | = +  |
 * |------+------+------+------+------|   |------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  | F10  |   |      | 1 !  | 2 @  | 3 #  |  /   |
 * `-------------+------+------+------|   |------+------+--------------------'
 *               |      |      |      |   | 0 )  |      |
 *               |      |      |      |   |      |      |
 *               `--------------------'   '-------------'
 */
    [_NUMBAR] = LAYOUT(
     _______,  KC_F7 ,  KC_F8 ,  KC_F9 , KC_F12 ,    _______, SE_7,    SE_8,    SE_9, SE_MINS,
     _______,  KC_F4 ,  KC_F5 ,  KC_F6 , KC_F11 ,    SE_ASTR, SE_4,    SE_5,    SE_6, SE_PLUS,
     _______,  KC_F1 ,  KC_F2 ,  KC_F3 , KC_F10 ,    _______, SE_1,    SE_2,    SE_3, SE_SLSH,
                       _______, _______, _______,    _______, SE_0
    ),
/*
 * Mouse Layer: Mouse stuff
 *
 * ,----------------------------------.   ,----------------------------------.
 * |      |      | DPI+ | SDPI+|      |   |      |      |      |      |      |
 * |------+------+------+------+------|   |------+------+------+------+------|
 * |      |      |      |      |      |   |      |      |      |      |      |
 * |------+------+------+------+------|   |------+------+------+------+------|
 * |      |      |MOUSE1|MOUSE2|      |   |      |      |      |SNIPE |SCROLL|
 * `-------------+------+------+------|   |------+------+--------------------'
 *               |      |      |      |   |      |      |
 *               |      |      |      |   |      |      |
 *               `--------------------'   '-------------'
 */
    [_MOUSE] = LAYOUT(
     _______, _______, DPI_MOD, S_D_MOD, _______,    _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______,
     _______, _______, MS_BTN1, MS_BTN2, _______,    _______, _______, _______, _______, _______,
                       _______, _______, _______,    _______, _______
    ),

/*
 * Adjust
 *
 * ,----------------------------------.   ,----------------------------------.
 * |QWERTY|HUE_UP|SAT_UP|VAL_UP|SPD_UP|   |      |      |      |      |      |
 * |------+------+------+------+------|   |------+------+------+------+------|
 * | MAC  |HUE_D |SAT_D |VAL_D |SPD_D |   |      |      |      |      |      |
 * |------+------+------+------+------|   |------+------+------+------+------|
 * |      |      |      |      |      |   |      |      |      |      |      |
 * `-------------+------+------+------|   |------+------+--------------------'
 *               |      |      |      |   |      |      |
 *               |      |      |      |   |      |      |
 *               `--------------------'   '-------------'
 */
    [_ADJUST] = LAYOUT(
     QWERTY , UG_HUEU, UG_SATU, UG_VALU, UG_SPDU,    _______, _______, _______, _______, _______,
     MAC_QWE, UG_HUED, UG_SATD, UG_VALD, UG_SPDD,    _______, _______, _______, _______, _______,
     _______, UG_TOGG, _______, UG_PREV, UG_NEXT,    _______, _______, _______, _______, _______,
                       _______, _______, _______,    _______, _______
    ),

};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _SYM, _NAV, _NUMBER);
    state = update_tri_layer_state(state, _MAC_SYM, _MAC_NAV, _MAC_NUMBER);
    return state;
}

// }}}

// {{{ key overrides
// Add key overrides to emulate american layout on swedish keyboard
const key_override_t coln_key_override = ko_make_basic(MOD_MASK_SHIFT, SE_SCLN, SE_COLN);  // shift + ; -> :
const key_override_t squo_key_override = ko_make_basic(MOD_MASK_SHIFT, SE_QUOT, SE_DQUO);  // shift + ' -> "

const key_override_t labk_key_override = ko_make_with_layers(MOD_MASK_SHIFT, SE_COMM, SE_LABK, 1 << _QWERTY);  // shift + , -> <
const key_override_t rabk_key_override = ko_make_with_layers(MOD_MASK_SHIFT, SE_DOT, SE_RABK, 1 << _QWERTY);   // shift + . -> >

const key_override_t mac_labk_key_override = ko_make_with_layers(MOD_MASK_SHIFT, AP_COMM, AP_LABK, 1 << _MAC_QWE);  // shift + , -> <
const key_override_t mac_rabk_key_override = ko_make_with_layers(MOD_MASK_SHIFT, AP_DOT, AP_RABK, 1 << _MAC_QWE);   // shift + . -> >

const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL); // shift + backspace -> Del

const key_override_t *key_overrides[] = {
    &coln_key_override,
    &squo_key_override,
    &labk_key_override,
    &rabk_key_override,
    &mac_labk_key_override,
    &mac_rabk_key_override,
    &delete_key_override,
};

// }}}

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in
// rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif

// vim: set foldmethod=marker:foldlevel=0
