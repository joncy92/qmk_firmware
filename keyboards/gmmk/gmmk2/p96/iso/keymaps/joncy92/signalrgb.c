/* SignalRGB protocol 1.0.6 (based on SRGBmods' signalrgb.c), buffered version.
 * See signalrgb.h for why this is buffered.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */
#include QMK_KEYBOARD_H
#include <string.h>
#include "raw_hid.h"
#include "signalrgb.h"

#define SRGB_PROTOCOL_VERSION_1 1
#define SRGB_PROTOCOL_VERSION_2 0
#define SRGB_PROTOCOL_VERSION_3 6
#define SRGB_FIRMWARE_TYPE 2 /* QMK mainline-style */
#define SRGB_ERROR_LED_BOUNDS 253
#define SRGB_ERROR_LED_COUNT 254
#define SRGB_MAX_LEDS_PER_PACKET 9
#define SRGB_PACKET_SIZE 32 /* raw HID report size */

/* QMK version reported to SignalRGB (Vial is based on QMK 0.29) */
#define SRGB_QMK_VERSION_1 0
#define SRGB_QMK_VERSION_2 29
#define SRGB_QMK_VERSION_3 0

#ifndef SIGNALRGB_DEVICE_ID_1
#    define SIGNALRGB_DEVICE_ID_1 0
#endif
#ifndef SIGNALRGB_DEVICE_ID_2
#    define SIGNALRGB_DEVICE_ID_2 0
#endif
#ifndef SIGNALRGB_DEVICE_ID_3
#    define SIGNALRGB_DEVICE_ID_3 0
#endif
#ifndef SIGNALRGB_TIMEOUT_MS
#    define SIGNALRGB_TIMEOUT_MS 5000
#endif

static uint8_t  srgb_colours[RGB_MATRIX_LED_COUNT][3];
static bool     srgb_active      = false; /* SignalRGB has taken over the lighting */
static uint32_t srgb_last_packet = 0;

static void send_reply(uint8_t cmd, uint8_t b1, uint8_t b2, uint8_t b3) {
    uint8_t reply[SRGB_PACKET_SIZE] = {0};
    reply[0]                  = cmd;
    reply[1]                  = b1;
    reply[2]                  = b2;
    reply[3]                  = b3;
    raw_hid_send(reply, SRGB_PACKET_SIZE);
}

static void srgb_enable(void) {
    srgb_active      = true;
    srgb_last_packet = timer_read32();
    if (rgb_matrix_get_mode() != RGB_MATRIX_CUSTOM_SIGNALRGB) {
        rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_SIGNALRGB);
    }
}

static void srgb_disable(void) {
    if (srgb_active) {
        srgb_active = false;
        rgb_matrix_reload_from_eeprom(); /* back to your saved effect */
    }
}

static void srgb_stream(uint8_t *data, uint8_t length) {
    uint8_t first = data[1];
    uint8_t count = data[2];

    if ((uint16_t)first + count > RGB_MATRIX_LED_COUNT) {
        send_reply(data[0], SRGB_ERROR_LED_BOUNDS, 0, 0);
        return;
    }
    if (count > SRGB_MAX_LEDS_PER_PACKET || 3 + count * 3 > length) {
        send_reply(data[0], SRGB_ERROR_LED_COUNT, 0, 0);
        return;
    }

    memcpy(srgb_colours[first], &data[3], count * 3);

    /* Colours arriving means SignalRGB is in charge (also covers waking from
       sleep, when SignalRGB resumes without re-sending "enable"). */
    srgb_enable();
}

bool signalrgb_raw_hid_rx(uint8_t *data, uint8_t length) {
    switch (data[0]) {
        case SRGB_GET_QMK_VERSION:
            send_reply(data[0], SRGB_QMK_VERSION_1, SRGB_QMK_VERSION_2, SRGB_QMK_VERSION_3);
            break;
        case SRGB_GET_PROTOCOL_VERSION:
            send_reply(data[0], SRGB_PROTOCOL_VERSION_1, SRGB_PROTOCOL_VERSION_2, SRGB_PROTOCOL_VERSION_3);
            break;
        case SRGB_GET_UNIQUE_IDENTIFIER:
            send_reply(data[0], SIGNALRGB_DEVICE_ID_1, SIGNALRGB_DEVICE_ID_2, SIGNALRGB_DEVICE_ID_3);
            break;
        case SRGB_STREAM_RGB_DATA:
            srgb_stream(data, length);
            break;
        case SRGB_SET_SIGNALRGB_MODE_ENABLE:
            srgb_enable();
            break;
        case SRGB_SET_SIGNALRGB_MODE_DISABLE:
            srgb_disable();
            break;
        case SRGB_GET_TOTAL_LEDS:
            send_reply(data[0], RGB_MATRIX_LED_COUNT, 0, 0);
            break;
        case SRGB_GET_FIRMWARE_TYPE:
            send_reply(data[0], SRGB_FIRMWARE_TYPE, 0, 0);
            break;
        default:
            return false; /* not ours - let Vial handle it */
    }
    return true;
}

void signalrgb_render(uint8_t led_min, uint8_t led_max) {
    for (uint8_t i = led_min; i < led_max; i++) {
        rgb_matrix_set_color(i, srgb_colours[i][0], srgb_colours[i][1], srgb_colours[i][2]);
    }
}

void signalrgb_task(void) {
    if (srgb_active && timer_elapsed32(srgb_last_packet) > SIGNALRGB_TIMEOUT_MS) {
        srgb_disable();
    }
}
