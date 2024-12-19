/*
* My_Tasks.c
*
* Created: 5/3/2024 1:54:25 AM
*  Author: Mohammed
*/

#include "My_Tasks.h"
#include "MCAL/DIO_Interface.h"
#include "HAL/LCD_Interface.h"
#include "HAL/SevSeg_Interface.h"
#include "FREERTOS/include/FreeRTOS.h"
#include "FREERTOS/FreeRTOSConfig.h"
#include "FREERTOS/include/semphr.h"
#include "MCAL/eepromInternal_Interface.h"
#define F_CPU	8000000UL
#include <util/delay.h>


extern SemaphoreHandle_t btn1Press;
extern SemaphoreHandle_t btn2Press;
extern SemaphoreHandle_t btn3Press;
volatile static Stopwatch_Mode_t stp_Mode = STOPWATCH_MODE_NORMAL;

volatile static u8  sevsegupdate=10;
static volatile u8  stopwatchMax=10;

void taskInitEcu(void){
	u8 x;
	DIO_Init();
	//LCD_Init();
	SEVSEG_2_Init();
	eepromInt_Int();
	eepromInt_Read(2, &x);
	if (x==0){
		eepromInt_Write(0, stopwatchMax);
		eepromInt_Write(2, 1);
		}else{
		eepromInt_Read(0, &stopwatchMax);
	}
	sevsegupdate=stopwatchMax;
}

void sevseg_2_update(void *ptr){
	while(1){
		FreeRTOS_SEVSEG_Display_2_Digit(SEVSEG_2, sevsegupdate, 1);
		vTaskDelay(2);
		FreeRTOS_SEVSEG_Display_2_Digit(SEVSEG_2, sevsegupdate, 2);
		vTaskDelay(2);
	}
}


void task_button(void *ptr){
	static u8 flag=1;
	while (1){
		
		if ( (DIO_ReadPin(PD2)==LOW) && (flag==1)){
			if (stp_Mode==STOPWATCH_MODE_NORMAL){
				stp_Mode=STOPWATCH_MODE_PAUSE;
			}
			else if (stp_Mode==STOPWATCH_MODE_PAUSE){
				stp_Mode=STOPWATCH_MODE_NORMAL;
			}
			xSemaphoreGive(btn1Press);
			flag=0;
		}
		else if ( (DIO_ReadPin(PD3)==LOW) && (flag==1)){
			if (stp_Mode==STOPWATCH_MODE_NORMAL){
				stp_Mode=STOPWATCH_MODE_RESET;
			}
			xSemaphoreGive(btn2Press);
			flag=0;
		}
		else if ( (DIO_ReadPin(PD4)==LOW) && (flag==1) ){
			if (stp_Mode==STOPWATCH_MODE_NORMAL){
				stp_Mode=STOPWATCH_MODE_EDIT;
			}
			else if (stp_Mode==STOPWATCH_MODE_EDIT){
				eepromInt_Write(0, stopwatchMax);
				stp_Mode=STOPWATCH_MODE_NORMAL;
			}
			sevsegupdate=stopwatchMax;
			xSemaphoreGive(btn3Press);
			flag=0;
		}
		else if((DIO_ReadPin(PD2)==LOW) && stp_Mode==STOPWATCH_MODE_EDIT){
			xSemaphoreGive(btn1Press);
		}
		else if((DIO_ReadPin(PD3)==LOW) && stp_Mode==STOPWATCH_MODE_EDIT){
			xSemaphoreGive(btn2Press);
		}
		else if (  (DIO_ReadPin(PD2)!=LOW) && (DIO_ReadPin(PD3)!=LOW) && (DIO_ReadPin(PD4)!=LOW) ){
			flag=1;
		}
		vTaskDelay(100);
	}
}
void task_Normal(void *ptr){
	
	while (1){
		if (stp_Mode==STOPWATCH_MODE_NORMAL){
			if (sevsegupdate==0){
				sevsegupdate=stopwatchMax;
			}
			else if (sevsegupdate==1){
				stp_Mode=STOPWATCH_MODE_PAUSE;
			}
			sevsegupdate--;
			vTaskDelay(1000);
		}
		else{
			vTaskDelay(100);
		}
	}
	
}


void task_Reset(void *ptr){
	while (1){
		if(stp_Mode==STOPWATCH_MODE_RESET){
			if(xSemaphoreTake(btn2Press, 0)==pdTRUE){
				sevsegupdate=stopwatchMax;
				stp_Mode = STOPWATCH_MODE_NORMAL;
			}
		}
		vTaskDelay(250);
	}
}



void task_Edit(void *ptr){
	while (1){
		if (stp_Mode == STOPWATCH_MODE_EDIT){
			if(xSemaphoreTake(btn1Press, 0)==pdTRUE){
				stopwatchMax+=10;
			}
			if(xSemaphoreTake(btn2Press, 0)==pdTRUE){
				stopwatchMax+=1;
				if (stopwatchMax%10==0){
					stopwatchMax-=10;
				}
			}
			stopwatchMax%=100;
			if (stopwatchMax==0){
				stopwatchMax=1;
			}
			sevsegupdate=stopwatchMax;
		}
			vTaskDelay(250);
	}
}
