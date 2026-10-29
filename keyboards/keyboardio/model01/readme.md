# Keyboardio Model 01

A split keyboard.

* Keyboard Maintainer: QMK Community
* Hardware Supported: Keyboardio Model 01
* Hardware Availability: [Keyboardio](https://shop.keyboard.io)

Make example for this keyboard (after setting up your build environment):

    make keyboardio/model01:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.
Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Programming the Keyboard

To program the keyboard, if you have avrdude installed:

    make keyboardio/model01:default:flash

When prompted to reset your keyboard, press the prog key at upper left. If the
keyboard does not reset, you can hold the prog key while plugging it into your
computer. The prog key will light up red in programming mode.

## Features

This implements the standard keymap, including mousekeys.

It doesn't do cursor warping - QMK does not support absolute mouse positioning.

LED support is limited. Gamma compensation is not implemented. LED data is
only resent when it changes, and LED banks are sent alternating between halves,
as in Kaleidoscope. The high current power path is enabled, so if you try and
turn all the LEDs on at full brightness, something may conk out.

The scanners' keyscan interval (and therefore their built-in debounce) is left
at the scanner firmware default.

Hotplugging the two halves works but is not extensively tested. A disconnected
half is retried periodically, and its LEDs are refreshed once it reconnects.
