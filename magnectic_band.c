/*
 * magnectic_band.c
 *
 *  Created on: Sep 6, 2019
 *      Author: gonzalosilva
 */

#include "board.h"
#include "magnetic_band.h"
#include "gpio.h"
#include "mygpio.h"


static void mag_data (void);//se obtiene bit a bit la data de la tarjeta
static void reset_mag(void);//resetea todos los valores luego que la informacion haya sido enviada

static unsigned int counter = 0; //contador general
static unsigned int count = 0; //contador de cada caracter
static unsigned int data_send_counter = 0;//contador del envio de informacion, esta se envia caracter a caracter
static unsigned int parity = 0;
static bool after_SS = false;
static bool loaded = false; //si ya tengo informacion en el arreglo y no me la pidieron, este queda en 1
static uint8_t code[40];
static uint8_t card_character = 0;


void init_mag_card(void) {
    MYgpioMode(CARD_ENABLE, INPUT);
    //MYgpioIRQ(CARD_ENABLE, GPIO_IRQ_MODE_RISING_EDGE, reset_mag);

    MYgpioMode(CARD_CLOCK, INPUT);
    MYgpioIRQ(CARD_CLOCK, GPIO_IRQ_MODE_FALLING_EDGE, mag_data);

    MYgpioMode(CARD_DATA, INPUT);

    MYgpioMode(PIN_SW3, INPUT);//para pruebas
    MYgpioIRQ(PIN_SW3, GPIO_IRQ_MODE_FALLING_EDGE, get_data);
#warning sacar los dos switches
    MYgpioMode(PIN_SW2, INPUT);//para pruebas
        MYgpioIRQ(PIN_SW2, GPIO_IRQ_MODE_FALLING_EDGE, reset_mag);
}


void mag_data (void){
	if (!MYgpioRead(CARD_ENABLE) && loaded == false){ //si se esta pasando la tarjeta
		if(!after_SS){ //si todavia no se encontro el inicio de los caracteres de la tarjeta
			card_character = card_character >> 1;
			card_character |= (((uint8_t)(!MYgpioRead(CARD_DATA))) << 4);
			if(card_character == SS){
				after_SS = true;
				card_character = 0;
			}
		}
		else{ //una vez que se ecnontro el primer caracter (SS) empiezan a buscarse todos los restantes
			if (count < 4){
				card_character |= (((uint8_t)(!MYgpioRead(CARD_DATA))) << count);
				count++;
			}
			else if (count == 4){
				if(!MYgpioRead(CARD_DATA))
					parity++;
				count++;
			}
			else if (counter < 40){
				code[counter] = card_character;
				card_character = 0;
				counter++;
				count = 0;
			}
			if (code[counter-1] == ES){ //si el es final de la informacion se pone como cargado y ya no se vuelve a modificar hasta que se pida esta informacion
				loaded = true;
			}
		}
	}
}
//TODO: fijarse bien que informacion devolver, ahora devuelve todo el arreglo
#warning no tiene que ser void, tiene que devolver uint8, ahora esta para debug
void get_data(void){
	if (data_send_counter < counter && loaded == true){
		data_send_counter++;
		//return code[data_send_counter];
	}
	else{
		reset_mag();
		//return 255;
	}
}

bool is_loaded(void){
	return loaded;
}

void reset_mag(void){
	data_send_counter = 0;
	counter = 0;
	count = 0;
	loaded = false;
	card_character = 0;
	after_SS = false;
	parity = 0;
	for (int i = 0; i < 40; i++)
		code[i] = 0;
}



