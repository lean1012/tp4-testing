/************************************************************************************************
Copyright (c) 2023, Leandro Diaz <diazleandro1012@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*************************************************************************************************/

/** @file
 ** @brief driver for 16 LEDs
 */

/* === Headers files inclusions =============================================================== */

#include "leds.h"

/* === Macros definitions ====================================================================== */

#define BIT_HIGH     1
#define LED_OFFSET   1
#define ALL_LEDS_OFF 0x0000
#define ALL_LEDS_ON  0xFFFF
#define FIRSTLED     1
#define LASTLED      16
#define LED_VALID(x) (x >= FIRSTLED && x <= LASTLED)

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */
static uint16_t leds_virtuales;

static const int LED = 3;

static uint16_t * puntero;

/* === Private function declarations =========================================================== */

static uint16_t led_to_mask(int led) {
    return (BIT_HIGH << (led - LED_OFFSET));
}

/**
 * @brief right shift
 *
 * @param value_to_shift make a right shift
 * @param num value to shift
 * @return uint16_t shifted value
 */
static uint16_t right_shift(uint16_t value_to_shift, uint16_t num) {
    return value_to_shift >> num;
}

/**
 * @brief returns the bit of a position.
 * Example: if the number is 00001010 and the selected bit is 2, the function returns 0.
 * If the selected bit is 1, the function returns 1.
 *
 * @param number number which want to select a bit

 * @param sel_bit number of bit
 * @return uint8_t value of bit position
 */
static uint8_t select_bit(uint16_t number, uint16_t sel_bit) {
    return right_shift(number & led_to_mask(sel_bit), sel_bit - LED_OFFSET);
}

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

/* === Public function implementation ========================================================== */

void leds_init(uint16_t * puerto) {
    puntero = puerto;
    *puntero = ALL_LEDS_OFF;
}

int8_t leds_turn_on(uint8_t led) {
    if (LED_VALID(led)) {
        *puntero |= led_to_mask(led);
        return LED_SUCCESS;
    } else {
        return LED_INVALID;
    }
}

int8_t leds_turn_off(uint8_t led) {
    if (LED_VALID(led)) {
        *puntero &= ~led_to_mask(led);
        return LED_SUCCESS;
    } else {
        return LED_INVALID;
    }
}

int8_t leds_is_on(uint8_t led) {
    if (!LED_VALID(led)) {
        return LED_INVALID;
    } else {
        if (1 == select_bit(*puntero, led))
            return 1;
        else
            return 0;
    }
}

int8_t leds_is_off(uint8_t led) {
    if (!LED_VALID(led)) {
        return LED_INVALID;
    } else {
        if (0 == select_bit(*puntero, led))
            return 1;
        else
            return 0;
    }
}

void leds_turn_on_all() {
    *puntero = ALL_LEDS_ON;
}

void leds_turn_off_all() {
    *puntero = ALL_LEDS_OFF;
}

/* === End of documentation ==================================================================== */
