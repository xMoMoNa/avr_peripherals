/*
 * RGB_Interface.h
 *
 * Created: 4/16/2024 8:22:21 AM
 *  Author: Mohammed
 */ 


#ifndef RGB_INTERFACE_H_
#define RGB_INTERFACE_H_
#include "..\MCAL\DIO_Interface.h"
typedef enum{
	RGB_LED1,
	TOTAL_RGB_LED
}RGB_t;

typedef union{
	struct{
		DIO_Pin_t red;
		DIO_Pin_t green;
		DIO_Pin_t blue;
		};
	DIO_Pin_t pin[3];
	}RGB_Pin_t;

typedef union{
	struct{
		u8 red;
		u8 green;
		u8 blue;
		u8 intenisty;
	};
	u8 color[4];
}RGB_Color_t;

void rgb_Init();
void rgb_setColor(RGB_t led, RGB_Color_t color);


#endif /* RGB_INTERFACE_H_ */