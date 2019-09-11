#include "encoder.h"
#include "SysTick.h"

static int aState;
static int aLastState;

static int cState;
static int cLastState;

void doNothing(){}

int encoder_init(){
	counter = 0;
	callback_CW = doNothing;
	callback_CCW = doNothing;
	callback_SW_PRESS = doNothing;
	callback_SW_RELEASE = doNothing;

	MYgpioMode(PIN_ENCODER_A, INPUT);
	MYgpioMode(PIN_ENCODER_B, INPUT);
	MYgpioMode(PIN_ENCODER_C, INPUT);

	cLastState = MYgpioRead(PIN_ENCODER_C);
	aLastState = MYgpioRead(PIN_ENCODER_A);

	SysTick_Init(encoder_read);

	return 1;
}

void encoder_read(){
	encoder_read_POS();
	encoder_read_SW();
}

/*******************************************************************************
 * ENCODER FUNCTIONS
 ******************************************************************************/

void encoder_action(){

	// If B is HIGH -> CW
	if(MYgpioRead(PIN_ENCODER_B) == HIGH){
		counter ++;
		callback_CW();
	}
	// If not -> CCW
	else{
		counter --;
		callback_CCW();
	}
}

void encoder_read_POS(){
	aState = MYgpioRead(PIN_ENCODER_A);

	// If the state of A has changed
	if (aState != aLastState && aState == HIGH){
		encoder_action();
	}

	aLastState = aState;
}

/*******************************************************************************
 * SWITCH FUNCTIONS
 ******************************************************************************/

void encoder_read_SW(){
	cState = MYgpioRead(PIN_ENCODER_C);

	if(cState == LOW){
		if (cState != cLastState){
			callback_SW_PRESS();
		}
	}
	else{
		if (cState != cLastState){
			callback_SW_RELEASE();
		}
	}
	cLastState = cState;
}

/*******************************************************************************
 * GETTERS AND SETTERS
 ******************************************************************************/

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

void encoder_set_callback_SW_PRESS(void (*userCallback_SW_PRESS)(void)){
	callback_SW_PRESS = userCallback_SW_PRESS;
}

void encoder_set_callback_SW_RELEASE(void (*userCallback_SW_RELEASE)(void)){
	callback_SW_RELEASE = userCallback_SW_RELEASE;
}
