#include "7SegDisp.h"
#include <stdbool.h>
#include<stdint.h>
#include"SysTick.h"
/* cseg register(?) */
static uint8_t cseg[4];//pin values(HIGH O LOW) for each 7seg
static uint8_t pinCsGa;
static uint8_t pinCsGb;
static uint8_t pinCsGc;
static uint8_t pinCsGd;
static uint8_t pinCsGe;
static uint8_t pinCsGf;
static uint8_t pinCsGg;
static uint8_t pinCsGdp;
static uint8_t pinSe10;
static uint8_t pinSe11;
static uint32_t SysTickFrec;
static uint8_t current7Seg=0;//7 segmento que se esta senalando en el momento
static uint32_t prescalerMultiplexor;
static uint32_t prescalerPwm;
static uint8_t brightLevel=4;

/* Masks */

#define display_CSEGA_Pos          	0U
#define display_CSEGA_Msk 			(1UL << display_CSEGA_Pos)

#define display_CSEGB_Pos          	1U
#define display_CSEGB_Msk 			(1UL << display_CSEGB_Pos)

#define display_CSEGC_Pos          	2U
#define display_CSEGC_Msk 			(1UL << display_CSEGC_Pos)

#define display_CSEGD_Pos          	3U
#define display_CSEGD_Msk 			(1UL << display_CSEGD_Pos)

#define display_CSEGE_Pos          	4U
#define display_CSEGE_Msk 			(1UL << display_CSEGE_Pos)

#define display_CSEGF_Pos          	5U
#define display_CSEGF_Msk 			(1UL << display_CSEGF_Pos)

#define display_CSEGG_Pos          	6U
#define display_CSEGG_Msk 			(1UL << display_CSEGG_Pos)

#define display_CSEGDP_Pos          7U
#define display_CSEGDP_Msk 			(1UL << display_CSEGDP_Pos)


#define FREC_MULTIPLEXOR	1000U //frecuencia con las que se cambia de digito
#define FREC_BRIGHTNESS	5000U //frecuencia de las simulaion del PWM
#define BRIGHT_LEVEL 4 // cantidad de niveles de brillo
#define DIGIT_AMOUNT 4//cantidad de digitos del display
#define ALPHABET 10//cantidad de simbolos del alfabeto
#define CLEAR_DISPLAY 0
#define MAX_INT_4_DIGIT 9999
/**
 * @brief turn an int into a 7seg pin state
 * @param num numbre to turn into a 7seg
 */
uint8_t display_set_cseg(unsigned int num){
	switch(num){
		case 0:
			return(0x3F);
			break;
		case 1:
			return(0x06);
			break;
		case 2:
			return(0x5B);
			break;
		case 3:
			return(0x4F);
			break;
		case 4:
			return(0x66);
			break;
		case 5:
			return(0x6D);
			break;
		case 6:
			return(0x7D);
			break;
		case 7:
			return(0x07);
			break;
		case 8:
			return(0x7F);
			break;
		case 9:
			return(0x6F);
			break;
		default:
			return(0x00);
			break;
	}
}

/**
 * @brief turn on off each gpio
 */
void display_CSEG_show(int PIN_CSEG, int PIN_LEVEL){
	if(PIN_LEVEL!=0){
		gpioWrite(PIN_CSEG, HIGH);
	}
	else{
		gpioWrite(PIN_CSEG, LOW);
	}
}

/**
 * @brief set HIGH or LOW the 7 seg pins
 */
void setPinsState(uint8_t cSeg){
	display_CSEG_show(pinCsGa, cSeg & display_CSEGA_Msk);
	display_CSEG_show(pinCsGb, cSeg & display_CSEGB_Msk);
	display_CSEG_show(pinCsGc, cSeg & display_CSEGC_Msk);
	display_CSEG_show(pinCsGd, cSeg & display_CSEGD_Msk);
	display_CSEG_show(pinCsGe, cSeg & display_CSEGE_Msk);
	display_CSEG_show(pinCsGf, cSeg & display_CSEGF_Msk);
	display_CSEG_show(pinCsGg, cSeg & display_CSEGG_Msk);
	display_CSEG_show(pinCsGdp, cSeg & display_CSEGDP_Msk);
}

/**
 * @brief set up gpio of the mux
 * @param disp, wich 7seg i want to turn on, between 0 to 3
 */
void setMux(uint8_t disp){
	if(disp>3){
		disp=3;
	}
	bool s0 [4]={HIGH,HIGH,LOW,LOW};
	bool s1 [4]={HIGH,LOW,HIGH,LOW};
	gpioWrite(pinSe10,s0[disp]);
	gpioWrite(pinSe11,s1[disp]);
}

bool display_init(uint8_t _pinCsGa,uint8_t _pinCsGb,uint8_t _pinCsGc,uint8_t _pinCsGd,uint8_t _pinCsGe,uint8_t _pinCsGf,uint8_t _pinCsGg,uint8_t _pinCsGdp,uint8_t _pinSe10,uint8_t _pinCsSe11,uint32_t _SysTickFrec){
	pinCsGa=_pinCsGa;
	pinCsGb=_pinCsGb;
	pinCsGc=_pinCsGc;
	pinCsGd=_pinCsGd;
	pinCsGe=_pinCsGe;
	pinCsGf=_pinCsGf;
	pinCsGg=_pinCsGg;
	pinCsGdp=_pinCsGdp;
	pinSe10=_pinSe10;
	pinSe11=_pinCsSe11;
	SysTickFrec=_SysTickFrec;

	prescalerMultiplexor=FREC_BRIGHTNESS/FREC_MULTIPLEXOR;
	prescalerPwm=SysTickFrec/FREC_BRIGHTNESS;

	gpioMode(pinCsGa, OUTPUT);
	gpioMode(pinCsGb, OUTPUT);
	gpioMode(pinCsGc, OUTPUT);
	gpioMode(pinCsGd, OUTPUT);
	gpioMode(pinCsGe, OUTPUT);
	gpioMode(pinCsGf, OUTPUT);
	gpioMode(pinCsGg, OUTPUT);
	gpioMode(pinCsGdp, OUTPUT);
	gpioMode(pinSe10, OUTPUT);
	gpioMode(pinSe11, OUTPUT);
	setMux(0);//inicializo en rimer display el mux

	SysTick_Init(IrqAllInclusive);

	for(int i=0;i<4;i++){//SACAR para pruebas nomas, seteo los display en 0 1 2 3
		cseg[i]=display_set_cseg(8);

	}
	return true;
}


/**
 * @brief turn on off each 7seg, and change multiplexor(print lcd and set bright)
 */
void IrqAllInclusive(void){
	static uint32_t CounterPrescalerPwm=0;
	static uint32_t CounterPrescalerMux=0;
	static uint32_t currentPeriod=0;
	static uint8_t turnOnOnce=0;
	static uint8_t turnOffOnce=0;
	static uint8_t lastDigit=0;

	if((CounterPrescalerPwm%=prescalerPwm)==0){ //divicion del clock para el PWM
		if((currentPeriod<brightLevel)){
			if(!turnOnOnce){
				setPinsState(cseg[lastDigit]);
				turnOnOnce=1;
			}

		}else if(!turnOffOnce){
			setPinsState(0);
			turnOffOnce=1;
		}


		if((CounterPrescalerMux%=prescalerMultiplexor)==0){ // divicion del clock para el multiplexeo de los 7 segmentos
			setMux(current7Seg);
			if(!turnOffOnce){
				setPinsState(cseg[current7Seg]);
			}
			//setPinsState(cseg[current7Seg]);
			lastDigit=current7Seg;
			current7Seg++;
			current7Seg=current7Seg%4;
			//lastDigit=current7Seg;
		}
		CounterPrescalerMux++;
		currentPeriod++;
		if((currentPeriod%=BRIGHT_LEVEL)==0){
					turnOnOnce=0;
					turnOffOnce=0;
				}
	}
	CounterPrescalerPwm++;
}


void setBright(uint8_t bright){
	bright%=BRIGHT_LEVEL;// aseguro que el nivel de brillo no sea mallor al esperado
	brightLevel=bright;
}


void setDigit(uint8_t pos,uint8_t digit){
	pos%=DIGIT_AMOUNT;//overflow protection
	digit%=ALPHABET;
	cseg[pos]=display_set_cseg(digit);
}

void clearDisplay(){
	for(int i=0;i<DIGIT_AMOUNT;i++){
		cseg[i]=CLEAR_DISPLAY;
	}
}

bool setInt2Dsplay(uint16_t num){
	uint8_t currentNum=0;
	if(num>MAX_INT_4_DIGIT){
		return false;
	}

	for(int i=0;i<MAX_INT_4_DIGIT;i++){
		currentNum=num/(10^(MAX_INT_4_DIGIT-1-i));
		num-=currentNum;
		setDigit(MAX_INT_4_DIGIT-1-i,currentNum);
	}

}
