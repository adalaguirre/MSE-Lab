/**
 * @file SRS_TIM_DRIVER.c
 * @brief Module that manipulates the timers that the 
 * development board has in its disposal.
 * 
 * The user may use multiple functions to indicate the development board
 * which timer it will use.
 *
 * @author Steven McClellan
 * @date 04/15/2026
 *
 */
/*** INCLUDES ***/
#include <stdint.h>
#include "stm32f4xx.h"
#include "SRS_TIM_DRIVER.h"



// Declaring universal array for TIM addresses
TIM_TypeDef* TIM_ar[SIZE];

/* This register will initialize all TIM ports in it's default state*/
void tim_init(void){
    TIM_ar[0] = TIM1;
    TIM_ar[1] = TIM2;
    TIM_ar[2] = TIM3;
    TIM_ar[3] = TIM4;
    TIM_ar[4] = TIM5;
    TIM_ar[5] = TIM9;
    TIM_ar[6] = TIM10;
    TIM_ar[7] = TIM11;
}

// Internal fucntion to decide which value of timer will be used
static uint32_t tim_getClock(tim_g tim){
    if (tim == tim1 || tim == tim9 || tim == tim10 || tim == tim11){
        return 16000000; // APB2 timers — HSI default 16MHz
    } 
    else if (tim == tim2 || tim == tim3 || tim == tim4 || tim == tim5){
        return 16000000; // APB1 timers — HSI default 16MHz
    }
    return 0;
}


/* This function shall enable clocking for a specified GPIO port */
uint32_t tim_initTimer(tim_g tim){
    
    // If the input tim is out of the valid range the function fails
    if(tim >= SIZE) return 1; // Invalid port return

    // This multi-generational if sequence especifies which GPIO port shall enable
    // clocking depending on the input
    if(tim == tim1)       RCC->APB2ENR |= (1U << 0);  // Clock enabled for TIM1
    else if(tim == tim2)  RCC->APB1ENR |= (1U << 0);  // Clock enabled for TIM2
    else if(tim == tim3)  RCC->APB1ENR |= (1U << 1);  // Clock enabled for TIM3
    else if(tim == tim4)  RCC->APB1ENR |= (1U << 2);  // Clock enabled for TIM4
    else if(tim == tim5)  RCC->APB1ENR |= (1U << 3);  // Clock enabled for TIM5
    else if(tim == tim9)  RCC->APB2ENR |= (1U << 16); // Clock enabled for TIM9
    else if(tim == tim10) RCC->APB2ENR |= (1U << 17); // Clock enabled for TIM10
    else if(tim == tim11) RCC->APB2ENR |= (1U << 18); // Clock enabled for TIM11
    else return 1;

    return 0;
}

// This fuction sets the PSC and ARR given an input of milisenconds 
uint32_t tim_setTimerMs(tim_g tim, uint32_t ms_duration){
    
    // If the input tim is out of the valid range the function fails 
    if (tim >= SIZE) return 1;

    //Internal variable to set a base frequency
    uint32_t tim_clk = tim_getClock(tim);
    if (tim_clk == 0) return 1;
    
    // Set individual variable for prescaler to get 1 ms tick
    uint32_t PSC_value = (tim_clk / 1000) - 1;

    // Assign PSC_value to the actual PSC 
    TIM_ar[tim]->PSC = PSC_value;

    // Assign ARR value to an indepent varaible to check for overflow
    uint32_t ARR_value = ms_duration - 1;
    
    // If condition that makes sure that fails if Timers aside 2 and 5 get a value higher than 16 bits
    if (ARR_value > 0xFFFF && tim != tim2 && tim != tim5) return 1;

    //Set auto-reaload for desired duration
    TIM_ar[tim]->ARR = ARR_value;
    
    //Reset counter
    TIM_ar[tim]->CNT = 0;
    
    return 0;
}

// This function calculates the PSC and ARR given an input on frequency
uint32_t tim_setTimerFreq(tim_g tim, uint32_t freq){

    // If the input tim is out of the valid range the function fails 
    if (tim >= SIZE || freq == 0) return 1;

    //Internal variable to set a base frequency
    uint32_t tim_clk = tim_getClock(tim);
    if (tim_clk == 0) return 1;

    // Calculate total ticks
    uint32_t ticks = tim_clk / freq;

    // Set individual variable for a base value prescaler
    uint32_t PSC_value, ARR_value;

    // If condition that if Timer 2 or 5 are used then assigns set vales to ARR and PSC
    if(tim == tim2 || tim == tim5){
        PSC_value = 0;
        ARR_value = ticks - 1;
    } else{

        // Divides the total ticks by the max value of 16-bits
        PSC_value = (ticks + 65536) / 65536;

        // If condition that detects bit overflow on PSC
        if(PSC_value > 0xFFFF) return 1; 

        // Calculates ARR value
        ARR_value = (ticks / (PSC_value + 1)) - 1;

        // If condition that detects bit overflow on ARR
        if(ARR_value > 0xFFFF) return 1; 
    }

    // Sets calculated values to both PSC and ARR 
    TIM_ar[tim]->PSC = PSC_value;
    TIM_ar[tim]->ARR = ARR_value;
    
    // Updating EGR after assigning PSC and ARR values
    TIM_ar[tim]->EGR |= (1U << 0);

    return 0;
}

uint32_t tim_enableTimer(tim_g tim){
    if (tim >= SIZE) return 1;

    // Reset counter
    TIM_ar[tim]->CNT = 0;

    // Force update to load PSC and ARR
    TIM_ar[tim]->EGR |= (1U << 0);

    // Enable counter
    TIM_ar[tim]->CR1 |= (1U << 0);

    return 0;
    
}uint32_t tim_enableTimer(tim_g tim){
    if (tim >= SIZE) return 1;

    // Reset counter
    TIM_ar[tim]->CNT = 0;

    // Enable counter
    TIM_ar[tim]->CR1 |= (1U << 0);

    return 0;
}

uint32_t tim_disableTimer(tim_g tim){
    
    // If the input tim is out of the valid range the function fails 
    if (tim >= SIZE) return 1;

    // Disable counter
    TIM_ar[tim]->CR1 &= ~(1U << 0);

    return 0;
}

uint32_t tim_waitTimer(tim_g tim){

    // If the input tim is out of the valid range the function fails 
    if (tim >= SIZE) return 1;

    // If timer is not enabled it fails the function
    if (!(TIM_ar[tim]->CR1 & (1U << 0))) return 1;

    // Timeout variable to avoid deadlocks
    uint32_t timeout = 50000000;

    // While loop that waits until the timer overflows
    while (!(TIM_ar[tim]->SR & TIM_SR_UIF)){
        // If condition that continues to substrack timeout to avoid deadlock
        if (--timeout == 0) return 1;
}

    // Prepares timer for the next cycle and prevents instant return
    TIM_ar[tim]->SR &= ~TIM_SR_UIF;

    return 0;
}

uint32_t tim_setTimerCompareChannelValue(tim_g tim, uint8_t channel, uint32_t value){

    // If the input tim is out of the valid range the function fails 
    if (tim >= SIZE) return 1;
    // If the input channel us out of the valid range the function fails
    if (channel < 1 || channel > 4) return 1;

    // Timer channel limitations
    if ((tim == tim10 || tim == tim11) && channel != 1) return 1;
    if (tim == tim9 && channel > 2) return 1;


    // If condition that checks for 16-bit limit
    if ((value > 0xFFFF) && (tim != tim2 && tim != tim5)) return 1;

    // Switch that assigns the value to the correct channel
    switch(channel){
        case 1: TIM_ar[tim]->CCR1 = value; break;
        case 2: TIM_ar[tim]->CCR2 = value; break;
        case 3: TIM_ar[tim]->CCR3 = value; break;
        case 4: TIM_ar[tim]->CCR4 = value; break;
    }

    return 0;
}

uint32_t tim_setTimerCompareChannelMode(tim_g tim, uint8_t channel, uint8_t mode){

    // If the input tim is out of the valid range the function fails 
    if (tim >= SIZE) return 1;
    // If the input channel us out of the valid range the function fails
    if (channel < 1 || channel > 4) return 1;
    // If the input mode us out of the valid range the function fails
    if (mode > 7) return 1;

    // Timer channel limitations
    if ((tim == tim10 || tim == tim11) && channel != 1) return 1;
    if (tim == tim9 && channel > 2) return 1;

    // Volatile variable that points to the address of each channel 
    volatile uint32_t *ccmr;
    uint8_t shift;
    uint8_t preload_shift;

    if (channel == 1){
        ccmr = &TIM_ar[tim]->CCMR1;
        shift = 4;
    }
    else if (channel == 2){
        ccmr = &TIM_ar[tim]->CCMR1;
        shift = 12;
    }
    else if (channel == 3){
        ccmr = &TIM_ar[tim]->CCMR2;
        shift = 4;
    }
    else { // channel 4
        ccmr = &TIM_ar[tim]->CCMR2;
        shift = 12;
    }

    preload_shift = shift - 1;
    // Clear previous mode
    *ccmr &= ~(7U << shift);

    // Set new mode
    *ccmr |= (mode << shift);

    // Enable preload (OCxPE)
    *ccmr |= (1U << preload_shift);

    return 0;
}

uint32_t tim_enableTimerCompareChannel(tim_g tim, uint8_t channel){

    // If the input tim is out of the valid range the function fails 
    if (tim >= SIZE) return 1;
    // If the input channel us out of the valid range the function fails
    if (channel < 1 || channel > 4) return 1;

    // Timer channel limitations
    if ((tim == tim10 || tim == tim11) && channel != 1) return 1;
    if (tim == tim9 && channel > 2) return 1;


    // Calculate bit position for CCxE
    uint8_t bit = (channel - 1) * 4;

    // Enable channel (CCxE = 1)
    TIM_ar[tim]->CCER |= (1U << bit);

    return 0;
}

uint32_t tim_disableTimerCompareChannel(tim_g tim, uint8_t channel){

    // If the input tim is out of the valid range the function fails
    if (tim >= SIZE) return 1;
    // If the input channel us out of the valid range the function fails
    if (channel < 1 || channel > 4) return 1;

    // Timer channel limitations
    if ((tim == tim10 || tim == tim11) && channel != 1) return 1;
    if (tim == tim9 && channel > 2) return 1;

    // Calculate bit position for CCxE
    uint8_t bit = (channel - 1) * 4;

    // Disable channel (CCxE = 0)
    TIM_ar[tim]->CCER &= ~(1U << bit);

    return 0;
}