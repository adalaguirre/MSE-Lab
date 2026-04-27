/**
 * @file SRS_GPIO_DRIVER.c
 * @brief Module that manipulates the components that the 
 * development board may use.
 * 
 * The user may use multiple functions to indicate the development board
 * which component it will use.
 *
 * @author Steven McClellan
 * @date 04/15/2026
 *
 */
/*** INCLUDES ***/
#include <stdint.h>
#include "stm32f4xx.h"
#include "SRS_GPIO_DRIVER.h"

GPIO_TypeDef* GPIO_arr[GPIO_PORT_MAX];

/* This register will initialize all GPIO ports in it's default state*/
void gpio_init(void){
    GPIO_arr[0] = GPIOA;
    GPIO_arr[1] = GPIOB;
    GPIO_arr[2] = GPIOC;
    GPIO_arr[3] = GPIOD;
    GPIO_arr[4] = GPIOE;
    GPIO_arr[5] = GPIOH;
}

    

/* This function shall enable clocking for a specified GPIO port */
uint32_t gpio_initPort(port_g port){
    
    // If the input port is out of the valid range the function fails
    if(port >= GPIO_PORT_MAX) return 1; // Invalid port return

    gpio_init(); // Initializes GPIO_arr contents

    // This multi-generational if sequence especifies which GPIO port shall enable
    // clocking depending on the input
    if(port == A) RCC->AHB1ENR |= (1U << 0);      // Clock enabled for GPIOA
    else if(port == B) RCC->AHB1ENR |= (1U << 1); // Clock enabled for GPIOB
    else if(port == C) RCC->AHB1ENR |= (1U << 2); // Clock enabled for GPIOC
    else if(port == D) RCC->AHB1ENR |= (1U << 3); // Clock enabled for GPIOD
    else if(port == E) RCC->AHB1ENR |= (1U << 4); // Clock enabled for GPIOE
    else if(port == H) RCC->AHB1ENR |= (1U << 7); // Clock enabled for GPIOH
    else return 1;

    return 0;
}

/* This function allows the configuration of pin direction and mode */
uint32_t gpio_setPinMode(port_g port, uint8_t pin, uint8_t mode){

    // If the input port is out of the valid range the function fails
    if(port >= GPIO_PORT_MAX) return 1; // Invalid port return

    // If the input mode is not valid the function fails
    if(mode > 3) return 1; // Invalid mode return

    if(pin > 15) return 1; // Invalid pin return


    // Clear the bits within the MODER
    GPIO_arr[port]->MODER &= ~(3<<(pin*2));
    // The operation pin*2 allows to find which real pin is being used
    // The operation 3<< shifts to the correct position on the register of the desired pin 

    // Sets the desired mode on the MODER
    GPIO_arr[port]->MODER |= (mode<<(pin*2));

    return 0;

}

/* This function will set a specified pin into a HIGH value state*/
uint32_t gpio_setPin(port_g port, uint8_t pin){
   
    // If the input port is out of the valid range the function fails
    if(port >= GPIO_PORT_MAX) return 1; // Invalid port return

    if(pin > 15) return 1;             // Invalid pin return

    GPIO_arr[port]->BSRR = (1U << pin); // Sets the specified pin
    return 0;
}

/* This function will set a specified pin into a LOW value state*/
uint32_t gpio_clearPin(port_g port, uint8_t pin){
    // If the input port is out of the valid range the function fails
    if(port >= GPIO_PORT_MAX) return 1; // Invalid port return

    if(pin > 15) return 1;             // Invalid pin return

    GPIO_arr[port]->BSRR = (1U << (pin + 16)); // Clears the specified pin
    return 0;
}

/* This function will set a specified pin into it's reversed value state*/
uint32_t gpio_togglePin(port_g port, uint8_t pin){
    // If the input port is out of the valid range the function fails
   if(port >= GPIO_PORT_MAX) return 1; // Invalid port return

    if(pin > 15) return 1;             // Invalid pin return

    GPIO_arr[port]->ODR ^= (1U << pin); // Flips the specified pin
    return 0;
}

/* This fucntion will retrieve a specified pin value state */
uint32_t gpio_readPin(port_g port, uint8_t pin){
// If the input port is out of the valid range the function fails
    if(port >= GPIO_PORT_MAX) return 1; // Invalid port return

    if(pin > 15) return 1;             // Invalid pin return

    uint32_t value = (GPIO_arr[port]->IDR >> pin) & 1U;

    return value;

}

uint32_t gpio_setAlternateFunction(port_g port, uint8_t pin, uint8_t af){
    
    // If the input port is out of the valid range the function fails
    if(port >= GPIO_PORT_MAX) return 1;
    // If the input pin is out of the valid range the function fails
    if(pin > 15) return 1;
    // If the input af is out of the valid range the function fails
    if(af > 15) return 1;

    // Set MODER to AF
    GPIO_arr[port]->MODER &= ~(3 << (pin*2));
    GPIO_arr[port]->MODER |= (2 << (pin*2));

    // Select AFR register
    if(pin < 8){
        GPIO_arr[port]->AFR[0] &= ~(0xF << (pin*4));
        GPIO_arr[port]->AFR[0] |= (af << (pin*4));
    } else {
        GPIO_arr[port]->AFR[1] &= ~(0xF << ((pin-8)*4));
        GPIO_arr[port]->AFR[1] |= (af << ((pin-8)*4));
    }

    return 0;
}