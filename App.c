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
#include <gpio.h>


#include "fsm.h"

#include "database.h"




#include "board.h"
#include "gpio.h"
#include "8DigitsDisplay.h"
#include "3LedDsip.h"
#include "SysTick.h"
#include "encoder.h"
#include "magnetic_band.h"


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
	timerInit();
	//_7SegDisp_display_init();
	_8DigitDisplay_init();
	_3LedDisp_dispInit();
	encoder_init();
	init_mag_card();
}

/* Función que se llama constantemente en un ciclo infinito */

void App_Run (void)
{



	uint8_t ID[] = {4,5,1,7,6,6,0,1};
	uint8_t PIN[] = {4,5,9};
	database_append(database_get_hash(ID, 8), database_get_hash(PIN,3));
	uint8_t ID1[] = {3,7,6,6,3,6,4,5};
	uint8_t PIN1[] = {3,2,3,2};
	database_append(database_get_hash(ID1, 8), database_get_hash(PIN1,4));
	uint8_t ID2[] = {0,1,2,3,4,5,6,7};
	uint8_t PIN2[] = {5,5,5,5,5};
	database_append(database_get_hash(ID2, 8), database_get_hash(PIN2,5));
	FSM * machine  = FSM__create();
	while(!FSM_cycle(machine));


}


/*******************************************************************************
 ******************************************************************************/
