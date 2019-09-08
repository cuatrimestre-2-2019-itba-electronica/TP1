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







//set_display_word(const char * word);

//scroll_on();
//scroll_off();   //pasa a mostrar solo el final de la palabra
//scroll(bool on);
//
//
////curosr interno NO DOT
//append_char(char c);
//
//
////dot
//cursor_on();
//cursor_off();
//set_cursor_pos();
//get_cursor_pos();
//set_char_in_pos();
//set_cursor_to_end();//al numero menos significativo y devuelve la la posicion de este
////en el arreglo la posicion cero es el mas significativo
////cursor left si llego a los extremos me quedo ahi
////cursor right
////mode pin(on/off)
////reset
////preprara caraccter en blanco
////////////////////////////////////////////////
//
//int get_size();
//uint8_t get_next_digit();



#endif
