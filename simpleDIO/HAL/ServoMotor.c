/*
* ServoMotor.c
*
* Created: 4/4/2024 12:37:49 PM
*  Author: Mohammed
*/
#include "..\MCAL\DIO_Interface.h"
#include "..\MCAL\Timers.h"
#include "..\HAL\ServoMotor_Interface.h"

extern const DIO_Pin_t servoMotor_Pin_Array[TOTAL_SERVOMOTOR];

void ServoMotor_Init(void){
	for(ServoMotor_t servo=0; servo<TOTAL_SERVOMOTOR; servo++){
		DIO_InitPin(servoMotor_Pin_Array[servo], OUTPUT);
	}
	Timer1_Init(TIMER1_FASTPWM_OCRA_TOP_MODE, TIMER1_SCALER_8);
	Timer1_OCRB1Mode(OCRB_NON_INVERTING);
	OCR1A=1999;
	
}

void ServoMotor_SetPosition(ServoMotor_t servo, u16 pos){
	pos=pos*(u32)1000/180+999;
	OCR1B=pos;
}
void ServoMotor_stop(){
	Timer1_OCRB1Mode(OCRB_DISCONNECTED);
}