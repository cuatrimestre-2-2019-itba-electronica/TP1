/***************************************************************************//**
  @file     App.c
  @brief    Application functions
  @author   Nicolás Magliola
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <assert.h>


#include "fsm.h"

#include "database.h"




#include "board.h"
#include "gpio.h"
#include "mygpio.h"
#include "8DigitsDisplay.h"
#include "3LedDsip.h"
#include "SysTick.h"
#include"encoder.h"


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

static void delayLoop(uint32_t veces);


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/* Función que se llama 1 vez, al comienzo del programa */
void App_Init (void)
{
	SysTick_Init();
	//_7SegDisp_display_init();
	_8DigitDisplay_init();
	_3LedDisp_dispInit();
	encoder_init();

}

/* Función que se llama constantemente en un ciclo infinito */

void App_Run (void)
{
//	for(int i=0;i<10;i++){
//
//		for(int j=0;j<4;j++){
//			_7SegDisp_setDigit(j,i);
//		}
//
//		//7SegDisp_setBright(i);
//		delayLoop(13947000);
//	}
//	delayLoop(13947000);
//	for(int i=0;i<4;i++){
//		_7SegDisp_setBright(i);
//		_7SegDisp_setCursor(i);
//		_7SegDisp_updateCursor();
//		delayLoop(13947000);
//	}
//	_7SegDisp_clearCursor();
//	delayLoop(13947000);
//
//	for(int i=0;i<3;i++){
//		_3LedDisp_setLed(i,true);
//		delayLoop(13947000);
//	}
//	for(int i=0;i<3;i++){
//			_3LedDisp_setLed(i,false);
//			delayLoop(13947000);
////		}
//	_8DigitDisplay_PinMode(true);
//	_8DigitDisplay_cursorOn();
//	_8DigitDisplay_SetCursorPos(4);

//	for(int i=0;i<8;i++){
//		_8DigitDisplay_cursorOn();
//		_8DigitDisplay_append(i);
//
//		delayLoop(13947000);
//
//	}
//	_8DigitDisplay_reset();


//	delayLoop(13947000);
//	_8DigitDisplay_cursorOff();
//	delayLoop(13947000);
//	_8DigitDisplay_cursorOn();
//	delayLoop(13947000);
//	//_8DigitDisplay_cursorOff();
//	_8DigitDisplay_SetCursorPos(1);
//	delayLoop(13947000);
//	_8DigitDisplay_SetCharInCursorPos(8);
//	delayLoop(13947000);
//	_8DigitDisplay_SetCursorPosOnScrenn();
////	delayLoop(13947000);
//	_8DigitDisplay_SetCursorPos2End();
//	_8DigitDisplay_SetCursorPosOnScrenn();
//	delayLoop(13947000);
//	for(int i=0;i<4;i++){
//		_8DigitDisplay_SetBright(i);
//		delayLoop(13947000);
//
//	}
//
//	for(int i=0;i<10;i++){
//	 _8DigitDisplay_ShiftCursorLeft();
//	 _8DigitDisplay_SetCursorPosOnScrenn();
//	 delayLoop(13947000/2);
//	}
//	_8DigitDisplay_PinMode(false);
//	delayLoop(13947000);
//	_8DigitDisplay_reset();








	uint8_t ID[3] = {0,0,0};
	uint8_t PIN[3] = {4,5,9};
	database_append(database_get_hash(ID, 3), database_get_hash(PIN,3));
	uint8_t ID1[3] = {4,2,3};
	uint8_t PIN1[3] = {4,5,6};
	database_append(database_get_hash(ID1, 3), database_get_hash(PIN1,3));
	uint8_t ID2[3] = {2,2,3};
	uint8_t PIN2[3] = {3,3,1};
	database_append(database_get_hash(ID2, 3), database_get_hash(PIN2,3));
	FSM * machine  = FSM__create();
	while(!FSM_cycle(machine));


}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static void delayLoop(uint32_t veces)
{

	while (veces--);
}


/*******************************************************************************
 ******************************************************************************/
