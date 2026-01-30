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
#include "pointing_device.h"
#include QMK_KEYBOARD_H

#include "features/oneshot.h"
#include "features/casemodes.h"
#include "features/swapper.h"
#include "features/keymap_swedish_mac_ansi.h"
#include "keymap_swedish.h"

// {{{ tap dances
enum td_keycodes {
    TD_CAPS,
    TD_SYMB,
    TD_MAC_SYMB,
    TD_NAVI,
    TD_MAC_NAVI
};

void td_sym_tap_fn(tap_dance_state_t *state, void *user_data);
void td_sym_reset_fn(tap_dance_state_t *state, void *user_data);

void mac_td_sym_tap_fn(tap_dance_state_t *state, void *user_data);
void mac_td_sym_reset_fn(tap_dance_state_t *state, void *user_data);

void td_nav_tap_fn(tap_dance_state_t *state, void *user_data);
void td_nav_reset_fn(tap_dance_state_t *state, void *user_data);

void mac_td_nav_tap_fn(tap_dance_state_t *state, void *user_data);
void mac_td_nav_reset_fn(tap_dance_state_t *state, void *user_data);

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
    [TD_SYMB] = ACTION_TAP_DANCE_FN_ADVANCED(td_sym_tap_fn, NULL, td_sym_reset_fn),
    [TD_MAC_SYMB] = ACTION_TAP_DANCE_FN_ADVANCED(mac_td_sym_tap_fn, NULL, mac_td_sym_reset_fn),
    [TD_NAVI] = ACTION_TAP_DANCE_FN_ADVANCED(td_nav_tap_fn, NULL, td_nav_reset_fn),
    [TD_MAC_NAVI] = ACTION_TAP_DANCE_FN_ADVANCED(mac_td_nav_tap_fn, NULL, mac_td_nav_reset_fn),
};

#define TD_CPS TD(TD_CAPS)
#define TD_SYM TD(TD_SYMB)
#define TD_MC_S TD(TD_MAC_SYMB)
#define TD_NAV TD(TD_NAVI)
#define TD_MC_N TD(TD_MAC_NAVI)
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
 *               |Caps- | Nav  |Numbar|  | Space|  SYM |
 *               |Word  |      |      |  |      |      |
 *               `--------------------'  '-------------'
 */
    [_QWERTY] = LAYOUT(
     SE_Q ,  SE_W  ,  SE_E  ,   SE_R ,   SE_T ,        SE_Y,   SE_U ,   SE_I ,   SE_O ,   SE_P ,
     SE_A ,  SE_S  ,  SE_D  ,   SE_F ,   SE_G ,        SE_H,   SE_J ,   SE_K ,   SE_L , SE_SCLN,
     SE_Z ,  SE_X  ,  SE_C  ,   SE_V ,   SE_B ,        SE_N,   SE_M , SE_COMM, SE_DOT , SE_SLSH,
                     TD_CPS , TD_NAV , NUMBAR ,      KC_SPC, TD_SYM
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
                      _______, TD_NAV , _______,    _______, _______
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
                       _______, _______, _______,    _______, TD_SYMB
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
 *               |Caps- | Nav  |Number|   | Space| Sym  |
 *               |Word  |      |      |   |      |      |
 *               `--------------------'   `-------------'
 */
    [_MAC_QWE] = LAYOUT(
       AP_Q ,  AP_W  ,  AP_E  ,   AP_R ,   AP_T ,       AP_Y,   AP_U ,   AP_I ,   AP_O ,   AP_P ,
       AP_A ,  AP_S  ,  AP_D  ,   AP_F ,   AP_G ,       AP_H,   AP_J ,   AP_K ,   AP_L , AP_SCLN,
       AP_Z ,  AP_X  ,  AP_C  ,   AP_V ,   AP_B ,       AP_N,   AP_M , AP_COMM, AP_DOT , AP_SLSH,
                       TD_CPS ,TD_MC_N , NUMBAR ,     KC_SPC, TD_MC_S
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
                         _______, TD_MC_N, _______,  _______, _______
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
                       _______, _______, _______,    _______, TD_MC_S
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
 * |SCROLL|      |      |      |      |   |      |      |      |      |      |
 * |------+------+------+------+------|   |------+------+------+------+------|
 * |SNIPE |      |MOUSE1|MOUSE2|      |   |      |      |      |      |      |
 * `-------------+------+------+------|   |------+------+--------------------'
 *               |      |      |      |   |      |      |
 *               |      |      |      |   |      |      |
 *               `--------------------'   '-------------'
 */
    [_MOUSE] = LAYOUT(
     _______, _______, DPI_MOD, S_D_MOD, _______,    _______, _______, _______, _______, _______,
     DRGSCRL, _______, _______, _______, _______,    _______, _______, _______, _______, _______,
     SNIPING, _______, MS_BTN1, MS_BTN2, _______,    _______, _______, _______, _______, _______,
                       _______, _______, _______,    _______, _______
    ),

/*
 * Adjust
 *
 * ,----------------------------------.   ,----------------------------------.
 * |QWERTY|HUE_UP|SAT_UP|VAL_UP|SPD_UP|   |      |      |      |      | BOOT |
 * |------+------+------+------+------|   |------+------+------+------+------|
 * | MAC  |HUE_D |SAT_D |VAL_D |SPD_D |   |      |      |      |      |      |
 * |------+------+------+------+------|   |------+------+------+------+------|
 * |      |RGBTOG|      |RGBPRV|RGBNXT|   |      |      |      |      |      |
 * `-------------+------+------+------|   |------+------+--------------------'
 *               |      |      |      |   |      |      |
 *               |      |      |      |   |      |      |
 *               `--------------------'   '-------------'
 */
    [_ADJUST] = LAYOUT(
     QWERTY , UG_HUEU, UG_SATU, UG_VALU, UG_SPDU,    _______, _______, _______, _______, QK_BOOT,
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

// {{{ combos

enum combo_events {
  JKL_ENT,
  XC_ESC,
  OP_ARNG,
  LSEMICOLON_ADIA,
  KSEMICOLON_ODIA,
  MCOMMA_MINS,
  COMMADOT_UNDS,
  COMBO_LENGTH
};

uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM jkl_combo[] = {KC_J, KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM xc_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM op_combo[] = {KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM ksemicolon_combo[] = {KC_K, SE_SCLN, COMBO_END};
const uint16_t PROGMEM lsemicolon_combo[] = {KC_L, SE_SCLN, COMBO_END};
const uint16_t PROGMEM mcomma_combo[] = {KC_M, SE_COMM, COMBO_END};
const uint16_t PROGMEM commadot_combo[] = {SE_COMM, SE_DOT, COMBO_END};

combo_t key_combos[] = {
    [JKL_ENT] = COMBO(jkl_combo, KC_ENT),
    [XC_ESC] = COMBO(xc_combo, KC_ESC),
    [OP_ARNG] = COMBO(op_combo, SE_ARNG),
    [LSEMICOLON_ADIA] = COMBO(lsemicolon_combo, SE_ADIA),
    [KSEMICOLON_ODIA] = COMBO(ksemicolon_combo, SE_ODIA),
    [MCOMMA_MINS] = COMBO(mcomma_combo, SE_MINS),
    [COMMADOT_UNDS] = COMBO(commadot_combo, SE_UNDS),
};
// }}}

// {{{ process_record_user

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case SYM:
    case TD_SYM:
    case NAV:
    case TD_NAV:
    case MAC_SYM:
    case TD_MC_S:
    case MAC_NAV:
    case TD_MC_N:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case SYM:
    case TD_SYM:
    case NAV:
    case TD_NAV:
    case MAC_SYM:
    case TD_MC_S:
    case MAC_NAV:
    case TD_MC_N:
    case OS_SFT:
    case OS_CTL:
    case OS_ALT:
    case OS_GUI:
        return true;
    default:
        return false;
    }
}

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

bool sw_win_active = false;
bool mac_sw_app_active = false;
bool mac_sw_win_active = false;

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (!process_case_modes(keycode, record)) {
        return false;
    }

    update_oneshot(
        &os_shft_state, KC_LSFT, OS_SFT, keycode, record
    );
    update_oneshot(
        &os_ctrl_state, KC_LCTL, OS_CTL, keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT, keycode, record
    );
    update_oneshot(
        &os_cmd_state, KC_LGUI, OS_GUI, keycode, record
    );

    update_swapper(&sw_win_active, KC_LALT, KC_TAB, KC_LSFT, ALT_TAB, SA_TAB, keycode, record);
    update_swapper(&mac_sw_app_active, KC_LGUI, KC_TAB, KC_LSFT, MC_TAB, MC_STAB, keycode, record);
    update_swapper(&mac_sw_win_active, KC_LGUI, AP_LABK, KC_LSFT, MC_TICK, MC_STICK, keycode, record);

    // Regular user keycode case statement
    switch (keycode) {
        case SE_TILDE:
            if (record->event.pressed) {
                SEND_STRING("~");
            }
            return true;
        case SE_GRAVE:
            if (record->event.pressed) {
                SEND_STRING("`");
            }
            return true;
        case SE_HATT:
            if (record->event.pressed) {
                SEND_STRING("^");
            }
            return true;
        default:
            return true;
    }
}

// }}}

// {{{ tap dance function definitions
void td_sym_tap_fn(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        layer_on(_SYM);
    } else if (state->count == 2) {
        layer_on(_ADJUST);
    }
}

void td_sym_reset_fn(tap_dance_state_t *state, void *user_data) {
    layer_off(_ADJUST);
    layer_off(_SYM);
};

void mac_td_sym_tap_fn(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        layer_on(_MAC_SYM);
    } else if (state->count == 2) {
        layer_on(_ADJUST);
    }
}

void mac_td_sym_reset_fn(tap_dance_state_t *state, void *user_data) {
    layer_off(_ADJUST);
    layer_off(_MAC_SYM);
};

void td_nav_tap_fn(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        layer_on(_NAV);
    } else if (state->count == 2) {
        layer_on(_MOUSE);
    }
}

void td_nav_reset_fn(tap_dance_state_t *state, void *user_data) {
    layer_off(_MOUSE);
    layer_off(_NAV);
};

void mac_td_nav_tap_fn(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        layer_on(_MAC_NAV);
    } else if (state->count == 2) {
        layer_on(_MOUSE);
    }
}

void mac_td_nav_reset_fn(tap_dance_state_t *state, void *user_data) {
    layer_off(_MOUSE);
    layer_off(_MAC_NAV);
};
// }}}

// {{{ Mouse

#define SCROLL_THRESHOLD 7
#define BACKSPACE_THRESHOLD -10
#define MAX_SCROLL_SPEED 50
#define MIN_SCROLL_DELAY 5
#define BACKSPACE_DELAY 50

static void clear_mouse_movement(report_mouse_t* mouse_report) {
    mouse_report->x = 0;
    mouse_report->y = 0;
    mouse_report->h = 0;
    mouse_report->v = 0;
}

static int calculate_adaptive_delay(int movement, int max_speed, int min_delay, int delay_range) {
    int speed = abs(movement);
    speed = speed > max_speed ? max_speed : speed;
    const float fraction = speed / (float)max_speed;
    return min_delay + (delay_range * (1.0f - fraction));
}

static void handle_vertical_scroll(mouse_xy_report_t y_movement) {
    static uint16_t last_scroll_time = 0;
    const int adaptive_delay = calculate_adaptive_delay(y_movement, MAX_SCROLL_SPEED, MIN_SCROLL_DELAY, 100);

    if (y_movement < -SCROLL_THRESHOLD && timer_elapsed(last_scroll_time) > adaptive_delay) {
        tap_code(KC_UP);
        last_scroll_time = timer_read();
    } else if (y_movement > SCROLL_THRESHOLD && timer_elapsed(last_scroll_time) > adaptive_delay) {
        tap_code(KC_DOWN);
        last_scroll_time = timer_read();
    }
}

static void handle_horizontal_backspace(mouse_xy_report_t x_movement) {
    static uint16_t last_backspace_time = 0;

    if (x_movement < BACKSPACE_THRESHOLD) {
        const int adaptive_delay = calculate_adaptive_delay(x_movement, MAX_SCROLL_SPEED, MIN_SCROLL_DELAY, 100);
        if (timer_elapsed(last_backspace_time) > adaptive_delay) {
            tap_code(KC_BSPC);
            last_backspace_time = timer_read();
        }
    }
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (layer_state_is(_MOUSE)) {
        return mouse_report;
    }

    if (!(layer_state_is(_NAV) || layer_state_is(_MAC_NAV))) {
        clear_mouse_movement(&mouse_report);
        return mouse_report;
    }

    if (abs(mouse_report.y) > abs(mouse_report.x)) {
        handle_vertical_scroll(mouse_report.y);
    } else {
        handle_horizontal_backspace(mouse_report.x);
    }

    clear_mouse_movement(&mouse_report);
    return mouse_report;
}
// }}}

// {{{ process_detected_host_os

bool process_detected_host_os_user(os_variant_t detected_os) {
    switch (detected_os) {
        case OS_MACOS:
            set_single_default_layer(_MAC_QWE);
            break;
        case OS_WINDOWS:
        case OS_LINUX:
            set_single_default_layer(_QWERTY);
            break;
        default:
            break;
    }
    return true;
}
// }}}

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in
// rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif

// vim: set foldmethod=marker:foldlevel=0
