/* Copyright 2018 James Laird-Wah
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
#include "i2c_master.h"
#include "led_tables.h"
#include "rgb_matrix.h"
#include <string.h>
#include "model01.h"

/* Keep this short: a missing half NACKs every transfer, and i2c_start()
 * keeps retrying until the timeout expires. */
#define I2C_TIMEOUT     10
#define HAND_RETRY_MS   250

void set_all_leds_to(uint8_t r, uint8_t g, uint8_t b) {
  uint8_t buf[] = {
    TWI_CMD_LED_SET_ALL_TO,
    b, g, r
  };
  i2c_transmit(I2C_ADDR(LEFT), buf, sizeof(buf), I2C_TIMEOUT);
  i2c_transmit(I2C_ADDR(RIGHT), buf, sizeof(buf), I2C_TIMEOUT);
  _delay_us(10);
}

void set_led_to(int led, uint8_t r, uint8_t g, uint8_t b) {
  uint8_t buf[] = {
    TWI_CMD_LED_SET_ONE_TO,
    led & 0x1f,
    b, g, r
  };
  int hand = (led >= 32) ? RIGHT : LEFT;
  i2c_transmit(I2C_ADDR(hand), buf, sizeof(buf), I2C_TIMEOUT);
  _delay_us(10);
}

#ifdef RGB_MATRIX_ENABLE

#define LEDS_PER_HAND   32
#define LED_BANKS       4
#define LEDS_PER_BANK   8
#define BANK_BYTES      (LEDS_PER_BANK * 3)

static struct {
  uint8_t b;
  uint8_t g;
  uint8_t r;
} __attribute__((packed)) led_state[64];

static bool     leds_dirty = true;
static bool     hand_offline[2];
static uint16_t hand_retry_timer[2];

void model01_leds_invalidate(void) {
  leds_dirty = true;
}

static void set_color(int index, uint8_t r, uint8_t g, uint8_t b) {
  if (led_state[index].r == r && led_state[index].g == g && led_state[index].b == b)
    return;

  led_state[index].r = r;
  led_state[index].g = g;
  led_state[index].b = b;
  leds_dirty = true;
}

static void set_color_all(uint8_t r, uint8_t g, uint8_t b) {
  for (int i=0; i<RGB_MATRIX_LED_COUNT; i++)
    set_color(i, r, g, b);
}

static void init(void) {
  // Enable high current pathway to LEDs - this does violate the USB spec though! (1.6 amps...)
  gpio_set_pin_output(E6);
  gpio_write_pin_low(E6);

  // Overcurrent check input
  gpio_set_pin_input(B4);
}

static void flush(void) {
  if (!leds_dirty)
    return;

  bool send[2];
  bool complete = true;
  for (int hand=0; hand<2; hand++)
    send[hand] = !hand_offline[hand] || timer_elapsed(hand_retry_timer[hand]) >= HAND_RETRY_MS;

  /* Alternate between the halves, as Kaleidoscope does, so each scanner has
   * time to latch a bank before it receives the next one. */
  uint8_t command[1 + BANK_BYTES];
  for (int bank=0; bank<LED_BANKS; bank++) {
    for (int hand=0; hand<2; hand++) {
      if (!send[hand]) {
        complete = false;
        continue;
      }

      const uint8_t *bank_data = (const uint8_t *)&led_state[hand * LEDS_PER_HAND + bank * LEDS_PER_BANK];
      command[0] = TWI_CMD_LED_BASE + bank;
      for (int i=0; i<BANK_BYTES; i++)
        command[1 + i] = bank_data[i];

      if (i2c_transmit(I2C_ADDR(hand), command, sizeof(command), I2C_TIMEOUT) != I2C_STATUS_SUCCESS) {
        /* Back off so a disconnected half doesn't stall every frame. */
        send[hand] = false;
        hand_offline[hand] = true;
        hand_retry_timer[hand] = timer_read();
        complete = false;
        continue;
      }
      hand_offline[hand] = false;
      _delay_us(100);
    }
  }

  leds_dirty = !complete;
}

const rgb_matrix_driver_t rgb_matrix_driver = {
  .init = init,
  .flush = flush,
  .set_color = set_color,
  .set_color_all = set_color_all
};

#else

void model01_leds_invalidate(void) {}

#endif

/* vim: set ts=2 sw=2 et: */
