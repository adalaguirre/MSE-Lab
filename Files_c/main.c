/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Steven McClellan
 * @brief          : Main program body
 ******************************************************************************
 */

#include <stdint.h>
#include "button.h"
#include "led.h"


int main(void)
{
	led_init();
	button_init();

	button_state_t prev_state = BUTTON_RELEASED; // For toggle implementation, it remembers the last state of the button
	
	/* Loop forever */
	while(1){
		button_state_t state = button_get_state();

		// if (state == BUTTON_PRESSED ) led_on(); // Push to turn ON implementation
		// else led_off();

		if (state == BUTTON_PRESSED && prev_state == BUTTON_RELEASED){  // Toggle implementation
        led_toggle();
    }

    prev_state = state;	// Necessary for toggle implementation
	}
}
