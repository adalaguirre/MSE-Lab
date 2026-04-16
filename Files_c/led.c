/******************************************************************************
* Copyright (C) 2026 by Mauricio Vela Chavira - CETYS Universidad
*****************************************************************************/
#include "led.h"

#define RCC_BASE      (0x40023800UL)
#define GPIOA_BASE    (0x40020000UL)

#define RCC_AHB1ENR   (*(volatile uint32_t *)(RCC_BASE + 0x30UL))
#define GPIOA_MODER   (*(volatile uint32_t *)(GPIOA_BASE + 0x00UL))
#define GPIOA_ODR     (*(volatile uint32_t *)(GPIOA_BASE + 0x14UL))

void led_init(void) {
    RCC_AHB1ENR |= (1UL << 0);    // Reloj Puerto A
    GPIOA_MODER |= (1UL << 10);   // Pin 5 como Salida
    GPIOA_MODER &= ~(1UL << 11);
}

void led_on(void) {
    GPIOA_ODR |= (1UL << 5);
}

void led_off(void) {
    GPIOA_ODR &= ~(1UL << 5);
}

void led_toggle(void) {
    /* Operación XOR para invertir el bit 5 */
    GPIOA_ODR ^= (1UL << 5);
}