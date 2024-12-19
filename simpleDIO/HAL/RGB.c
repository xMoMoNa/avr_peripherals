/*
* ٌRGB.c
*
* Created: 4/16/2024 8:22:05 AM
*  Author: Mohammed
*/
#include "..\memory_map.h"
#include "..\MCAL\DIO_Interface.h"
#include "..\MCAL\Timers.h"
#include "..\SERVICES\Timers_Services.h"
#include "RGB_Interface.h"
static RGB_Color_t ledColor[TOTAL_RGB_LED];
static RGB_Color_t led_temp;
const RGB_Pin_t RGB_PinArray[TOTAL_RGB_LED];
static void rgb_ISR(void);



void rgb_Init(){
	for (u8 led=0; led<TOTAL_RGB_LED; led++){
		DIO_InitPin(RGB_PinArray[led].red, OUTPUT);
		DIO_InitPin(RGB_PinArray[led].green, OUTPUT);
		DIO_InitPin(RGB_PinArray[led].blue, OUTPUT);
	}
	TIMER0_OV_InterruptEnable();
	TIMER0_OV_SetCallBack(rgb_ISR);
	TIMER0_Init(TIMER1_NORMAL_MODE, TIMER1_SCALER_8);
}

void rgb_setColor(RGB_t led, RGB_Color_t color){
	u8 i=color.intenisty;
	ledColor[led].red=color.red*(u16)i/100;
	ledColor[led].green=color.green*(u16)i/100;
	ledColor[led].blue=color.blue*(u16)i/100;
}

static void rgb_ISR(void){
	static u8 counter=0;
	TCNT0=150;
	for(u8 i=0; i<TOTAL_RGB_LED; i++){
		if (counter*2>ledColor[i].red){
			DIO_WritePin(RGB_PinArray[i].red, LOW);
		}
		else{
			DIO_WritePin(RGB_PinArray[i].red, HIGH);
		}
		if (counter*2>ledColor[i].green){
			DIO_WritePin(RGB_PinArray[i].green, LOW);
		}
		else{
			DIO_WritePin(RGB_PinArray[i].green, HIGH);
		}
		if (counter*2>ledColor[i].blue){
			DIO_WritePin(RGB_PinArray[i].blue, LOW);
		}
		else{
			DIO_WritePin(RGB_PinArray[i].blue, HIGH);
		}
		
	}
	if(counter<127){
		counter++;
	}else{
		counter=0;
	}
}