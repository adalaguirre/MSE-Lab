/**
 * @file SRS_GPIO_DRIVER.h
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
#ifndef __SRS_GPIO_DRIVER_H__
#define __SRS_GPIO_DRIVER_H__


#include <stdint.h>
#include "stm32f4xx.h"

/* Declaring enum for ease of access from other files*/
typedef enum port{
    A,
    B,
    C,
    D,
    E,
    H,
    GPIO_PORT_MAX
}port_g;

/* Declaring universal array and size of array for GPIO addresses*/
extern GPIO_TypeDef* GPIO_arr[GPIO_PORT_MAX];

// Declaring all functions

/* This register will initialize all GPIO ports in it's default state */
void gpio_init(void);

/* This function shall enable clocking for a specified GPIO port */
uint32_t gpio_initPort(port_g port);

/* This function allows the configuration of pin direction and mode */
uint32_t gpio_setPinMode(port_g port, uint8_t pin, uint8_t mode);

/* This function will set a specified pin into a HIGH value state */
uint32_t gpio_setPin(port_g port, uint8_t pin);

/* This function will set a specified pin into a LOW value state */
uint32_t gpio_clearPin(port_g port, uint8_t pin);

/* This function will set a specified pin into it's reversed value state */
uint32_t gpio_togglePin(port_g port, uint8_t pin);

/* This fucntion will retrieve a specified pin value state */
uint32_t gpio_readPin(port_g port, uint8_t pin);


uint32_t gpio_setAlternateFunction(port_g port, uint8_t pin, uint8_t af);
#endif /* __SRS_GPIO_DRIVER_H__ */
