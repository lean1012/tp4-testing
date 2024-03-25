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

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

/* === Public function implementation ========================================================== */

void leds_init(uint16_t * puerto) {
    puntero = puerto;
    *puntero = ALL_LEDS_OFF;
}

void leds_turn_on(uint8_t led) {
    if (LED_VALID(led))
        *puntero |= led_to_mask(led);
}

void leds_turn_off(uint8_t led) {
    if (LED_VALID(led))
        *puntero &= ~led_to_mask(led);
}

int8_t leds_is_on(uint8_t led) {
    if (!LED_VALID(led)) {
        return LED_ERROR;
    } else {
        if (1 == right_shift(*puntero & led_to_mask(led), led - LED_OFFSET))
            return 1;
        else
            return 0;
    }
}

int8_t leds_is_off(uint8_t led) {
    if (!LED_VALID(led)) {
        return LED_ERROR;
    } else {
        if (0 == right_shift(*puntero & led_to_mask(led), led - LED_OFFSET))
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
