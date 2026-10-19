/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>
 * Keymap: joncy92 (Vial + SignalRGB)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 */

#include QMK_KEYBOARD_H
#include "usb_device_state.h"
#include "signalrgb.h"

#define _BL 0
#define _FL 1
#define _L2 2

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Base layer */
[_BL] = LAYOUT(
  QK_GESC,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  KC_DEL,   KC_INS,   KC_PGUP,  KC_PGDN,
  KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_NUM,   KC_PSLS,  KC_PAST,  KC_PMNS,
  KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_ENT,   KC_P7,    KC_P8,    KC_P9,    KC_PPLS,
  KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_NUHS,            KC_P4,    KC_P5,    KC_P6,
  KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,    KC_P1,    KC_P2,    KC_P3,    KC_PENT,
  KC_LCTL,  KC_LGUI,  KC_LALT,                      KC_SPC,                                 KC_RALT,  MO(_FL),  KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_P0,    KC_PDOT),

  /* Function layer (hold Fn) */
[_FL] = LAYOUT(
  QK_BOOT,  KC_MYCM,  KC_WHOM,  KC_CALC,  KC_MSEL,  KC_MPLY,  KC_MPRV,  KC_MNXT,  KC_MSTP,  KC_MUTE,  KC_VOLU,  KC_VOLD,  _______,  _______,  _______,  _______,  KC_HOME,  KC_END,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,
  _______,  _______,  RM_SATU,  RM_SATD,  RM_SPDD,  RM_SPDU,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RM_VALU,  _______,  _______,  _______,  _______,
  _______,  UC_WIN,   _______,                      _______,                                _______,  _______,  _______,  RM_PREV,  RM_VALD,  RM_NEXT,  _______,  _______),

  /* Spare layer - set it up in Vial if you want it */
[_L2] = LAYOUT(
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,                      _______,                                _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______)
};
// clang-format on

/* ------------------------------------------------------------------------
 * Indicator lights
 *
 * LED numbers (GMMK 2 96% ISO): Caps 54, Tab 36, A 55, Left Shift 70.
 * Numpad: Num Lock 32, / 33, * 34, - 35, 7 50, 8 51, 9 52, + 53,
 *         4 67, 5 68, 6 69, 1 84, 2 85, 3 86, Enter 87, 0 98, . 99.
 * Side light bars: left 100-109, right 110-119.
 * ------------------------------------------------------------------------ */

static const uint8_t caps_leds[]   = {54, 36, 55, 70};
static const uint8_t numpad_leds[] = {32, 33, 34, 35, 50, 51, 52, 53, 67, 68, 69, 84, 85, 86, 87, 98, 99};

#define CAPS_COLOUR 0, 255, 0  /* green */
#define NUM_OFF_COLOUR 255, 0, 0 /* red */

static void paint(const uint8_t *leds, uint8_t count, uint8_t r, uint8_t g, uint8_t b, uint8_t led_min, uint8_t led_max) {
    for (uint8_t i = 0; i < count; i++) {
        if (leds[i] >= led_min && leds[i] < led_max) {
            rgb_matrix_set_color(leds[i], r, g, b);
        }
    }
}

/* Runs every lighting frame, AFTER the effect (or SignalRGB) has drawn, so
 * these colours always win and never flicker. */
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    /* PC off / not talking to the keyboard: keep everything dark */
    if (usb_device_state_get_configure_state() != USB_DEVICE_STATE_CONFIGURED) {
        for (uint8_t i = led_min; i < led_max; i++) {
            rgb_matrix_set_color(i, 0, 0, 0);
        }
        return false;
    }

    led_t leds = host_keyboard_led_state();

    if (leds.caps_lock) {
        paint(caps_leds, sizeof(caps_leds), CAPS_COLOUR, led_min, led_max);
    }
    if (!leds.num_lock) {
        paint(numpad_leds, sizeof(numpad_leds), NUM_OFF_COLOUR, led_min, led_max);
    }
    return false;
}

/* ------------------------------------------------------------------------
 * SignalRGB
 * ------------------------------------------------------------------------ */

/* SignalRGB's messages are handled here; anything else goes to Vial. */
bool via_command_kb(uint8_t *data, uint8_t length) {
    return signalrgb_raw_hid_rx(data, length);
}

void housekeeping_task_user(void) {
    signalrgb_task();
}

/* ------------------------------------------------------------------------
 * Num Lock on at start-up (what STARTUP_NUMLOCK_ON was meant to do)
 * ------------------------------------------------------------------------ */
bool led_update_user(led_t led_state) {
    static bool checked = false;
    if (!checked && usb_device_state_get_configure_state() == USB_DEVICE_STATE_CONFIGURED) {
        checked = true;
        if (!led_state.num_lock) {
            tap_code(KC_NUM);
        }
    }
    return true;
}
