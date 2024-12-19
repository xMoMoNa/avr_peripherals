/*
* UART_Task_Cfg.c
*
* Created: 4/16/2024 2:44:21 AM
*  Author: Mohammed
*/
#include "..\std_types.h"
#include "..\MCAL\DIO_Interface.h"
#include "..\MCAL\Timers.h"
#include "..\HAL\ServoMotor_Interface.h"
#include "..\HAL\ServoMotor_Interface.h"
#include "..\HAL\RGB_Interface.h"
#include "..\HAL\LCD_Interface.h"
#include "..\SERVICES\UART_Services.h"

static RGB_Color_t color[2]={{100, 100, 250, 100}, {100, 250, 100, 100}};
static RGB_Color_t tmpColor={0,0,0,100};

static void ledOn(u8 numberOfLed);
static void ledOff(u8 numberOfLed);
static void Servo(u8 angle);
static void RGB_red(u8 value);
static void RGB_green(u8 value);
static void RGB_blue(u8 value);
static void RGB_Intinisty(u8 value);
static void RGB_SetColor(u8 i);

const uart_task_t uart_taskArray[NUMBEROFTASK]={
	{"ledOn",ledOn},
	{"ledOff",ledOff},
	{"servo",Servo},
	{"rgbRed",RGB_red},
	{"rgbGreen",RGB_green},
	{"rgbBlue",RGB_blue},
	{"rgbIntinisty",RGB_Intinisty},
	{"rgbSetColor", RGB_SetColor},
};


void ledOn(u8 numberOfLed){
	if (numberOfLed==5)
	{
		DIO_WritePin(PC4, HIGH);
		uart_sendStringAsync("Done\n");
	}else if(numberOfLed==4){
	DIO_WritePin(PC3, HIGH);
	uart_sendStringAsync("Done\n");
}
}


void ledOff(u8 numberOfLed){
	if (numberOfLed==5)
	{
		DIO_WritePin(PC4, LOW);
		uart_sendStringAsync("Done\n");
	}else if(numberOfLed==4){
		DIO_WritePin(PC3, LOW);
		uart_sendStringAsync("Done\n");
	}
}


static void Servo(u8 angle){ // need to complete
	ServoMotor_SetPosition(SERVOMOTOR1, angle);
	uart_sendStringAsync("Done\n");
}

static void RGB_red(u8 value){
	tmpColor.red=value;
	rgb_setColor(RGB_LED1, tmpColor);
	uart_sendStringAsync("Done\n");
}

static void RGB_green(u8 value){
	tmpColor.green=value;
	rgb_setColor(RGB_LED1, tmpColor);
	uart_sendStringAsync("Done\n");
}

static void RGB_blue(u8 value){
	tmpColor.blue=value;
	rgb_setColor(RGB_LED1, tmpColor);
	uart_sendStringAsync("Done\n");
}

static void RGB_Intinisty(u8 value){
	tmpColor.intenisty=value;
	rgb_setColor(RGB_LED1, tmpColor);
	uart_sendStringAsync("Done\n");
}

static void RGB_SetColor(u8 i){
	rgb_setColor(RGB_LED1, color[i+1]);
	uart_sendStringAsync("Done\n");
}
