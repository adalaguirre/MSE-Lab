/**
 * @file pwm.h
 * @brief PWM module — signal generation using TIM3, Channel 1, on PA6.
 *
 * Generates a PWM signal by combining the GPIO driver (alternate function
 * configuration) and the TIM driver (compare channel in PWM mode).
 *
 * Hardware mapping (STM32F411RE NUCLEO-64):
 *   Timer  : TIM3
 *   Channel: 1
 *   Pin    : PA6  (AF2 = TIM3_CH1)
 *   Header : CN10, pin 13  ← connect oscilloscope probe here
 *
 * @author Adal Aguirre
 * @date 04/2026
 */

#ifndef __PWM_H__
#define __PWM_H__

#include <stdint.h>

/**
 * @brief Initializes the PWM module at the given frequency.
 *
 * Configures PA6 in alternate function mode (AF2 = TIM3_CH1),
 * initializes TIM3, sets the PWM frequency, configures channel 1
 * in PWM Mode 1, and sets initial duty cycle to 0%.
 *
 * @param freq_hz  Desired PWM frequency in Hz. Must be > 0.
 * @return 0 on success, 1 on invalid input or configuration error.
 */
uint32_t pwm_init(uint32_t freq_hz);

/**
 * @brief Sets the PWM duty cycle.
 *
 * Calculates CCR1 = (ARR + 1) * duty / 100 and writes it to TIM3->CCR1.
 * Can be called while the PWM is running (updated on next period).
 *
 * @param duty  Duty cycle percentage (0–100).
 * @return 0 on success, 1 if duty > 100.
 */
uint32_t pwm_setSignal(uint8_t duty);

/**
 * @brief Starts PWM output on TIM3 Channel 1.
 *
 * Enables the compare channel (CCER) and starts the timer counter (CR1.CEN).
 *
 * @return 0 on success, 1 on error.
 */
uint32_t pwm_start(void);

/**
 * @brief Stops PWM output on TIM3 Channel 1.
 *
 * Disables the compare channel and stops the timer counter.
 *
 * @return 0 on success, 1 on error.
 */
uint32_t pwm_stop(void);

#endif /* __PWM_H__ */
