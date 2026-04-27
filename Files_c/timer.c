/**
 * @file timer.c
 * @brief Timer module — hardware delay generation using TIM2.
 *
 * Uses the TIM driver internally. No direct register access here —
 * all hardware interaction goes through SRS_TIM_DRIVER functions.
 *
 * TIM2 is chosen because it is a 32-bit timer on the STM32F411,
 * allowing ARR values up to 0xFFFFFFFF without overflow for long delays.
 *
 * @author Adal Aguirre
 * @date 04/2026
 */

#include "timer.h"
#include "SRS_TIM_DRIVER.h"

/* TIM2 is used for all blocking delays in this module */
#define DELAY_TIMER  tim2

/* ─── Public functions ─────────────────────────────────────────────────────── */

void timer_init(void)
{
    /* Populate TIM_ar[] with CMSIS base addresses */
    tim_init();

    /* Enable APB1 clock for TIM2 */
    tim_initTimer(DELAY_TIMER);
}

uint32_t timer_delay_ms(uint32_t ms_duration)
{
    /* A delay of 0 ms is a no-op — not an error, just return immediately */
    if (ms_duration == 0) return 0;

    /*
     * Configure TIM2 for ms_duration milliseconds.
     *
     * tim_setTimerMs sets:
     *   PSC = (CLK / 1000) - 1  →  1 tick = 1 ms
     *   ARR = ms_duration - 1   →  overflow after ms_duration ticks
     *   CNT = 0                 →  reset counter
     *
     * TIM2 is APB1: CLK = 50 MHz (default config on F411 NUCLEO)
     * PSC = (50,000,000 / 1000) - 1 = 49,999
     */
    if (tim_setTimerMs(DELAY_TIMER, ms_duration) != 0) return 1;

    /* Start the timer: resets CNT, forces EGR update, sets CR1.CEN */
    tim_enableTimer(DELAY_TIMER);

    /*
     * Block here until TIM2 overflows.
     * tim_waitTimer polls SR.UIF and clears it when done.
     * It has an internal timeout to avoid infinite deadlock.
     */
    uint32_t result = tim_waitTimer(DELAY_TIMER);

    /* Stop the timer — do not leave it running between calls */
    tim_disableTimer(DELAY_TIMER);

    return result;
}
