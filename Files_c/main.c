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

#define BLINK_PERIOD_MS  500U   /* LED toggle period in milliseconds */
#define PWM_FREQUENCY_HZ 1000U  /* PWM signal frequency in Hz        */
#define PWM_DUTY_PERCENT 50U    /* PWM duty cycle (0-100)            */

int main(void)
{
    /* ── Initialize LED on PA5 (output, active-low) ── */
    led_init();

    /* ── Initialize TIM2-based hardware delay ── */
    timer_init();

    /* ── Initialize PWM on PA6 via TIM3 CH1 at 1 kHz ── */
    pwm_init(PWM_FREQUENCY_HZ);

    /* ── Set duty cycle to 50% ── */
    pwm_setSignal(PWM_DUTY_PERCENT);

    /* ── Start PWM — runs autonomously in hardware from this point ── */
    pwm_start();

    /* ── Main loop: blink LED every 500 ms using hardware timer ── */
    while (1)
    {
        /*
         * timer_delay_ms blocks here for 500 ms using TIM2.
         * During this time, TIM3 keeps generating the PWM signal
         * without any CPU intervention.
         */
        timer_delay_ms(BLINK_PERIOD_MS);
        led_toggle();
    }
}
