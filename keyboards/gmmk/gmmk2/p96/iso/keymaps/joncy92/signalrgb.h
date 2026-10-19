/* SignalRGB protocol 1.0.6 (SRGBmods), buffered version.
 *
 * The original SRGBmods code writes colours straight to the LEDs whenever a
 * packet arrives. That happens between lighting frames, so it fights with any
 * indicator colours drawn by the keymap and the keys flicker.
 *
 * This version stores the colours in a buffer instead. The "SignalRGB"
 * lighting effect copies the buffer to the LEDs once per frame, and the
 * keymap's indicators are drawn on top afterwards, so nothing flickers.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */
#pragma once

#include <stdint.h>
#include <stdbool.h>

enum signalrgb_commands {
    SRGB_GET_QMK_VERSION            = 0x21,
    SRGB_GET_PROTOCOL_VERSION       = 0x22,
    SRGB_GET_UNIQUE_IDENTIFIER      = 0x23,
    SRGB_STREAM_RGB_DATA            = 0x24,
    SRGB_SET_SIGNALRGB_MODE_ENABLE  = 0x25,
    SRGB_SET_SIGNALRGB_MODE_DISABLE = 0x26,
    SRGB_GET_TOTAL_LEDS             = 0x27,
    SRGB_GET_FIRMWARE_TYPE          = 0x28,
};

/* Handle a raw HID packet. Returns true if it was a SignalRGB packet and the
   response (if any) has already been sent. */
bool signalrgb_raw_hid_rx(uint8_t *data, uint8_t length);

/* Copy SignalRGB's colours to the LEDs (called by the lighting effect). */
void signalrgb_render(uint8_t led_min, uint8_t led_max);

/* Call regularly; drops back to the normal effect if SignalRGB goes quiet. */
void signalrgb_task(void);
