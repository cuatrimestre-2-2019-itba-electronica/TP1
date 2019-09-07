/***************************************************************************//**
  @file     board.h
  @brief    Board management
  @author   Nicolás Magliola
 ******************************************************************************/

#ifndef _BOARD_H_
#define _BOARD_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "gpio.h"


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

/***** BOARD defines **********************************************************/
// 7segDsip Pins
#define PIN_CSEGA 	PORTNUM2PIN(PD,1)
#define PIN_CSEGB 	PORTNUM2PIN(PD,3)
#define PIN_CSEGC 	PORTNUM2PIN(PD,2)
#define PIN_CSEGD 	PORTNUM2PIN(PD,0)
#define PIN_CSEGE 	PORTNUM2PIN(PC,4)
#define PIN_CSEGF	PORTNUM2PIN(PC,5)
#define PIN_CSEGG 	PORTNUM2PIN(PC,3)
#define PIN_CSEGDP 	PORTNUM2PIN(PC,2)
#define PIN_SE10 	PORTNUM2PIN(PB,23)
#define PIN_SE11 	PORTNUM2PIN(PA,2)

// On Board User LEDs
#define PIN_LED_RED	PORTNUM2PIN(PB,22)     // ???
#define PIN_LED_GREEN	PORTNUM2PIN(PE,26)  // ???
#define PIN_LED_BLUE	PORTNUM2PIN(PB,21) // PTB21
#define LED_ACTIVE	LOW

// On Board User Switches
#define PIN_SW2 PORTNUM2PIN(PC,6)      // ???
#define PIN_SW3 PORTNUM2PIN(PA,4)     // ???

/*******************************************************************************
 ******************************************************************************/

#endif // _BOARD_H_
