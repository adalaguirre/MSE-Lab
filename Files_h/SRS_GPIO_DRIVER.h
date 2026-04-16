#include <stdint.h>
#include "stm32f4xx.h"

void gpio_init();

uint32_t gpio_initPort();

uint32_t setPinMode();

uint32_t gpio_setPin();

uint32_t gpio_clearPin();

uint32_t gpio_togglePin();

uint32_t gpio_readPin();