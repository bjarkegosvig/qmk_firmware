/* Copyright 2018 James Laird-Wah
 * Copyright 2025 QMK
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "leds.h"
#include "led_tables.h"
#include "rgb_matrix.h"
#include <string.h>
#include "model100.h"

/* LED writes go over the SAME I2C1 bus as the key scanners. QMK's ChibiOS DMA
 * i2c_transmit does not work on the GD32F303 and mixing it with the polled key
 * reads corrupts the bus, so use the shared polled i2c_poll_write (matrix.c). */

/* Like Kaleidoscope, gamma-correct every channel just before it is sent. */
#define GAMMA(c)        pgm_read_byte(&CIE1931_CURVE[(c)])

void set_all_leds_to(uint8_t r, uint8_t g, uint8_t b) {
  uint8_t buf[] = {
    TWI_CMD_LED_SET_ALL_TO,
    GAMMA(b), GAMMA(g), GAMMA(r)
  };
  i2c_poll_write(I2C_ADDR(LEFT), buf, sizeof(buf));
  i2c_poll_write(I2C_ADDR(RIGHT), buf, sizeof(buf));
}

void set_led_to(int led, uint8_t r, uint8_t g, uint8_t b) {
  uint8_t buf[] = {
    TWI_CMD_LED_SET_ONE_TO,
    led & 0x1f,
    GAMMA(b), GAMMA(g), GAMMA(r)
  };
  int hand = (led >= 32) ? RIGHT : LEFT;
  i2c_poll_write(I2C_ADDR(hand), buf, sizeof(buf));
}

#ifdef RGB_MATRIX_ENABLE

/* Each hand's 32 LEDs are sent as 4 banks of 8 LEDs (8 * 3 = 24 bytes).
 * led_state[0..31] is the left hand, [32..63] the right. */
#define LEDS_PER_HAND   32
#define LED_BANKS       4
#define LEDS_PER_BANK   (LEDS_PER_HAND / LED_BANKS)   /* 8 */
#define ALL_BANKS       ((1U << LED_BANKS) - 1)

static struct {
  uint8_t b;
  uint8_t g;
  uint8_t r;
} __attribute__((packed)) led_state[64];

/* Banks (bit n = bank n) per hand that the scanner doesn't have yet. */
static uint8_t dirty_banks[2] = {ALL_BANKS, ALL_BANKS};

/* RGB Matrix normally applies the CIE curve to the HSV value. Gamma is applied
 * per channel on output instead (see flush), so convert without it. */
rgb_t rgb_matrix_hsv_to_rgb(hsv_t hsv) {
  return hsv_to_rgb_nocie(hsv);
}

void model100_leds_resend(int hand) {
  dirty_banks[hand] = ALL_BANKS;
}

static void set_color(int index, uint8_t r, uint8_t g, uint8_t b) {
  if (led_state[index].r == r && led_state[index].g == g && led_state[index].b == b)
    return;

  led_state[index].r = r;
  led_state[index].g = g;
  led_state[index].b = b;
  dirty_banks[index / LEDS_PER_HAND] |= 1U << ((index % LEDS_PER_HAND) / LEDS_PER_BANK);
}

static void set_color_all(uint8_t r, uint8_t g, uint8_t b) {
  for (int i=0; i<RGB_MATRIX_LED_COUNT; i++)
    set_color(i, r, g, b);
}

static void init(void) {
  /* The Model 100 gates power to the two 5V scanner/LED nets via B9, which is
   * enabled in matrix_init(). Unlike the Model 01 there is no separate
   * high-current LED enable line to drive here. B14/B15 are power-sense inputs. */
  gpio_set_pin_input(B14);
  gpio_set_pin_input(B15);
}

/* Only banks that changed (or failed to send) go out, so a static frame costs
 * no I2C traffic. A changed bank is sent to both hands, interleaved bank by bank
 * (L0, R0, L1, R1, ...): back-to-back writes to the same ATtiny outrun it (it is
 * still committing the previous bank to memory) and later banks get dropped.
 * Kaleidoscope documents this exact race and alternates hands the same way. */
static void flush(void) {
  uint8_t command[1 + LEDS_PER_BANK * 3];
  uint8_t banks = dirty_banks[LEFT] | dirty_banks[RIGHT];

  for (int bank = 0; bank < LED_BANKS; bank++) {
    if (!(banks & (1U << bank)))
      continue;

    command[0] = TWI_CMD_LED_BASE + bank;
    for (int hand = 0; hand < 2; hand++) {
      const uint8_t *src = (const uint8_t *)&led_state[hand * LEDS_PER_HAND + bank * LEDS_PER_BANK];
      for (int i = 0; i < LEDS_PER_BANK * 3; i++)
        command[1 + i] = GAMMA(src[i]);
      if (i2c_poll_write(I2C_ADDR(hand), command, sizeof(command)))
        dirty_banks[hand] &= ~(1U << bank);
    }
  }
}

const rgb_matrix_driver_t rgb_matrix_driver = {
  .init = init,
  .flush = flush,
  .set_color = set_color,
  .set_color_all = set_color_all
};

#else

void model100_leds_resend(int hand) {}

#endif

/* vim: set ts=2 sw=2 et: */
