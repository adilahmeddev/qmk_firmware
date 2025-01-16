// @sdk66, @iamdanielv & @irfanjmdn

#include <stdint.h>
#include "color.h"
#include "config.h"
#include "gpio.h"
#include "os_detection.h"
#include QMK_KEYBOARD_H
#include "features/socd_cleaner.h"

socd_cleaner_t socd_v = {{KC_W, KC_S}, SOCD_CLEANER_LAST};
socd_cleaner_t socd_h = {{KC_A, KC_D}, SOCD_CLEANER_LAST};

enum layer_names {
    _BASE,     // 0
    _BASE_FN,  // 1
    _MAC,      // 2
    _MAC_FN,   // 3
    _ALT_A,    // 4
    _ALT_A_FN, // 5
    _ALT_B,    // 6
    _ALT_B_FN, // 7
    _BOOT      // 8
};

enum custom_keycodes {
    SOCD_TOGGLE,
    /*STORE_SETUPS,*/
    /*PRINT_SETUPS,*/
};

bool    socd_enabled = true;
os_variant_t os           = 0;

const uint16_t number_to_function[] PROGMEM = {KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SOCD_TOGGLE:
            if (record->event.pressed) {
                socd_enabled = !socd_enabled;
            }
            return false;
            /*case STORE_SETUPS:*/
            /*      if (record->event.pressed) {*/
            /*          store_setups_in_eeprom();*/
            /*      }*/
            /*      return false;*/
            /*  case PRINT_SETUPS:*/
            /*      if (record->event.pressed) {*/
            /*          print_stored_setups();*/
            /*      }*/
            /*      return false;*/
    }

    if (socd_enabled) {
        if (!process_socd_cleaner(keycode, record, &socd_v)) {
            return false;
        }
        if (!process_socd_cleaner(keycode, record, &socd_h)) {
            return false;
        }
    }

    return true;
}

void housekeeping_task_user(void) {
    if (IS_LAYER_ON(_MAC) || IS_LAYER_ON(_MAC_FN)) {
        gpio_write_pin_low(LED_MAC_PIN);
        gpio_write_pin_high(LED_WIN_LOCK_PIN);
    } else {
        gpio_write_pin_high(LED_MAC_PIN);
        gpio_write_pin_low(LED_WIN_LOCK_PIN);
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] =      LAYOUT(
    KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_MUTE,
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,
    KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_PGUP,
    KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_PGDN,
    KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, MO(_BASE_FN), KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_BASE_FN] =   LAYOUT(
    KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, MO(_BOOT), _______, KC_HOME, KC_SCRL, RGB_MOD, KC_INS,
    _______, TO(_BASE), TO(_MAC), _______, _______, _______, _______, _______, _______, MO(_BOOT), _______, KC_PSCR, _______, KC_PAUSE,
    _______, _______, _______, _______, SOCD_TOGGLE, NK_TOGG, _______, _______, RGB_HUI, _______, _______, _______, RGB_VAI, KC_END,
    _______, _______, _______, EE_CLR, _______, _______, RGB_SPD, RGB_VAD, RGB_SPI
    ),

    [_MAC] =       LAYOUT(
    KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_MUTE,
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,
    KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_PGUP,
    KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_PGDN,
    KC_LCTL, KC_LALT, KC_LGUI, KC_SPC, KC_RALT, MO(_MAC_FN), KC_LEFT, KC_DOWN, KC_RGHT),

    [_MAC_FN] =    LAYOUT(
    KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, MO(_BOOT), _______, KC_HOME, KC_SCRL, RGB_MOD, KC_INS,
    _______, TO(_BASE), TO(_MAC), _______, _______, _______, _______, _______, _______, MO(_BOOT), _______, KC_PSCR, _______, KC_PAUSE,
    _______, _______, _______, _______, SOCD_TOGGLE, NK_TOGG, _______, _______, RGB_HUI, _______, _______,_______, RGB_VAI, KC_END,
    _______, _______, _______, EE_CLR, _______, _______, RGB_SPD, RGB_VAD, RGB_SPI),

    [_ALT_A] =     LAYOUT(
    KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_MUTE,
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,
    KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_PGUP,
    KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_PGDN,
    KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, MO(5), KC_LEFT, KC_DOWN, KC_RGHT),

    [_ALT_A_FN] =  LAYOUT(
    KC_GRV, KC_MYCM, KC_HOME, KC_MAIL, KC_CALC, KC_SLCT, KC_MSTP, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, MO(8), _______, KC_HOME, KC_SCRL, RGB_MOD, KC_INS,
    _______, TO(4), TO(6), _______, _______, _______, _______, _______, _______, MO(8), _______, KC_PSCR, _______, KC_PAUSE,
    _______, _______, _______, _______, _______, NK_TOGG, _______, _______, RGB_HUI, _______, _______, _______, RGB_VAI, KC_END,
    _______, _______, _______, EE_CLR, _______, _______, RGB_SPD, RGB_VAD, RGB_SPI),

    [_ALT_B] =     LAYOUT(
    KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_MUTE,
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,
    KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_PGUP,
    KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_PGDN,
    KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, MO(7), KC_LEFT, KC_DOWN, KC_RGHT),

    [_ALT_B_FN] = LAYOUT(
    KC_GRV, KC_BRMD, KC_BRMU, KC_F3, KC_F4, KC_BRID, KC_BRIU, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, MO(8), _______, KC_HOME, KC_SCRL, RGB_MOD, KC_INS,
    _______, TO(4), TO(6), _______, _______, _______, _______, _______, _______, MO(8), _______, KC_PSCR, _______, KC_PAUSE,
    _______, _______, _______, _______, _______, NK_TOGG, _______, _______, RGB_HUI, _______, _______, _______, RGB_VAI, KC_END,
    _______, _______, _______, EE_CLR, _______, _______, RGB_SPD, RGB_VAD, RGB_SPI),

    [_BOOT] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______,_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______),
};

bool process_detected_host_os_kb(os_variant_t detected_os) {
    if (!process_detected_host_os_user(detected_os)) {
        return false;
    }
    os = detected_os;
    return true;
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

    if (host_keyboard_led_state().caps_lock) {
        uint8_t index = g_led_config.matrix_co[2][0];
        if (index & LED_FLAG_KEYLIGHT) {
            rgb_matrix_set_color(index, 255, 255, 255);
        }
    }

    if (host_keyboard_led_state().caps_lock) {
        uint8_t index = g_led_config.matrix_co[2][0];
        if (index & LED_FLAG_KEYLIGHT) {
            rgb_matrix_set_color(index, 255, 255, 255);
        }
    }

    if (socd_enabled) {
        uint8_t index = g_led_config.matrix_co[3][4];
        if (index & LED_FLAG_KEYLIGHT) {
            rgb_matrix_set_color(index, 255, 255, 255);
        }
    }



    uint8_t guiKey = g_led_config.matrix_co[0][0];
    switch (os) {
        case OS_MACOS:
            rgb_matrix_set_color(guiKey, RGB_WHITE);

            if (!(IS_LAYER_ON(_MAC) || IS_LAYER_ON(_MAC_FN))) {
                layer_move(_MAC);
            }
            break;
        case OS_WINDOWS:
            rgb_matrix_set_color(guiKey, RGB_BLUE);
            if (!(IS_LAYER_ON(_BASE) || IS_LAYER_ON(_BASE_FN))) {
                layer_move(_BASE);
            }
            break;
        default:
            rgb_matrix_set_color(guiKey, RGB_RED);
            break;
    }
    return false;
}

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_BASE_FN] = {ENCODER_CCW_CW(_______, _______)},
    [_MAC] = {ENCODER_CCW_CW(_______, _______)},
    [_MAC_FN] = {ENCODER_CCW_CW(_______, _______)},
    [_ALT_A] = {ENCODER_CCW_CW(_______, _______)},
    [_ALT_A_FN] = {ENCODER_CCW_CW(_______, _______)},
    [_ALT_B] = {ENCODER_CCW_CW(_______, _______)},
    [_ALT_B_FN] = {ENCODER_CCW_CW(_______, _______)},
    [_BOOT] = {ENCODER_CCW_CW(_______, _______)}};
#endif
