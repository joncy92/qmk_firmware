# Vial (live remapping from the Vial app / vial.rocks)
VIA_ENABLE = yes
VIAL_ENABLE = yes
VIALRGB_ENABLE = yes

# Extra features you can set up in the Vial app
TAP_DANCE_ENABLE = yes
COMBO_ENABLE = yes
KEY_OVERRIDE_ENABLE = no

# Lighting
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_CUSTOM_USER = yes   # adds the "SignalRGB" lighting effect (rgb_matrix_user.inc)

# SignalRGB support (talks to SignalRGB over raw HID; see signalrgb.c)
RAW_ENABLE = yes
SRC += signalrgb.c

LTO_ENABLE = yes
