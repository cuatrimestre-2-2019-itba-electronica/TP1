#include "encoder.h"

int encoder_init(){
	counter = 0;
	callback_CW = NULL;
	callback_CCW = NULL;
	callback_SW = NULL;

	if(gpioIRQ(PIN_ENCODER_A, 10, &encoder_action_CCW()));
		return 0;
	if(gpioIRQ(PIN_ENCODER_B, 10, &encoder_action_CW()));
			return 0;
	if(gpioIRQ(PIN_ENCODER_C, 10, &encoder_action_SW()));
			return 0;

	return 1;
}

int encoder_get_counter(){
	return counter;
}

void encoder_set_counter(int userCounter){
	counter = userCounter;
}

void encoder_set_callback_CW(void (*userCallback_CW)(void)){
	callback_CW = userCallback_CW;
}

void encoder_set_callback_CCW(void (*userCallback_CCW)(void)){
	callback_CCW = userCallback_CCW;
}

void encoder_set_callback_SW(void (*userCallback_SW)(void)){
	callback_SW = userCallback_SW;
}

void encoder_action_CW(){
	counter += 1;
	callback_CW();
}

void encoder_action_CWW(){
	counter -=1;
	callback_CWW();
}

void encoder_action_SW(){
	callback_SW();
}