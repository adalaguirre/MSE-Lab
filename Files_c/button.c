/**
 * @file button.c
 * @brief Module that manipulates the push bottom component on the development board.
 * 
 * 
 * For this file to work it only needs to be called on the main.c file
 *
 * @authors Mauricio Vela, Steven McClellan
 * @date 04/16/2026
 *
 */
#include "button.h"
#include "SRS_GPIO_DRIVER.h"

// This function initializes the GPIO, Pin and mode that the push button is located
void button_init(void) {
    gpio_init();                   // Initialize GPIO subsystem
    gpio_initPort(C);             // Initialize clocking in C port  
    gpio_setPinMode(C, 13, 0);    // Set pin 13 as input
}

// This function reads the state in which the push button currently is
button_state_t button_get_state(void) {
    if (gpio_readPin(C, 13)) {    // Depending in the current bit value of Pin 13 this if condition will return 
        return BUTTON_RELEASED;   // the current condition of the Button which is or isn't pressed
    } else {
        return BUTTON_PRESSED;
    }
}