/***************************************************************************//**
  @file     8DigitsDisplay.h
  @brief    Display 8 digits driver
  @author   Matias Pierdominici

 ******************************************************************************/

#ifndef _8DIGITSDISPLAY_H_
#define _8DIGITSDISPLAY_H_

#include <stdbool.h>
#include <stdint.h>

#define AMAUNT_DIGITS_8_DISPLAY 8 //cantidad de digitos del display emulado

void _8DigitDisplay_init(void);
void _8DigitDisplay_reset(void);
void _8DigitDisplay_append(uint8_t num);
void _8DigitDisplay_cursorOn(void);
void _8DigitDisplay_cursorOff(void);
bool _8DigitDisplay_SetCursorPos(uint8_t pos);
uint8_t _8DigitDisplay_GetCursorPos(void);
void _8DigitDisplay_SetCharInCursorPos(uint8_t num);
void _8DigitDisplay_SetCursorPos2End(void);
void _8DigitDisplay_SetCursorPosOnScrenn(void);
void _8DigitDisplay_ShiftCursorLeft(void);
void _8DigitDisplay_PinMode(bool mode);
void _8DigitDisplay_SetBright(uint8_t b);






//scroll_on();
//scroll_off();   //pasa a mostrar solo el final de la palabra
//scroll(bool on);



////mode pin(on/off)

////////////////////////////////////////////////
//
//int get_size();
//uint8_t get_next_digit();



#endif
