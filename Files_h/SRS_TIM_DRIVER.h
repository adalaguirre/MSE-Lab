/**
 * @file SRS_TIM_DRIVER.h
 * @brief Module that manipulates the components that the 
 * development board may use.
 * 
 * The user may use multiple functions to indicate the development board
 * which component it will use.
 *
 * @author Steven McClellan
 * @date 04/25/2026
 *
 */
/*** INCLUDES ***/
#ifndef __SRS_TIM_DRIVER_H__
#define __SRS_TIM_DRIVER_H__


#include <stdint.h>
#include "stm32f4xx.h"

/* Declaring enum for ease of access from other files*/
typedef enum tim{
    tim1,
    tim2,
    tim3,
    tim4,
    tim5,
    tim9,
    tim10,
    tim11,
    SIZE
}tim_g;

/* Declaring universal array and size of array for TIM addresses*/
extern TIM_TypeDef* TIM_ar[SIZE];

// Declaring all functions

/* This register will initialize all GPIO ports in it's default state */
void tim_init(void);

/* This function shall enable clocking for a specified GPIO port */
uint32_t tim_initTimer(tim_g tim);

/* This function allows the configuration of pin direction and mode */
uint32_t tim_setTimerMs(tim_g tim, uint32_t ms_duration);

/* This function will set a specified pin into a HIGH value state */
uint32_t tim_setTimerFreq(tim_g port, uint32_t freq);

/* This function will set a specified pin into a LOW value state */
uint32_t tim_enableTimer(tim_g tim);

/* This function will set a specified pin into it's reversed value state */
uint32_t tim_disableTimer(tim_g tim);

/* This fucntion will retrieve a specified pin value state */
uint32_t tim_waitTimer(tim_g port);


uint32_t tim_setTimerCompareChannelValue(tim_g port, uint8_t channel, uint32_t value);

uint32_t tim_setTimerCompareChannelMode(tim_g port, uint8_t channel, uint8_t mode);

uint32_t tim_enableTimerCompareChannel(tim_g tim, uint8_t channel);

uint32_t tim_disableTimerCompareChannel(tim_g tim, uint8_t channel);
#endif /* __SRS_TIM_DRIVER_H__ */
