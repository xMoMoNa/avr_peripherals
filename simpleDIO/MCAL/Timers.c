#include "..\std_types.h"
#include "..\memory_map.h"
#include "Timers.h"

/*************************Pointer to functions to be assigned to ISR*********************************/
static void (*Timer0_OVF_Fptr) (void)=NULL;
static void (*Timer1_OVF_Fptr) (void)=NULL;
static void (*Timer1_OCA_Fptr) (void)=NULL;
static void (*Timer1_OCB_Fptr) (void)=NULL;
static void (*Timer1_ICU_Fptr) (void)=NULL;
/******************************************************************************************/
/*timer 0 functions*/
void TIMER0_Init(Timer0Mode_type mode,Timer0Scaler_type scaler)
{
	switch (mode)
	{
		case TIMER0_NORMAL_MODE:
		ClearBit(TCCR0,WGM00);
		ClearBit(TCCR0,WGM01);
		break;
		case TIMER0_PHASECORRECT_MODE:
		SetBit(TCCR0,WGM00);
		ClearBit(TCCR0,WGM01);
		break;
		case TIMER0_CTC_MODE:
		ClearBit(TCCR0,WGM00);
		SetBit(TCCR0,WGM01);
		break;
		case TIMER0_FASTPWM_MODE:
		SetBit(TCCR0,WGM00);
		SetBit(TCCR0,WGM01);
		break;
	}
	TCCR0&=0XF8;//0b11111000
	TCCR0|=scaler;
}

void TIMER0_OC0Mode(OC0Mode_type mode)
{
	switch (mode)
	{
		case OC0_DISCONNECTED:
		ClearBit(TCCR0,COM00);
		ClearBit(TCCR0,COM01);
		break;
		case OC0_TOGGLE:
		SetBit(TCCR0,COM00);
		ClearBit(TCCR0,COM01);
		break;
		case OC0_NON_INVERTING:
		ClearBit(TCCR0,COM00);
		SetBit(TCCR0,COM01);
		break;
		case OC0_INVERTING:
		SetBit(TCCR0,COM00);
		SetBit(TCCR0,COM01);
		break;
	}
}
void TIMER0_FastPWM(u8 duty){
	OCR0=((u16)duty*255)/100;
}

void TIMER0_OV_SetCallBack(void(*local_fptr)(void)){
	Timer0_OVF_Fptr=local_fptr;
}
void TIMER0_OV_InterruptEnable(void)
{
	SetBit(TIMSK,TOIE0);
}
void TIMER0_OV_InterruptDisable(void)
{
	ClearBit(TIMSK,TOIE0);
}
void TIMER0_OC_InterruptEnable(void)
{
	SetBit(TIMSK,OCIE0);
}
void TIMER0_OC_InterruptDisable(void)
{
	ClearBit(TIMSK,OCIE0);
}

ISR(VECT_TIM0_OVF){
	if (Timer0_OVF_Fptr!=NULL){
		Timer0_OVF_Fptr();
	}
}



/*************************************************************************/
/*timer 1 functions*/
void Timer1_Init( Timer1Mode_type mode,Timer1Scaler_type scaler)
{
	switch (mode)
	{
		case TIMER1_NORMAL_MODE:
		ClearBit(TCCR1A,WGM10);
		ClearBit(TCCR1A,WGM11);
		ClearBit(TCCR1B,WGM12);
		ClearBit(TCCR1B,WGM13);
		break;
		case TIMER1_CTC_ICR_TOP_MODE:
		ClearBit(TCCR1A,WGM10);
		ClearBit(TCCR1A,WGM11);
		SetBit(TCCR1B,WGM12);
		SetBit(TCCR1B,WGM13);
		break;
		
		case TIMER1_CTC_OCRA_TOP_MODE:
		ClearBit(TCCR1A,WGM10);
		ClearBit(TCCR1A,WGM11);
		SetBit(TCCR1B,WGM12);
		ClearBit(TCCR1B,WGM13);
		break;
		
		case TIMER1_FASTPWM_ICR_TOP_MODE:
		ClearBit(TCCR1A,WGM10);
		SetBit(TCCR1A,WGM11);
		SetBit(TCCR1B,WGM12);
		SetBit(TCCR1B,WGM13);
		break;
		
		case TIMER1_FASTPWM_OCRA_TOP_MODE:
		SetBit(TCCR1A,WGM10);
		SetBit(TCCR1A,WGM11);
		SetBit(TCCR1B,WGM12);
		SetBit(TCCR1B,WGM13);
		break;
	}

	TCCR1B&=0XF8;
	TCCR1B|=scaler;

}
void Timer1_OCRA1Mode(OC1A_Mode_type oc1a_mode)
{
	switch (oc1a_mode)
	{
		case OCRA_DISCONNECTED:
		ClearBit(TCCR1A,COM1A0);
		ClearBit(TCCR1A,COM1A1);
		break;
		case OCRA_TOGGLE:
		SetBit(TCCR1A,COM1A0);
		ClearBit(TCCR1A,COM1A1);
		break;
		case OCRA_NON_INVERTING:
		ClearBit(TCCR1A,COM1A0);
		SetBit(TCCR1A,COM1A1);
		break;
		case OCRA_INVERTING:
		SetBit(TCCR1A,COM1A0);
		SetBit(TCCR1A,COM1A1);
		break;
	}
}
void Timer1_OCRB1Mode(OC1B_Mode_type oc1b_mode)
{
	switch (oc1b_mode)
	{
		case OCRB_DISCONNECTED:
		ClearBit(TCCR1A,COM1B0);
		ClearBit(TCCR1A,COM1B1);
		break;
		case OCRB_TOGGLE:
		SetBit(TCCR1A,COM1B0);
		ClearBit(TCCR1A,COM1B1);
		break;
		case OCRB_NON_INVERTING:
		ClearBit(TCCR1A,COM1B0);
		SetBit(TCCR1A,COM1B1);
		break;
		case OCRB_INVERTING:
		SetBit(TCCR1A,COM1B0);
		SetBit(TCCR1A,COM1B1);
		break;
	}
}
void Timer1_InputCaptureEdge(ICU_Edge_type edge)
{
	if(edge==RISING)
	SetBit(TCCR1B,ICES1);
	
	else if(edge==FALLING)
	ClearBit(TCCR1B,ICES1);
}


/****************************Timer 1 Interrupt functions**************************************/

void Timer1_ICU_InterruptEnable(void)
{
	SetBit(TIMSK,TICIE1);
}
void Timer1_ICU_InterruptDisable(void)
{
	ClearBit(TIMSK,TICIE1);
}
void Timer1_OVF_InterruptEnable(void)
{
	SetBit(TIMSK,TOIE1);
}
void Timer1_OVF_InterruptDisable(void)
{
	ClearBit(TIMSK,TOIE1);
}
void Timer1_OCA_InterruptEnable(void)
{
	SetBit(TIMSK,OCIE1A);
}
void Timer1_OCA_InterruptDisable(void)
{
	ClearBit(TIMSK,OCIE1A);
}
void Timer1_OCB_InterruptEnable(void)
{
	ClearBit(TIMSK,OCIE1B);
}
void Timer1_OCB_InterruptDisable(void)
{
	ClearBit(TIMSK,OCIE1B);
}

/*********************************Timer 1 Call Back functions*****************************************/

void Timer1_OVF_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_OVF_Fptr=LocalFptr;
}
void Timer1_OCA_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_OCA_Fptr=LocalFptr;
}
void Timer1_OCB_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_OCB_Fptr=LocalFptr;
}
void Timer1_ICU_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_ICU_Fptr=LocalFptr;
}

/*********************************Timer 1 ISR functions*********************************************/
/*
ISR(VECT_TIM1_OVF)
{
	if(Timer1_OVF_Fptr!=NULL)
	{
		Timer1_OVF_Fptr();
	}
}
ISR(VECT_TIM1_COMPA)
{
	if(Timer1_OCA_Fptr!=NULL)
	{
		Timer1_OCA_Fptr();
	}
}
ISR(VECT_TIM1_COMPB)
{
	if(Timer1_OCB_Fptr!=NULL)
	{
		Timer1_OCB_Fptr();
	}
}
ISR(VECT_TIM1_CAP)
{
	if(Timer1_ICU_Fptr!=NULL)
	{
		Timer1_ICU_Fptr();
	}
}
*/