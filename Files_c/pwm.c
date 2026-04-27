/**
 * @file pwm.c
 * @brief PWM module — signal generation using TIM3, Channel 1, on PA6.
 *
 * Hardware mapping (STM32F411RE NUCLEO-64):
 *   Timer   : TIM3  (APB1, 50 MHz default)
 *   Channel : 1
 *   Pin     : PA6   (AF2 = TIM3_CH1, CN10 pin 13)
 *
 * Configuration order is critical for correct PWM operation:
 *   1. GPIO port clock + alternate function (MODER + AFR)
 *   2. Timer clock enable
 *   3. Frequency configuration (PSC + ARR)
 *   4. Compare mode = PWM Mode 1 (CCMR, OC1M = 110b = 6)
 *   5. Initial CCR = 0
 *   6. Enable ARR preload (CR1.ARPE) so ARR is buffered
 *   7. pwm_start: enable channel (CCER) + start counter (CR1.CEN)
 *
 * @author Adal Aguirre
 * @date 04/2026
 */

#include "pwm.h"
#include "SRS_TIM_DRIVER.h"
#include "SRS_GPIO_DRIVER.h"

/* ─── Hardware mapping constants ───────────────────────────────────────────── */

#define PWM_TIMER    tim3   /* TIM3, APB1 */
#define PWM_CHANNEL  1      /* TIM3_CH1   */
#define PWM_PORT     A      /* GPIOA      */
#define PWM_PIN      6      /* PA6        */
#define PWM_AF       2      /* AF2 = TIM3 on PA6 (STM32F411RE datasheet Table 9) */

/*
 * PWM Mode 1 = 6 (binary 110).
 * In this mode: output is HIGH while CNT < CCR, LOW when CNT >= CCR.
 * This is the standard PWM mode used in embedded systems.
 */
#define PWM_MODE_1   6

/* ─── Public functions ─────────────────────────────────────────────────────── */

uint32_t pwm_init(uint32_t freq_hz)
{
    if (freq_hz == 0) return 1;

    /* ── Step 1: Configure PA6 as alternate function (TIM3_CH1 = AF2) ── */
    gpio_init();
    gpio_initPort(PWM_PORT);               /* Enable GPIOA clock           */
    gpio_setAlternateFunction(PWM_PORT, PWM_PIN, PWM_AF); /* MODER=10, AFR=AF2 */

    /* ── Step 2: Initialize TIM3 and enable its APB1 clock ── */
    tim_init();
    if (tim_initTimer(PWM_TIMER) != 0) return 1;

    /* ── Step 3: Set PWM frequency (calculates PSC and ARR) ── */
    if (tim_setTimerFreq(PWM_TIMER, freq_hz) != 0) return 1;

    /* ── Step 4: Configure channel 1 in PWM Mode 1 ── */
    /*
     * tim_setTimerCompareMode writes OC1M bits in CCMR1 and enables
     * the output compare preload (OC1PE) so CCR changes take effect
     * at the start of the next period, not mid-cycle.
     */
    if (tim_setTimerCompareChannelMode(PWM_TIMER, PWM_CHANNEL, PWM_MODE_1) != 0) return 1;

    /* ── Step 5: Set initial duty cycle to 0% (CCR1 = 0) ── */
    if (tim_setTimerCompareChannelValue(PWM_TIMER, PWM_CHANNEL, 0) != 0) return 1;

    /*
     * ── Step 6: Enable ARR preload (CR1.ARPE = bit 7) ──
     *
     * Without this, writing a new ARR value takes effect immediately,
     * which can cause the counter to skip or glitch mid-period.
     * With ARPE set, the new ARR is loaded only at the next update event.
     *
     * TIM_ar[] is declared extern in SRS_TIM_DRIVER.h — we access it
     * directly here because the TIM driver does not expose a CR1 setter.
     * This is the only register access in this module.
     */
    TIM_ar[PWM_TIMER]->CR1 |= (1U << 7);  /* ARPE = 1 */

    return 0;
}

uint32_t pwm_setSignal(uint8_t duty)
{
    if (duty > 100) return 1;

    /*
     * Calculate CCR from duty cycle percentage:
     *   CCR = (ARR + 1) * duty / 100
     *
     * Example: ARR = 999, duty = 50%
     *   CCR = 1000 * 50 / 100 = 500
     *   → HIGH for ticks 0–499, LOW for ticks 500–999 → 50%
     *
     * We read ARR from the timer register to keep this calculation
     * correct regardless of which frequency was configured.
     */
    uint32_t arr = TIM_ar[PWM_TIMER]->ARR;
    uint32_t ccr = ((arr + 1) * duty) / 100;

    return tim_setTimerCompareChannelValue(PWM_TIMER, PWM_CHANNEL, ccr);
}

uint32_t pwm_start(void)
{
    /* Enable compare channel output (CCER.CC1E = bit 0) */
    if (tim_enableTimerCompareChannel(PWM_TIMER, PWM_CHANNEL) != 0) return 1;

    /* Start timer counter (CR1.CEN = bit 0) */
    if (tim_enableTimer(PWM_TIMER) != 0) return 1;

    return 0;
}

uint32_t pwm_stop(void)
{
    /* Disable compare channel output first */
    if (tim_disableTimerCompareChannel(PWM_TIMER, PWM_CHANNEL) != 0) return 1;

    /* Stop timer counter */
    if (tim_disableTimer(PWM_TIMER) != 0) return 1;

    return 0;
}
