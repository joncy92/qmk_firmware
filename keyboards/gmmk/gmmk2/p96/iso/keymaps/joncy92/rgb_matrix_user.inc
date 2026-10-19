// "SignalRGB" lighting effect: shows the colours SignalRGB sends.
RGB_MATRIX_EFFECT(SIGNALRGB)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

void signalrgb_render(uint8_t led_min, uint8_t led_max);

static bool SIGNALRGB(effect_params_t *params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    signalrgb_render(led_min, led_max);
    return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
