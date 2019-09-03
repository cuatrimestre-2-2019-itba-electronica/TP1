/***************************************************************************//**
  @file     display.h
  @brief    Display driver
  @author   Arturo
 ******************************************************************************/

#ifndef _7SEGDISP_H_
#define _7SEGDISP_H_

#include "gpio.h"
#include <stdbool.h>
#include <stdint.h>

//*************************IRQ****************************
/**
 * @brief when its called change de 7seg chosen
 */
void IrqMultiplexor(void);
void IrqBrightness(void);
void IrqAllInclusive(void);
//*************************END_IRQ****************************

//********************************************************
/**
 * @brief set up  the pins for 7seg display, as output
 * @param _pinxxxx the pin for each led of the 7seg. ej PORTNUM2PIN(PE,26)
 * @param _pinSexx the pin of the mux
 * @param SysTickFrec polling frequency of systich in Hz
 */
bool display_init(uint8_t _pinCsGa,uint8_t _pinCsGb,uint8_t _pinCsGc,uint8_t _pinCsGd,uint8_t _pinCsGe,uint8_t _pinCsGf,uint8_t _pinCsGg,uint8_t _pinCsGdp,uint8_t _pinSe10,uint8_t _pinCsSe11,uint32_t _SysTickFrec); // Init display

//TODO setter
// getter


#endif // _DISPLAY_H_
