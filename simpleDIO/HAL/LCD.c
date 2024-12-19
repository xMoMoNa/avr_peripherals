/*
* LCD.c
*
* Created: 2024-03-11 4:43:38 AM
*  Author: Mohammed
*/
#include "..\std_types.h"
#include "..\utils.h"
#include "..\MCAL\DIO_Interface.h"
#include "LCD_Interface.h"
#define F_CPU 8000000UL
#include "util\delay.h"


const LCD_Pin_t LCD_Pins_Array[TOTAL_LCD];
static u8 LcdCursor[TOTAL_LCD]={0};
static u8 contentCursor[TOTAL_LCD]={0};
static u8 LcdContent[TOTAL_LCD][32]={0};
static void LCD_ShiftContent(LCD_t lcd, LCD_Shift_Direction_t Direction){
	u8 i=0;
	for (i=0; i<16; i++){
		switch(Direction){
			case DIRECTION_UP:
			LcdContent[lcd][i]=LcdContent[lcd][i+16];
			LcdContent[lcd][i+16]=' ';
			break;
			case DIRECTION_DOWN:
			LcdContent[lcd][i+16]=LcdContent[lcd][i];
			LcdContent[lcd][i]=' ';
			break;
		}
		
	}
}

static u8 Digit2char(u8 num){
	if (num<10){
		return num+'0';
		} else if(num==10){
		return 'A';
		}else if(num==11){
		return 'B';
		}else if(num==12){
		return 'C';
		}else if(num==13){
		return 'D';
		}else if(num==14){
		return 'E';
		}else if(num==15){
		return 'F';
	}
}

#if LCD_MODE_PIN == _8_PIN
static void SendIns(LCD_t lcd, u8 ins){
	DIO_WritePin(LCD_Pins_Array[lcd].rs, LOW);
	for (DIO_Pin_t p=0; p<8; p++){
		DIO_WritePin(LCD_Pins_Array[lcd].pin[p], ReadBit(ins, p));
	}
	DIO_WritePin(LCD_Pins_Array[lcd].enable, HIGH);
	_delay_us(50);
	DIO_WritePin(LCD_Pins_Array[lcd].enable, LOW);
	_delay_us(50);
}
static void SendData(LCD_t lcd, u8 data){
	DIO_WritePin(LCD_Pins_Array[lcd].rs, HIGH);
	for (DIO_Pin_t p=0; p<8; p++){
		DIO_WritePin(LCD_Pins_Array[lcd].pin[p], ReadBit(data, p));
	}
	DIO_WritePin(LCD_Pins_Array[lcd].enable, HIGH);
	_delay_ms(1);
	DIO_WritePin(LCD_Pins_Array[lcd].enable, LOW);
	_delay_ms(1);
}
void LCD_Init(void){
	
	_delay_ms(50);
	for (LCD_t lcd=0; lcd<TOTAL_LCD; lcd++){
		for (u8 i=0;i<32;i++){
			LcdContent[lcd][i]=0;
		}
		for (DIO_Pin_t p=0; p<9; p++){
			DIO_InitPin(LCD_Pins_Array[lcd].pin[p], OUTPUT);
		}
		SendIns(lcd, 0x38); // Function set
		SendIns(lcd, 0x0C); // Display control
		SendIns(lcd, 0x01); // Clear display
		_delay_ms(1);
		SendIns(lcd, 0x06); // Entry Mode Set
	}
}

#elif LCD_MODE_PIN == _4_PIN

static void SendIns(LCD_t lcd, u8 ins){
	DIO_WritePin(LCD_Pins_Array[lcd].rs, LOW);
	for (DIO_Pin_t p=0; p<4; p++){
		DIO_WritePin(LCD_Pins_Array[lcd].pin[p], ReadBit((ins>>4), p));
	}
	DIO_WritePin(LCD_Pins_Array[lcd].enable, HIGH);
	_delay_us(100);
	DIO_WritePin(LCD_Pins_Array[lcd].enable, LOW);
	_delay_us(100);
	for (DIO_Pin_t p=0; p<4; p++){
		DIO_WritePin(LCD_Pins_Array[lcd].pin[p], ReadBit(ins, p));
	}
	DIO_WritePin(LCD_Pins_Array[lcd].enable, HIGH);
	_delay_us(100);
	DIO_WritePin(LCD_Pins_Array[lcd].enable, LOW);
	_delay_us(100);
}
static void SendData(LCD_t lcd, u8 data){
	DIO_WritePin(LCD_Pins_Array[lcd].rs, HIGH);
	for (DIO_Pin_t p=0; p<4; p++){
		DIO_WritePin(LCD_Pins_Array[lcd].pin[p], ReadBit((data>>4), p));
	}
	DIO_WritePin(LCD_Pins_Array[lcd].enable, HIGH);
	_delay_us(100);
	DIO_WritePin(LCD_Pins_Array[lcd].enable, LOW);
	_delay_us(100);
	for (DIO_Pin_t p=0; p<4; p++){
		DIO_WritePin(LCD_Pins_Array[lcd].pin[p], ReadBit(data, p));
	}
	DIO_WritePin(LCD_Pins_Array[lcd].enable, HIGH);
	_delay_us(100);
	DIO_WritePin(LCD_Pins_Array[lcd].enable, LOW);
	_delay_us(100);
}

void LCD_Init(void){
	_delay_ms(50);
	for (LCD_t lcd=0; lcd<TOTAL_LCD; lcd++){
		for (u8 i=0;i<32;i++){
			LcdContent[lcd][i]=0;
		}
		for (DIO_Pin_t p=0; p<6; p++){
			DIO_InitPin(LCD_Pins_Array[lcd].pin[p], OUTPUT);
		}
		SendIns(lcd, 0x02); //
		SendIns(lcd, 0x28); // function set
		SendIns(lcd, 0x0C); // display control
		SendIns(lcd, 0x01); // clear display
		_delay_ms(1);
		SendIns(lcd, 0x06); // Entry Mode Set
	}
}
#endif

void LCD_ClearScreen(LCD_t lcd){
	SendIns(lcd, 0x01);
	_delay_ms(2);
	LcdCursor[lcd]=0;
	for (;contentCursor[lcd]>0; contentCursor[lcd]--){
		LcdContent[lcd][contentCursor[lcd]]=' ';
	}
	LcdContent[lcd][contentCursor[lcd]]=' ';
}

void LCD_SetCursor(LCD_t lcd, u8 pos){
	u8 pos1=pos%16, pos2=pos-16;
	SendIns(lcd, 0x80 | ( pos<16? pos1 : 0x40+pos2));
	LcdCursor[lcd]=pos;
	contentCursor[lcd]=pos;
}

void LCD_SendChar(LCD_t lcd, u8 character, LCD_Shift_Direction_t direction){
	if (LcdCursor[lcd]==32&& direction == DIRECTION_UP){
		LCD_ShiftContent(lcd, direction);
		LCD_SetCursor(lcd, 0);
		for (contentCursor[lcd]=0; contentCursor[lcd]<32; contentCursor[lcd]++){
			if (contentCursor[lcd]==16){
				LCD_SetCursor(lcd,16);
			}
			SendData(lcd, LcdContent[lcd][contentCursor[lcd]] == 0 ? ' ': LcdContent[lcd][contentCursor[lcd]] );
		}
		LCD_SetCursor(lcd,16);
	}
	else if (LcdCursor[lcd]==16 && direction==DIRECTION_DOWN){
		LCD_ShiftContent(lcd, direction);
		LCD_SetCursor(lcd, 0);
		for (contentCursor[lcd]=0; contentCursor[lcd]<32; contentCursor[lcd]++){
			if (contentCursor[lcd]==16){
				LCD_SetCursor(lcd,16);
			}
			SendData(lcd,LcdContent[lcd][contentCursor[lcd]] == 0 ? ' ': LcdContent[lcd][contentCursor[lcd]] );
		}
		LCD_SetCursor(lcd, 0);
	}
	else if (LcdCursor[lcd]==32 && direction==DIRECTION_DOWN){
		LCD_SetCursor(lcd, 0);
	}
	LCD_SetCursor(lcd, LcdCursor[lcd]);
	LcdContent[lcd][contentCursor[lcd]]=character;
	SendData(lcd, LcdContent[lcd][contentCursor[lcd]]);
	LcdCursor[lcd]++;
	contentCursor[lcd]++;
}

void LCD_SendString(LCD_t lcd, u8* str, LCD_Shift_Direction_t direction){
	u8 c=0;
	while(str[c]){
		LCD_SendChar(lcd,str[c],direction);
		c++;
	}
}


void LCD_SendNumber(LCD_t lcd, s32 num, LCD_Shift_Direction_t direction){
	u8 n=0;
	if (num==0){
		LCD_SendChar(lcd, '0',direction);
	}
	else if(num<0){
		LCD_SendChar(lcd, '-',direction);
		num=num*-1;
	}
	u8 str[5]={0};
	while(num){
		str[n]=num%10+'0';
		num=num/10;
		n++;
	}
	while (n){
		n--;
		LCD_SendChar(lcd, str[n],direction);
	}
}

void LCD_SendBinary(LCD_t lcd, s32 num, LCD_Shift_Direction_t direction){
	u8 i=31;
	while(!ReadBit(num, i)&& i>0){
		i--;
	}
	while (i>0){
		LCD_SendChar(lcd, ReadBit(num, i)+'0',direction);
		i--;
	}
	if(i==0){
		LCD_SendChar(lcd, ReadBit(num, i)+'0',direction);
	}
}

void LCD_SendHex(LCD_t lcd, s32 num, LCD_Shift_Direction_t direction){
	u8 i=3;
	while(i>0 && (num&(0x000f<<(4*i)))==0){
		i--;
	}
	while (i>0){
		LCD_SendChar(lcd, Digit2char((num>>(i*4))&0x0f),direction);
		i--;
	}
	if(i==0){
		LCD_SendChar(lcd, Digit2char(num&0x0f),direction);
	}
}

void LCD_SendFloat(LCD_t lcd, s32 num, u8 pres,LCD_Shift_Direction_t direction){
	s32 rem=0, zero=0;
	if(num!=0){
		while (pres--){
			if (num==0){
				zero++;
				}else{
				rem=rem*10+num%10;
				num/=10;
			}
		}
	}
	LCD_SendNumber(lcd, num, direction);
	LCD_SendChar(lcd,'.', direction);
	for (pres=0; pres<zero; pres++){
		LCD_SendChar(lcd, '0', direction);
	}
	LCD_SendNumber(lcd, rem, DIRECTION_UP);
}

void LCD_DeleteNow(LCD_t lcd, LCD_Shift_Direction_t direction){
	switch (direction){
		case DIRECTION_UP:
		if (LcdCursor[lcd]>0){
			LCD_SetCursor(lcd, LcdCursor[lcd]-1);
			LCD_SendChar(lcd, ' ',direction);
			LCD_SetCursor(lcd, LcdCursor[lcd]-1);
		}
		break;
		case DIRECTION_DOWN:
		if (LcdCursor[lcd]==1){
			LCD_SetCursor(lcd, 0);
			LCD_SendChar(lcd, ' ',direction);
			LCD_SetCursor(lcd, 32);
		}
		else{
			LCD_SetCursor(lcd, LcdCursor[lcd]-1);
			LCD_SendChar(lcd, ' ',direction);
			LCD_SetCursor(lcd, LcdCursor[lcd]-1);
		}
		break;
	}
}

void LCD_Delete(LCD_t lcd, u8 end, u8 start, LCD_Shift_Direction_t direction){
	for (; end>=start; end--){
		LCD_DeleteNow(lcd,direction);
	}
	LCD_SetCursor(lcd, start);
}

void LCD_GenerateChar(LCD_t lcd, u8 pattern[7], u8 address){
	u8 i=7;
	SendIns(lcd, (address*8)|0x40); //set CGRAM Address
	while(i>0){	// Send 7 row pattern, row by row.
		SendData(lcd, pattern[7-i]);  // Only lower 5-bit of character pattern data is valid.
		i--;
	}
	LCD_SetCursor(lcd, LcdCursor[lcd]); // return to address counter of DD RAM location
	
}

u8 LCD_ReadCursor(LCD_t lcd){
	return LcdCursor[lcd];
}

u8 LCD_ReadContent(LCD_t lcd, u8 index){
	return LcdContent[lcd][index];
}