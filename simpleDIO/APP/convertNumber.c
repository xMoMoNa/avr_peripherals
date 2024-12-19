/*
* convertNumber.c
*
* Created: 2024-03-16 10:19:45 AM
*  Author: Mohammed
*/
#include "..\std_types.h"
#include "..\MCAL\DIO_Interface.h"
#include "..\HAL\LCD_Interface.h"
#include "..\HAL\KeyPad_Interface.h"
#include "convertNumber_Interface.h"
#define F_CPU 8000000UL
#include <util/delay.h>

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

static u8 Char2Digit(u8 c){
	if(c=='a' || c=='A'){
		return 10;
		}else if(c=='b'|| c=='B'){
		return 11;
		}else if(c=='c' || c=='C'){
		return 12;
		}else if(c=='D' || c=='d'){
		return 13;
		}else if(c=='e' || c=='E'){
		return 14;
		}else if(c=='f' || c=='F'){
		return 15;
	}
}

s32 Convert2Dec(NumberType_t type ){
	u8 key=0, i='F', flag=0;
	s32 num=0;
	while (1){
		key=KeyPad_4x4_ReadKey(KEYPAD_4X4_1);
		if (key>='0'&&key<='9' || key == '/'|| key == '*'|| key=='-'){
			switch(type){
				case Bin:
				if (key=='0'||key=='1')
				{
					LCD_SendChar(LCD1, key, DIRECTION_UP);
					num=num*2+key-'0';
				}
				else if(key=='-'&& LCD_ReadCursor(LCD1)>2){
					LCD_DeleteNow(LCD1, DIRECTION_UP);
					num=num/2;
				}
				break;
				
				case Dec:
				if (key>='0'&&key<='9')
				{
					LCD_SendChar(LCD1, key, DIRECTION_UP);
					num=num*10+key-'0';
				}
				else if(key=='-'&& LCD_ReadCursor(LCD1)>2){
					LCD_DeleteNow(LCD1, DIRECTION_UP);
					num=num/10;
				}
				break;
				case Hex:
				
				if (key>='0'&&key<='9')
				{
					LCD_SendChar(LCD1, key, DIRECTION_UP);
					num=num*16+key-'0';
					break;
				}
				else if(key=='-'&& LCD_ReadCursor(LCD1)>2){
					LCD_DeleteNow(LCD1, DIRECTION_UP);
					num=num/16;
				}
				
				else{
					if (key!= '/'){
						continue;
					}
					while (1){
						key=KeyPad_4x4_ReadKey(KEYPAD_4X4_1);
						if (key=='/'){
							i++;
							if (i>'F'){
								i='A';
							}
							LCD_SendChar(LCD1, i, DIRECTION_UP);
							LCD_SetCursor(LCD1, LCD_ReadCursor(LCD1)-1);
						}
						else if (key=='*'){
							LCD_SetCursor(LCD1, LCD_ReadCursor(LCD1)+1);
							flag=0;
							num=num*16+Char2Digit(i);
							break;
							
						}
						else{
						}// end of while to check a b c d e f
						_delay_ms(200);
					}
					i='F';
				}
				break;
			}// switch case of Dec Bin Hex
			_delay_ms(350);
		}
		else if(key == '='){
			return num;
		}
	}
}

void Screen_Welcome(void){
	LCD_ClearScreen(LCD1);
	LCD_SendString(LCD1, "   Welcome...", DIRECTION_UP);
	LCD_SetCursor(LCD1, 16);
	LCD_SendString(LCD1, "  By Mohammed", DIRECTION_UP);
	_delay_ms(1000);
}

static NumberType_t Get_Choise(){
	u8 key=0;
	LCD_SetCursor(LCD1, 16);
	LCD_SendString(LCD1, "1|D  2|B  3|H", DIRECTION_UP);
	while (1){
		key=KeyPad_4x4_ReadKey(KEYPAD_4X4_1);
		if (key>='1' && key<='3'){
			break;
		}
	}
	while (key==KeyPad_4x4_ReadKey(KEYPAD_4X4_1));
	return key-'0';
}

NumberType_t Screen_Convert_From(void){
	LCD_ClearScreen(LCD1);
	LCD_SendString(LCD1, "  Convert From", DIRECTION_UP);
	return Get_Choise();
}

NumberType_t Screen_Convert_To(){
	LCD_ClearScreen(LCD1);
	LCD_SendString(LCD1, "  Convert To", DIRECTION_UP);
	return Get_Choise();
}

static u8 convert_Type_To_Char(NumberType_t t){
	switch(t){
		case Bin:
		return 'B';
		break;
		case Dec:
		return 'D';
		break;
		case Hex:
		return 'H';
		break;
	}
	return 'r';

}

convert_State_t Screen_Converter(NumberType_t from, NumberType_t to){
	s32 num;
	u8 key;
	LCD_ClearScreen(LCD1);
	LCD_SendChar(LCD1,convert_Type_To_Char(from), DIRECTION_UP);
	LCD_SendChar(LCD1, ':', DIRECTION_UP);
	LCD_SetCursor(LCD1, 16);
	LCD_SendChar(LCD1,convert_Type_To_Char(to), DIRECTION_UP);
	LCD_SendChar(LCD1, ':', DIRECTION_UP);
	LCD_SetCursor(LCD1, 2);
	num=Convert2Dec(from);
	LCD_SetCursor(LCD1,18);
	switch(to){
		case Bin:
		LCD_SendBinary(LCD1, num, DIRECTION_UP);
		break;
		case Dec:
		LCD_SendNumber(LCD1, num, DIRECTION_UP);
		
		break;
		case Hex:
		LCD_SendHex(LCD1, num, DIRECTION_UP);
		break;
	}
	while(1){
		key=KeyPad_4x4_ReadKey(KEYPAD_4X4_1);
		if (key=='c'){
			return RETURN;
		}
		else if (key>='0'&&key<='9' || (from==Hex&&key=='/')){
			return CONTINUE;
		}
		
	}
}