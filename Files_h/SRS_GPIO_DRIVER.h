#include <stdint.h>

/* Declaring and defining enum for ease of access from other files*/
typedef enum port{
    A,
    B,
    C,
    D,
    E,
    H,
    SIZE
}port_g;

// Declaring all functions

/* This register will initialize all GPIO ports in it's default state */
void gpio_init();

/* This function shall enable clocking for a specified GPIO port */
uint32_t gpio_initPort(GPIO_TypeDef* GPIO_in);

/* This function allows the configuration of pin direction and mode */
uint32_t setPinMode(port_g port, uint8_t pin);

/* This function will set a specified pin into a HIGH value state */
uint32_t gpio_setPin(port_g port, uint8_t pin);

/* This function will set a specified pin into a LOW value state */
uint32_t gpio_clearPin(port_g port, uint8_t pin);

/* This function will set a specified pin into it's reversed value state */
uint32_t gpio_togglePin(port_g port, uint8_t pin);

/* This fucntion will retrieve a specified pin value state */
uint32_t gpio_readPin(port_g port, uint8_t pin);


uint32_t gpio_setAlternateFunction(port_g port, uint8_t pin);