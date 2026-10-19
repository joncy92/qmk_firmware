# joncy92 - GMMK 2 96% ISO (Vial + SignalRGB)

Built against **vial-kb/vial-qmk** (branch `vial`), not this QMK fork.

To build:
1. Clone https://github.com/vial-kb/vial-qmk
2. Copy this folder to `keyboards/gmmk/gmmk2/p96/iso/keymaps/joncy92`
3. Apply `vial-via-hook.patch` from the vial-qmk root: `git apply keyboards/gmmk/gmmk2/p96/iso/keymaps/joncy92/vial-via-hook.patch`
   (adds a `via_command_kb` hook so SignalRGB packets are handled without Vial echoing them)
4. `make gmmk/gmmk2/p96/iso:joncy92`

Features: Caps Lock area green, numpad red when Num Lock is off (no flicker with SignalRGB),
lights off on PC sleep/shutdown, 1 hour lighting timeout, Num Lock on at start-up, SignalRGB protocol 1.0.6.
