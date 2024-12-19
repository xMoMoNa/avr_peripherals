/*
* SevSeg_Interface.h
*
* Created: 2024-03-08 4:06:45 AM
*  Author: Mohammed
*/


#ifndef SEVSEG_INTERFACE_H_
#define SEVSEG_INTERFACE_H_

// use COM_CATHOD or COM_ANODE
#define SEVSEG_CONNECTION	COM_CATHOD

typedef enum{
//	SEVSEG_ONES1=0,
	SEVSEG_ONES_TOTAL
}SEVSEG_Ones_t;

typedef enum{
//	SEVSEG_TENS1=0,
	SEVSEG_TENS_TOTAL
}SEVSEG_Tens_t;

typedef enum{
//	SEVSEG_ONES_BCD1=0,
	SEVSEG_ONES_BCD_TOTAL
}SEVSEG_Ones_BCD_t;

typedef enum{
//	SEVSEG_TENS_BCD1=0,
	SEVSEG_TENS_BCD_TOTAL
}SEVSEG_Tens_BCD_t;

typedef enum{
	SEVSEG_2,
	SEVSEG_2_TOTAL
}SEVSEG_2_t;


typedef union{
	struct{
		DIO_Pin_t a;
		DIO_Pin_t b;
		DIO_Pin_t c;
		DIO_Pin_t d;
		DIO_Pin_t e;
		DIO_Pin_t f;
		DIO_Pin_t g;
		DIO_Pin_t dot;
	};
	DIO_Pin_t pin[8];
}SEVSEG_Ones_Pins_t;

typedef union{
	struct{
		DIO_Pin_t a;
		DIO_Pin_t b;
		DIO_Pin_t c;
		DIO_Pin_t d;
	};
	DIO_Pin_t pin[4];
}SEVSEG_Ones_BCD_Pins_t;

typedef union{
	struct{
		DIO_Pin_t a;
		DIO_Pin_t b;
		DIO_Pin_t c;
		DIO_Pin_t d;
		DIO_Pin_t e;
		DIO_Pin_t f;
		DIO_Pin_t g;
		DIO_Pin_t dot;
		DIO_Pin_t a2;
		DIO_Pin_t b2;
		DIO_Pin_t c2;
		DIO_Pin_t d2;
		DIO_Pin_t e2;
		DIO_Pin_t f2;
		DIO_Pin_t g2;
		DIO_Pin_t dot2;
	};
	DIO_Pin_t pin[16];
}SEVSEG_Tens_Pins_t;

typedef union{
	struct{
		DIO_Pin_t a;
		DIO_Pin_t b;
		DIO_Pin_t c;
		DIO_Pin_t d;
		DIO_Pin_t a2;
		DIO_Pin_t b2;
		DIO_Pin_t c2;
		DIO_Pin_t d2;
	};
	DIO_Pin_t pin[8];
}SEVSEG_Tens_BCD_Pins_t;

typedef union{
	struct{
		DIO_Pin_t a;
		DIO_Pin_t b;
		DIO_Pin_t c;
		DIO_Pin_t d;
		DIO_Pin_t e;
		DIO_Pin_t f;
		DIO_Pin_t g;
		DIO_Pin_t dot;
		DIO_Pin_t _1;
		DIO_Pin_t _2;
	};
	DIO_Pin_t pin[10];
}SEVSEG_2_Pins_t;


void SEVSEG_Ones_Init(void);
void SEVSEG_Ones_BCD_Init(void);
void SEVSEG_Tens_Init(void);
void SEVSEG_Tens_BCD_Init(void);
void SEVSEG_2_Init(void);

void SEVSEG_Display_Ones(SEVSEG_Ones_t sevSeg, u8 number);
void SEVSEG_Display_Ones_BCD(SEVSEG_Ones_t sevSeg, u8 number);
void SEVSEG_Display_Tens(SEVSEG_Tens_t sevSeg, u8 number);
void SEVSEG_Display_Tens_BCD(SEVSEG_Tens_t sevSeg, u8 number);
void SEVSEG_Display_2_Digit(SEVSEG_2_t sevSeg, u8 number);
void FreeRTOS_SEVSEG_Display_2_Digit(SEVSEG_2_t sevSeg, u8 number, u8 state);

#endif /* SEVSEG_INTERFACE_H_ */