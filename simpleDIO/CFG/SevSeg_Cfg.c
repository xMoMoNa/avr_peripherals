/*
 * SevSeg_Cfg.c
 *
 * Created: 2024-03-08 4:09:00 AM
 *  Author: Mohammed
 */ 
#include "..\std_types.h"
#include "..\MCAL\DIO_Interface.h"
#include "..\HAL\SevSeg_Interface.h"



const SEVSEG_Ones_Pins_t SEVSEG_Ones_Arr_Pins [SEVSEG_ONES_TOTAL]={
//	    A	B	    C	D	    E	F	    g	dot
//	{PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7},
	};

const SEVSEG_Ones_BCD_Pins_t SEVSEG_Ones_BCD_Arr_Pins [SEVSEG_ONES_BCD_TOTAL]={
//	    A	B	    C	D
//	{PB0, PB1, PB2, PB3},
};

const SEVSEG_Tens_Pins_t SEVSEG_Tens_Arr_Pins [SEVSEG_TENS_TOTAL]={
//	     A	 B	   C 	D	   E 	F	   g 	dot	    A2	 B2	   C2	D2	   E2	F2	   g2	dot2	
//	{PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7, PB0, PB1, PB2, PB3, PB4, PB5, PB6, PB7},
};

const SEVSEG_Tens_BCD_Pins_t SEVSEG_Tens_BCD_Arr_Pins [SEVSEG_TENS_BCD_TOTAL]={
//	   A	      B	  C	     D     A2    B2	  C2    D2
//	{PB0, PB1, PB2, PB3, PB4, PB5, PB6, PB7},
};

const SEVSEG_2_Pins_t SEVSEG_2_Arr_Pins [SEVSEG_2_TOTAL]={
//	    A	B	    C	D	    E	F	    g	dot		1	  2
	{PA1,  PA2, PA3, PA4, PA5, PA6, PA7, PB0, PC6, PC7},
	};