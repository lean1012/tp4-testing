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
 ** @brief Test para el driver test.c

Test a realizar:

1 - Al iniciar el controlador los leds deben quedar todos los bits en 0 sin importar el estado
anterior. 2 - Con todos los leds apagados prender el led 3 yverificar que efectivamente el bit 2 se
pone en 1 y el resto de bit permanece en 0. 3 - Apagar un led prendido y ver que efectivamente se
apaga y que el resto no cambia. 4 - Con todos los leds apagados prender un led y verificar que al
consultar el estado del mismo me informa que esta prendido. 5 - Prender todos los leds que estan
apagados antes de la operación 6 - Apagar todos los leds que ya estan prendidos 7 - Prender leds que
ya esten prendidos de antes 8 - Apagar leds que ya esten apagados 9 - Comprobar valores prohibidos
10- Comprobar los valores de limite
*/

/* === Headers files inclusions =============================================================== */

#include "leds.h"
#include "unity.h"
#include <stdint.h>

/* === Macros definitions ====================================================================== */

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */

static uint16_t leds_virtuales;

static const int LED = 3;

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

void setUp(void) {
    leds_init(&leds_virtuales);
}

//! @test 1 - Al iniciar el controlador los leds deben quedar todos los bits en 0 sin importar
// el estado anterior.
void test_todos_los_leds_inician_apagados(void) {
    uint16_t leds_virtuales = 0xFFFF; // sobrescribe a la global
    leds_init(&leds_virtuales);
    TEST_ASSERT_EQUAL_UINT16(0x0000, leds_virtuales);
}

//! @test 2 - Con todos los leds apagados prender el led 3 y verificar // que efectivamente
// el bit 2 se pone en 1 y el resto de bit permanece en 0.
void test_prender_un_led(void) {
    leds_turn_on(LED);

    // El bit 2 está en alto
    TEST_ASSERT_BIT_HIGH(LED - 1, leds_virtuales);
    // Todos los otros bits estan en bajo
    TEST_ASSERT_BITS_LOW(~(1 << (LED - 1)), leds_virtuales);
}

//! @test 3 - Apagar un led prendido y ver que efectivamente se apaga y que el resto no cambia.
void test_apagar_un_led(void) {
    leds_turn_on(LED);
    leds_turn_off(LED);
    TEST_ASSERT_EQUAL_UINT16(0x0000, leds_virtuales);
}

//! @test 7 - Prender leds que ya esten prendidos de antes y apagar leds que ya esten apagados
void test_prender_y_apagar_varios_led(void) {
    leds_turn_on(5);
    leds_turn_on(7);
    leds_turn_on(5);
    leds_turn_off(5);
    leds_turn_off(9);

    TEST_ASSERT_EQUAL_UINT16(1 << (7 - 1), leds_virtuales);
}

//! @test 4 - Con todos los leds apagados prender un led y verificar que // al consultar el
// estado del mismo me informa que esta prendido.
void test_estado_prendido_del_led(void) {
    leds_turn_on(LED);
    int8_t resultado = leds_is_on(LED);
    TEST_ASSERT_EQUAL_UINT16(resultado, 1);
}

//! @test 11 -  Con todos los leds apagados prender varios y apagar uno  y verificar que
// al consultar el estado del mismo me  informa que esta apagado.
void test_estado_apagado_del_led(void) {
    leds_turn_on(3);
    leds_turn_on(5);
    leds_turn_on(6);
    leds_turn_off(6);
    int8_t resultado = leds_is_off(6);
    TEST_ASSERT_EQUAL_UINT16(resultado, 1);
}

//! @test 5 - Prender todos los leds que estan apagados antes de la operación
void test_prender_todos_los_leds() {
    leds_turn_on(3);
    leds_turn_on(5);
    leds_turn_on(6);
    leds_turn_off(5);
    leds_turn_off(6);
    leds_turn_on_all();
    TEST_ASSERT_EQUAL_UINT16(0xFFFF, leds_virtuales);
}
//! @test 6 - Apagar todos los leds que ya estan prendidos
void test_apagar_todos_los_leds() {
    leds_turn_on(3);
    leds_turn_on(5);
    leds_turn_on(6);
    leds_turn_off_all();
    TEST_ASSERT_EQUAL_UINT16(0x0000, leds_virtuales);
}

//! @test 9 - Comprobar valores prohibidos
void test_led_invalido() {

    leds_turn_on(LED);
    leds_turn_on(-13);
    leds_turn_off(0);
    TEST_ASSERT_EQUAL_UINT16(1 << (LED - 1), leds_virtuales);
}

//! @test 10- Comprobar los valores de limite (superior)
void test_prender_y_apagar_ultimo_led(void) {
    leds_turn_on(16);
    TEST_ASSERT_EQUAL_UINT16(1 << (16 - 1), leds_virtuales);
    leds_turn_off(16);
    TEST_ASSERT_EQUAL_UINT16(0x0000, leds_virtuales);
}

//! @test 10- Comprobar los valores de limite (inferior)
void test_prender_y_apagar_primer_led(void) {
    leds_turn_on(1);
    TEST_ASSERT_EQUAL_UINT16(1 << (1 - 1), leds_virtuales);
    leds_turn_off(1);
    TEST_ASSERT_EQUAL_UINT16(0x0000, leds_virtuales);
}

/* === Public function implementation ========================================================== */

/* === End of documentation ==================================================================== */
