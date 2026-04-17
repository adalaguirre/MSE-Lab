/**
 * @file led.c
 * @brief Module that manipulates the led component on the development board.
 * 
 * 
 * For this file to work it only needs to be called on the main.c file
 *
 * @authors Mauricio Vela, Steven McClellan
 * @date 04/16/2026
 *
 */
#include "led.h"
#include "SRS_GPIO_DRIVER.h"

void led_init(void) {
    gpio_init();
    gpio_initPort(A);
    gpio_setPinMode(A, 5, 1);
}

void led_on(void) {
    gpio_clearPin(A, 5); // LOW == LED ON
}

void led_off(void) {
    gpio_setPin(A, 5); // HIGH == LED OFF
}

void led_toggle(void) {
    /*XOR Operation to toggle Pin 5 */
    gpio_togglePin(A, 5);
}