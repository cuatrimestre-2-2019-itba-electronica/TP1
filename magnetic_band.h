/*
 * magnetic_band.h
 *
 *  Created on: Sep 7, 2019
 *      Author: gonzalosilva
 */

#ifndef MAGNETIC_BAND_H_
#define MAGNETIC_BAND_H_




  ////////////////////////characters of the magnectic card//////////////////////////////
 ///********************************************************************************///
//////////////////////////////////////////////////////////////////////////////////////
#define SS				11
#define FS				13
#define ES				15
  ////////////////////////////////////////////////////////////////////////////////////
 ///******************************************************************************///
////////////////////////////////////////////////////////////////////////////////////
#define CARD_DATA		PORTNUM2PIN(PC, 5)
#define CARD_CLOCK		PORTNUM2PIN(PC, 7)
#define CARD_ENABLE		PORTNUM2PIN(PC, 0)
#define PIN_SW3			PORTNUM2PIN(PA,4)//prueba
#define PIN_SW2			PORTNUM2PIN(PC,6)//prueba
  ////////////////////////////////////////////////////////////////////////////////////
 ///******************************************************************************///
////////////////////////////////////////////////////////////////////////////////////
void init_mag_card(void);//inicializa los pines que usara la tarjeta magetica
void get_data(void); //devuelve caracter a caracter la informacion
bool is_loaded(void); //indica si hay informacion que no se uso



#endif /* MAGNETIC_BAND_H_ */
