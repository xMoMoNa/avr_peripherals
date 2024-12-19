/*
 * LCD_Cfg.h
 *
 * Created: 2024-03-11 4:44:26 AM
 *  Author: Mohammed
 */ 


#include "..\std_types.h"
#include "..\MCAL\DIO_Interface.h"
#include "..\HAL\LCD_Interface.h"

#if LCD_MODE_PIN == _8_PIN

const LCD_Pin_t LCD_Pins_Array[TOTAL_LCD]={
	{PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7, PB0, PB1}
};
#elif LCD_MODE_PIN == _4_PIN
const LCD_Pin_t LCD_Pins_Array[TOTAL_LCD]={
	{PA3, PA4, PA5, PA6, PA1, PA2}
};
#endif

