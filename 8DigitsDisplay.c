#include "8DigitsDisplay.h"
#include "7SegDisp.h"
static uint8_t data[AMAUNT_DIGITS_8_DISPLAY+DIGIT_AMOUNT-1]; //arreglo de los numores del display emulado, la posicion 0 es el mas significativo. ej 340 -> 3|4|0|..
uint8_t *_8digits;
static uint8_t cursorPosition=0;//posicion del cursor - dot
static int8_t lastDigitPos=-1;//posicion del ultimo digito del display - otambien tamano del display menos uno
static int8_t DispOffset=0;//ofeset para mover cambiar la ventana de lo que se ve en los 7seg- maximo ofset es 4



void _8DigitDisplay_reset(void){
	_7SegDisp_clearDisplay();
	for(int i=0;i<AMAUNT_DIGITS_8_DISPLAY+DIGIT_AMOUNT-1;i++){
		data[i]=_7DIGIT_BLANK;
	}
	cursorPosition=0;
	lastDigitPos=-1;
	DispOffset=0;
}

void _8DigitDisplay_init(void){
	_7SegDisp_display_init();
	_8DigitDisplay_reset();
	_8digits=data+(DIGIT_AMOUNT-1);

}

static void refresh7SegDisp(void){

for(int i=0;i<DIGIT_AMOUNT;i++){
	_7SegDisp_setDigit(i,data[DIGIT_AMOUNT-1+DispOffset-i]);

}
}

static bool shiftLeftDisp(void){

	if(DispOffset>AMAUNT_DIGITS_8_DISPLAY-1){
		DispOffset=AMAUNT_DIGITS_8_DISPLAY-1;
		refresh7SegDisp();
		return false;
	}else{

		refresh7SegDisp();
		DispOffset++;
		return true;

	}

}

static bool shiftRightDisp(void){
	DispOffset--;
	if(DispOffset<0){
		DispOffset=0;
		refresh7SegDisp();
		return false;
	}else{
		refresh7SegDisp();
		return true;
	}

}

void _8DigitDisplay_append(uint8_t num){
	lastDigitPos++;
	if(lastDigitPos>AMAUNT_DIGITS_8_DISPLAY-1){
		lastDigitPos=AMAUNT_DIGITS_8_DISPLAY-1;
	}

	_8digits[lastDigitPos]=num;

	shiftLeftDisp();



}

