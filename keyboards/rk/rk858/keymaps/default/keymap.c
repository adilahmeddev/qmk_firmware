// Copyright 2024 yangzheng20003 (@yangzheng20003)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT( /* Base */                 //win
        KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,       KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,       KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,       KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT ,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,       KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,                      KC_RSFT,            
        KC_LCTL,  KC_LGUI,  KC_LALT,                        KC_SPC,                       KC_RALT,  KC_APP,   KC_RCTL,                      MO(1)),
   [1] = LAYOUT( /* Base */                 //win FN
        _______,  KC_MYCM,  KC_WHOM,  KC_MAIL,  KC_CALC,  KC_MSEL,  KC_MSTP,  KC_MPRV,   KC_MPLY,  KC_MNXT,  KC_MUTE,   KC_VOLD,  KC_VOLU,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,   _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,   _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,                       _______,            
        _______,  GU_TOGG,  _______,                      _______,                       _______,  _______,  _______,                       _______),
};

// clang-format on
