/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 */

#pragma once

/* ---- Vial ---- */
#define VIAL_KEYBOARD_UID {0x6C, 0x21, 0xF2, 0xC5, 0x40, 0x85, 0xF7, 0x63}
/* Unlock Vial's protected settings by holding Esc + Enter */
#define VIAL_UNLOCK_COMBO_ROWS { 0, 13 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 3 }

#define DYNAMIC_KEYMAP_LAYER_COUNT 3

/* ---- Lighting ---- */
/* Turn the lights off after 1 hour without a key press (any key wakes them) */
#define RGB_MATRIX_TIMEOUT 3600000

/* Turn the lights off when the PC sleeps / shuts down (USB suspend) */
#ifndef RGB_MATRIX_SLEEP
#    define RGB_MATRIX_SLEEP
#endif

/* ---- SignalRGB ---- */
/* SignalRGB's ID for the GMMK 2 96% ISO (from SRGBmods' table) */
#define SIGNALRGB_DEVICE_ID_1 0
#define SIGNALRGB_DEVICE_ID_2 0
#define SIGNALRGB_DEVICE_ID_3 10

/* If SignalRGB stops sending colours for this long (e.g. it crashed or was
   closed without saying goodbye), go back to the keyboard's own effect. */
#define SIGNALRGB_TIMEOUT_MS 5000

/* ---- Vial extras (sized to fit the keyboard's settings memory) ---- */
#define VIAL_TAP_DANCE_ENTRIES 4
#define VIAL_COMBO_ENTRIES 4
