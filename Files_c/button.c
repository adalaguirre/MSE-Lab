/******************************************************************************
* Copyright (C) 2026 by Mauricio Vela Chavira - CETYS Universidad
*****************************************************************************/
#include "button.h"

#define RCC_BASE      (0x40023800UL)
#define GPIOC_BASE    (0x40020800UL)

#define RCC_AHB1ENR   (*(volatile uint32_t *)(RCC_BASE + 0x30UL))
#define GPIOC_MODER   (*(volatile uint32_t *)(GPIOC_BASE + 0x00UL))
#define GPIOC_IDR     (*(volatile uint32_t *)(GPIOC_BASE + 0x10UL))

void button_init(void) {
    RCC_AHB1ENR |= (1UL << 2);    // Reloj Puerto C
    GPIOC_MODER &= ~(3UL << 26);  // Pin 13 como Entrada
}

button_state_t button_get_state(void) {
    if (GPIOC_IDR & (1UL << 13)) {
        return BUTTON_RELEASED;
    } else {
        return BUTTON_PRESSED;
    }
}