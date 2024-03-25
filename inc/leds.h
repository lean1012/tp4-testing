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

#ifndef LEDS_H
#define LEDS_H

/** @file leds.h
 ** @brief Definiciones de la biblioteca para manejo de leds
 **/

/* === Headers files inclusions ================================================================ */

#include <stdint.h>

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */

#define LED_ERROR 255 /** Invalid LED **/

/* === Public data type declarations =========================================================== */

/* === Public variable declarations ============================================================ */

/* === Public function declarations ============================================================ */

/**
 * @brief Init port of leds
 *
 * @remark This function must be called before any other function in the library
 *
 * @param puerto pointer to port of leds
 */
void leds_init(uint16_t * puerto);
/**
 * @brief turn on the led
 *
 * @param led number of led to turn on (1 to 16)
 */
void leds_turn_on(uint8_t led);
/**
 * @brief turn off the led
 *
 * @param led number of led to turn off (1 to 16)
 */
void leds_turn_off(uint8_t led);
/**
 * @brief State of led
 *
 * @param led number of led
 * @return uint8_t return 1 if the led is on
 *                        0 if the led is off
 *                        LED_ERROR if the led parameter is invalid
 */
int8_t leds_is_on(uint8_t led);
/**
 * @brief State of led
 *
 * @param led number of led
 * @return uint8_t return 1 if the led is off
 *                        0 if the led is on
 *                        LED_ERROR if the led parameter is invalid
 */
int8_t leds_is_off(uint8_t led);
/**
 * @brief Turn on all leds
 *
 */
void leds_turn_on_all();
/**
 * @brief Turn off all leds
 *
 */
void leds_turn_off_all();

/* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* MAIN_H */
