/***************************************************************************//**
  @file     3LedDisp.h
  @brief    Leds driver
  @author   Matias Pierdominici
 ******************************************************************************/

#ifndef _SYSTICK_H_
#define _SYSTICK_H_



#include <stdbool.h>




#define SYSTICK_ISR_FREQUENCY_HZ 100000L
#define NUMBER_OF_CALLBACKS 10
typedef void (*SysTick_funcallback)(void);

/**
 * @brief Initialize SysTic driver
 * @return Initialization and registration succeed
 */
bool SysTick_Init (void);
bool SysTick_append(SysTick_funcallback func);

/*******************************************************************************
 ******************************************************************************/

#endif // _SYSTICK_H_