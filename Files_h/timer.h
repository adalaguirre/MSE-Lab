/**
 * @file timer.h
 * @brief Timer module — hardware delay generation using TIM2.
 *
 * Provides a blocking millisecond delay using the TIM driver.
 * Does NOT use software loops — delay accuracy depends on hardware timer.
 *
 * @author Adal Aguirre
 * @date 04/2026
 */

#ifndef __TIMER_H__
#define __TIMER_H__

#include <stdint.h>

/**
 * @brief Initializes the Timer module.
 *
 * Calls tim_init() to populate the TIM address array, then enables
 * the clock for TIM2 via tim_initTimer(). Must be called before
 * timer_delay_ms().
 */
void timer_init(void);

/**
 * @brief Blocks execution for the specified number of milliseconds.
 *
 * Configures TIM2 with a 1ms tick (PSC = CLK/1000 - 1) and an
 * ARR equal to ms_duration - 1. Starts the timer and polls the
 * Update Interrupt Flag (UIF) until the timer overflows, then stops.
 *
 * @param ms_duration  Delay in milliseconds. Must be > 0.
 * @return 0 on success, 1 if ms_duration is 0 or timer config fails.
 */
uint32_t timer_delay_ms(uint32_t ms_duration);

#endif /* __TIMER_H__ */
