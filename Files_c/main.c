/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Mauricio Vela, Adal Aguirre, Steven McClellan
 * @brief          : Lab 2 — Timer delay + PWM simultaneous demo
 *
 * Demonstrates two independent time-based operations running at the same time:
 *
 *   1. LED blink (PA5) — toggles every 500 ms using TIM2 hardware delay.
 *      The CPU blocks in timer_delay_ms() for 500 ms, then toggles the LED.
 *
 *   2. PWM signal (PA6) — 1 kHz, 50% duty cycle via TIM3 Channel 1.
 *      Runs entirely in hardware. The CPU does nothing to maintain it.
 *      Measure with oscilloscope on CN10 pin 13.
 *
 * Both operations use different timers so they do not interfere.
 ******************************************************************************
 */

#include <stdint.h>
#include "led.h"
#include "timer.h"
#include "pwm.h"

int main(void)
{
    led_init();
    timer_init();

    pwm_init(1000);        /* 1 kHz PWM on PA6 via TIM3_CH1 */
    pwm_setSignal(50);     /* 50% duty cycle */
    pwm_start();           /* enable CCER + start TIM3 counter */

    while(1) {
        led_toggle();
        timer_delay_ms(500);
    }
}