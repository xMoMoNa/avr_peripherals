/*
* LCD_Interface.h
*
* Created: 2024-03-11 4:44:04 AM
*  Author: Mohammed
*/


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_
#include "..\std_types.h"
#include "..\MCAL\DIO_Interface.h"

#define _4_PIN 1
#define _8_PIN 2
#define LCD_MODE_PIN	_4_PIN

typedef enum{
	LCD1,
	TOTAL_LCD
}LCD_t;

typedef enum{
	DIRECTION_UP,
	DIRECTION_DOWN
}LCD_Shift_Direction_t;

#if LCD_MODE_PIN == _8_PIN

typedef union{
	struct{
		DIO_Pin_t d0;
		DIO_Pin_t d1;
		DIO_Pin_t d2;
		DIO_Pin_t d3;
		DIO_Pin_t d4;
		DIO_Pin_t d5;
		DIO_Pin_t d6;
		DIO_Pin_t d7;
		DIO_Pin_t rs;
		DIO_Pin_t enable;
	};
	DIO_Pin_t pin[9];
}LCD_Pin_t;
#elif LCD_MODE_PIN == _4_PIN
typedef union{
	struct{
		DIO_Pin_t d4;
		DIO_Pin_t d5;
		DIO_Pin_t d6;
		DIO_Pin_t d7;
		DIO_Pin_t rs;
		DIO_Pin_t enable;
	};
	DIO_Pin_t pin[5];
}LCD_Pin_t;
#endif


void LCD_Init(void);
void LCD_SendChar(LCD_t lcd, u8 character, LCD_Shift_Direction_t direction);
void LCD_SendString(LCD_t lcd, u8* str, LCD_Shift_Direction_t direction);
void LCD_SendNumber(LCD_t lcd, s32 num, LCD_Shift_Direction_t direction);
void LCD_SendBinary(LCD_t lcd, s32 num, LCD_Shift_Direction_t direction);
void LCD_SendHex(LCD_t lcd, s32 num, LCD_Shift_Direction_t direction);
void LCD_SendFloat(LCD_t lcd, s32 num, u8 pres,LCD_Shift_Direction_t direction);
void LCD_ClearScreen(LCD_t lcd);
void LCD_SetCursor(LCD_t lcd, u8 pos);
void LCD_DeleteNow(LCD_t lcd, LCD_Shift_Direction_t direction);
void LCD_Delete(LCD_t lcd, u8 end, u8 start, LCD_Shift_Direction_t direction);
void LCD_GenerateChar(LCD_t lcd, u8 pattern[7], u8 address);
u8 LCD_ReadCursor(LCD_t lcd);
u8 LCD_ReadContent(LCD_t lcd, u8 index);

#endif /* LCD_INTERFACE_H_ */