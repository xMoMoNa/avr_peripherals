#define PROJECT_CODE 23

#if PROJECT_CODE == 0 //test code  for sessions
#include "std_types.h"
#include "MCAL/DIO_Interface.h"
#define F_CPU 8000000UL
#include <util/delay.h>
int main(){
	DIO_Init();
	DIO_WritePin(PC0, HIGH);
	DIO_WritePin(PC1, LOW);
	while (1){
		_delay_ms(2000);
		DIO_TogglePin(PC0);
		DIO_TogglePin(PC1);
	}
}

#elif PROJECT_CODE == 1 // two button to move led of 8 led in two direction
#include "std_types.h"
#include "utils.h"
#include "MCAL/DIO_Interface.h"
#define F_CPU 8000000UL
#include <util/delay.h>
int main(void)
{
	
	DIO_Init();
	DIO_Pin_t pin=PA0;
	u8 flagUp=0, flagDown=0, first_time=0;
	while (1)
	{
		
		if(DIO_ReadPin(PC0)==LOW){
			if(pin==PA7){
				pin=PA0;
				flagUp=0;
			}
			else{
				flagUp=1;
			}
			if (flagUp&&first_time)
			{
				pin++;
			}
			first_time=1;
			DIO_WritePort(PA,LOW);
			DIO_WritePin(pin,HIGH);
			
		}
		else if(DIO_ReadPin(PC1)==LOW){
			if(pin==(PA0)){
				pin=PA7;
				flagDown=0;
			}
			else{
				flagDown=1;
			}
			if (flagDown)
			{
				pin--;
			}
			DIO_WritePort(PA,LOW);
			DIO_WritePin(pin,HIGH);
		}
		_delay_ms(250);
	}
	
}

#elif PROJECT_CODE == 2 //one button for running 8 led in different direction
#include "std_types.h"
#include "utils.h"
#include "MCAL/DIO_Interface.h"
#define F_CPU 8000000UL
#include <util/delay.h>
int main(void){
	DIO_Pin_t pin=PA0;
	u8 flagUp=0, flagDown=0, first_time=0, direction=1;
	DIO_Init();
	while(1){
		if(DIO_ReadPin(PC0)==0){
			direction^=1;
			while(DIO_ReadPin(PC0)==0);
		}
		if(direction){
			if(pin==PA7){
				pin=PA0;
				flagUp=0;
			}
			else{
				flagUp=1;
			}
			if (flagUp&&first_time)
			{
				pin++;
			}
			first_time=1;
			DIO_WritePort(PA,LOW);
			DIO_WritePin(pin,HIGH);
		}
		else{
			if(pin==(PA0)){
				pin=PA7;
				flagDown=0;
			}
			else{
				flagDown=1;
			}
			if (flagDown){
				pin--;
			}
			DIO_WritePort(PA,LOW);
			DIO_WritePin(pin,HIGH);
		}
		for(u8 i =0; i<5 && DIO_ReadPin(PC0) !=0; i++){
			_delay_ms(100);
		}
	}
}

#elif PROJECT_CODE == 3 // Motor test code

#include "std_types.h"
#include "MCAL/DIO_Interface.h"
#include "HAL/Motors_Interface.h"
#define F_CPU 8000000UL
#include <util/delay.h>

int main(void){
	Motor_Init();
	while (1){
		#define MOTOR_CODE 2
		#if MOTOR_CODE == 1
		Motor_Start(M1, MOTOR_CCW);
		Motor_Stop(M2);
		Motor_Stop(M3);
		Motor_Stop(M4);
		_delay_ms(1000);
		Motor_Start(M2, MOTOR_CCW);
		Motor_Stop(M1);
		Motor_Stop(M3);
		Motor_Stop(M4);
		_delay_ms(1000);
		Motor_Start(M3, MOTOR_CCW);
		Motor_Stop(M2);
		Motor_Stop(M1);
		Motor_Stop(M4);
		_delay_ms(1000);
		Motor_Start(M4, MOTOR_CCW);
		Motor_Stop(M2);
		Motor_Stop(M3);
		Motor_Stop(M1);
		_delay_ms(1000);
		#elif MOTOR_CODE == 1
		for (MOTOR_t mstart=M1; mstart<TOTAL_MOTORS; mstart++){
			Motor_Start(mstart, MOTOR_CCW);
			for (MOTOR_t mstop=M1; mstop<TOTAL_MOTORS; mstop++){
				if (mstop==mstart){
					continue;
				}
				Motor_Stop(mstop);
			}
			_delay_ms(1000);
		}
		#endif //for motor code
	}
}

#elif PROJECT_CODE == 4 // stopwatch project
#include "MCAL/DIO_Interface.h"
#include "HAL/SevSeg_Interface.h"
#include "APP/Stopwatch_Interface.h"
#define F_CPU 8000000UL
#include <util/delay.h>

#define LED_PIN	PC5
void techDelay(u8* tech){
	if (*tech<=80){
		_delay_ms(15);
	}
	else if(*tech<=120){
		_delay_ms(7);
	}
	else if (*tech<=160){
		_delay_ms(3);
	}
	else if (*tech>160){
		_delay_ms(1);
	}
	if (*tech==200){
		*tech=160;
	}
}
int main(void){
	u8 Stopwatch_Default_Start = 10, Pressed_P=0, Pressed_E=0, Pressed_R=0, flag_P=0, flag_E=0, flag_R=0;
	u8 i=Stopwatch_Default_Start, click=6, tech=0;
	Stopwatch_Mode_t stopwatch_mode= STOPWATCH_MODE_RESUME;
	#if STOPWATCH_PRESET == 2
	u8 d1=Stopwatch_Default_Start%10;
	u8 d2=Stopwatch_Default_Start/10;
	#endif
	DIO_Init();
	SEVSEG_2_Init();
	while(1){
		for(u16 t=0; t<STOPWATCH_PERIOD_MS/2; t++){
			SEVSEG_Display_2_Digit(SEVSEG_2, i);
			Presed_Button(&Pressed_P, &Pressed_R, &Pressed_E);
			if(Pressed_R){
				stopwatch_mode=STOPWATCH_MODE_RESET;
				break;
			}
			if (Pressed_E)
			{
				stopwatch_mode=STOPWATCH_MODE_EDIT;
				break;
			}
			if (Pressed_P)
			{
				stopwatch_mode=STOPWATCH_MODE_PAUSE;
				break;
			}
		}
		if(i==0){
			tech=6;
			while (1){
				SEVSEG_Display_2_Digit(SEVSEG_2, 0);
				tech++;
				if (tech==0){
					tech=6;
					DIO_TogglePin(LED_PIN);
				}
				if (DIO_ReadPin(PIN_RESET) == LOW ){
					stopwatch_mode = STOPWATCH_MODE_RESET;
					DIO_WritePin(LED_PIN, LOW);
					break;
				}
				if (DIO_ReadPin(PIN_MODE) == LOW){
					stopwatch_mode = STOPWATCH_MODE_EDIT;
					DIO_WritePin(LED_PIN, LOW);
					break;
				}
			}
		}
		i--;
		/************************* reset mode *************************/
		if (stopwatch_mode==STOPWATCH_MODE_RESET){ //complete
			i=Stopwatch_Default_Start;
			stopwatch_mode=STOPWATCH_MODE_RESUME;
		}
		/************************* pause mode *************************/
		if (stopwatch_mode == STOPWATCH_MODE_PAUSE){ //complete
			if (Pressed_P){
				flag_P = 1;
				click=0;
				while(1) {
					SEVSEG_Display_2_Digit(SEVSEG_2, i);
					flag_P=Pressed_P;
					Presed_Button(&Pressed_P, &Pressed_R, &Pressed_E);
					if (flag_P != Pressed_P){
						click++;
					}
					if (click>2 && Pressed_P==0){
						break;
					}
				}
			}
			stopwatch_mode=STOPWATCH_MODE_RESUME;
		}
		/************************* Edit mode *************************/
		if (stopwatch_mode == STOPWATCH_MODE_EDIT){ //complete
			click=0;
			tech=0;
			while (1){
				SEVSEG_Display_2_Digit(SEVSEG_2, Stopwatch_Default_Start);
				flag_E=Pressed_E;
				flag_P=Pressed_P;
				flag_R=Pressed_R;
				Presed_Button(&Pressed_P, &Pressed_R, &Pressed_E);
				if (flag_E != Pressed_E){
					click++;
				}
				if (click>2 && Pressed_E==0){
					click=0;
					i=Stopwatch_Default_Start;
					break;
				}
				#if STOPWATCH_PRESET	== 1 //complete
				// preset 1 Two button 1 for increment and other for  decrement
				if (Pressed_P==1){ // increment
					tech++;
					if(tech%20==0 || flag_P ==0){
						Stopwatch_Default_Start++;
						if (Stopwatch_Default_Start>99){
							Stopwatch_Default_Start =1;
						}
					}
					techDelay(&tech);
					flag_P=1;
				}
				else if (Pressed_R==1){ // decrement
					tech++;
					if(tech%20==0 || flag_R ==0){
						Stopwatch_Default_Start--;
						if (Stopwatch_Default_Start<1){
							Stopwatch_Default_Start=99;
						}
					}
					techDelay(&tech);
					flag_R=1;
				}
				else{
					tech=0;
					flag_P=0;
					flag_R=0;
				}// preset 1 end
				#elif STOPWATCH_PRESET == 2 //complete
				//preset 2 for increment only and  truncate to 0
				if (Pressed_R ==0 && flag_R != Pressed_R){ // increment ones
					
					d1++;
					if (d1==10 && d2 !=0){
						d1=0;
						}else if(d1==10 && d2 ==0){
						d1=1;
					}
					Stopwatch_Default_Start=d1+d2*10;
				}
				else if (Pressed_P==0 && flag_P != Pressed_P){ // increment tens
					d2++;
					if (d2==10){
						d2=0;
					}
					Stopwatch_Default_Start=d1+d2*10;
				}// preset 2 end
				#endif
			}
			stopwatch_mode=STOPWATCH_MODE_RESUME;
		}
	} // super loop end
}// program end

#elif PROJECT_CODE == 5 // LCD
#include "MCAL/DIO_Interface.h"
#include "HAL/LCD_Interface.h"
#define F_CPU 8000000UL
#include <util/delay.h>
int main(void){
	u8 i=0;
	u8 pattern[7]={0x04, 0x0A, 0x04, 0x15, 0x0E, 0x04, 0x0A};
	u8 pattern2[7]={0x00, 0x0E, 0x19, 0x19, 0x0E, 0x00, 0x00};
	LCD_Init();
	#define PATTERN_MAN			1
	#define PATTERN_BULLET		2
	LCD_GenerateChar(LCD1, pattern, PATTERN_MAN);
	LCD_GenerateChar(LCD1, pattern2, PATTERN_BULLET);
	while(1){ // Not finished, think in struct (u8[32] and cursor).
		LCD_SetCursor(LCD1,0);
		LCD_SendChar(LCD1, PATTERN_MAN, DIRECTION_UP);
		LCD_SendChar(LCD1, PATTERN_BULLET, DIRECTION_UP);
		LCD_SetCursor(LCD1,15);
		LCD_SendChar(LCD1, PATTERN_MAN, DIRECTION_UP);
		LCD_SetCursor(LCD1,1);
		for (i=2; i<15; i++){
			LCD_SetCursor(LCD1,i-1);
			LCD_SendChar(LCD1, ' ', DIRECTION_UP);
			LCD_SetCursor(LCD1,i);
			LCD_SendChar(LCD1, PATTERN_BULLET, DIRECTION_UP);
			_delay_ms(200);
		}
		LCD_SetCursor(LCD1,i-1);
		LCD_SendChar(LCD1, ' ', DIRECTION_UP);
		LCD_SendChar(LCD1, ' ', DIRECTION_UP);
		for (i=0; i<10; i++){
			LCD_SetCursor(LCD1, 0);
			LCD_SendChar(LCD1, ' ', DIRECTION_UP);
			LCD_SetCursor(LCD1, 16);
			LCD_SendChar(LCD1, PATTERN_MAN, DIRECTION_UP);
			_delay_ms(100);
			LCD_SetCursor(LCD1, 16);
			LCD_SendChar(LCD1, ' ', DIRECTION_UP);
			LCD_SetCursor(LCD1, 0);
			LCD_SendChar(LCD1, PATTERN_MAN, DIRECTION_UP);
			_delay_ms(100);
		}
	}
}

#elif PROJECT_CODE == 6 // Keypad calculator
#include "MCAL/DIO_Interface.h"
#include "HAL/LCD_Interface.h"
#include "HAL/KeyPad_Interface.h"
#define F_CPU 8000000UL
#include <util/delay.h>
int main(void){
	LCD_Init();
	KeyPad_4x4_Init();
	LCD_Shift_Direction_t direction = DIRECTION_UP;
	s16 num1 =0, num2=0;
	u8 op=0, finished=0, key;
	while (1){
		key=KeyPad_4x4_ReadKey(KEYPAD_4X4_1);
		if (key!=0 && LCD_ReadCursor(LCD1)<11){
			if (key>='0' && key<='9'){
				if (finished==1){
					LCD_ClearScreen(LCD1);
					finished=0;
				}
				LCD_SendChar(LCD1, key, direction);
				num2=num2*10+key-'0';
			}
			else if (key=='c'){
				LCD_ClearScreen(LCD1);
				num2=0;
				num1=0;
			}
			else if(key=='+'){
				op='+';
				if (finished==1){
					finished=0;
					num2 = num1;
					LCD_ClearScreen(LCD1);
					LCD_SendNumber(LCD1, num1,direction);
				}
				LCD_SendChar(LCD1,'+', direction);
				num1=num2;
				num2=0;
			}
			else if(key=='-'){
				op='-';
				if (finished==1){
					finished=0;
					num2 = num1;
					LCD_ClearScreen(LCD1);
					LCD_SendNumber(LCD1, num1,direction);
				}
				LCD_SendChar(LCD1,'-', direction);
				num1=num2;
				num2=0;
			}
			else if(key=='*'){
				op='*';
				if (finished==1){
					finished=0;
					num2 = num1;
					LCD_ClearScreen(LCD1);
					LCD_SendNumber(LCD1, num1,direction);
				}
				LCD_SendChar(LCD1,'*', direction);
				num1=num2;
				num2=0;
			}
			else if(key=='/'){
				op='/';
				if (finished==1){
					finished=0;
					num2 = num1;
					LCD_ClearScreen(LCD1);
					LCD_SendNumber(LCD1, num1,direction);
				}
				LCD_SendChar(LCD1,'/', direction);
				num1=num2;
				num2=0;
			}
			else if(key== '='){
				LCD_SetCursor(LCD1,16);
				if (op=='/'){
					if (num2!=0)
					{
						num1=num1/num2;
						LCD_SendNumber(LCD1, num1, direction);
						}else{
						LCD_SendString(LCD1, "Error!", direction);
					}
				}
				else if(op=='*'){
					num1=num1*num2;
					LCD_SendNumber(LCD1, num1, direction);
				}
				else if(op=='+'){
					num1=num1+num2;
					LCD_SendNumber(LCD1, num1, direction);
				}
				else if(op=='-'){
					num1=num1-num2;
					LCD_SendNumber(LCD1, num1, direction);
				}
				op=0;
				finished=1;
				LCD_SetCursor(LCD1,0);
			}
			_delay_ms(500);
		}
	}

}

#elif PROJECT_CODE == 7 // keypad converter
#include "MCAL/DIO_Interface.h"
#include "HAL/LCD_Interface.h"
#include "HAL/KeyPad_Interface.h"
#include "APP/convertNumber_Interface.h"
#define F_CPU 8000000UL
#include <util/delay.h>

int main(void){
	NumberType_t from, to;
	convert_State_t state=RETURN;
	LCD_Init();
	KeyPad_4x4_Init();
	Screen_Welcome();
	while(1){
		if (state==RETURN){
			from=Screen_Convert_From();
			to=Screen_Convert_To();
			state=Screen_Converter(from, to);
		}
		else{
			state=Screen_Converter(from, to);
		}
	}
}

#elif PROJECT_CODE == 8 // ADC
#include "std_types.h"
#include "utils.h"
#include "MCAL/ADC_Interface.h"
#include "MCAL/DIO_Interface.h"
#include "HAL/LCD_Interface.h"
#define F_CPU 8000000UL
#include <util/delay.h>

#define ADCPROJECT	3
int main(void){
	s32 read, lastRead=0, i=0;
	DIO_Init();
	ADC_Init(AREF, ADC_SCALER_64);
	LCD_Init();
	while(1){
		#if ADCPROJECT == 1 // make sound volumeter
		read=ADC_ReadLiner(ADC0)*16/1023;
		if (lastRead!= read){
			LCD_ClearScreen(LCD1);
			for (i=0; i<read; i++){
				LCD_SendChar(LCD1, '>', DIRECTION_UP);
			}
			lastRead=read;
		}
		#elif ADCPROJECT ==2 // mapping 20 volt to 5 volt
		LCD_SetCursor(LCD1,0);
		read=(s32)ADC_ReadLiner(ADC7)*5000*4/1024;
		LCD_SendFloat(LCD1, read, 3, DIRECTION_UP);
		LCD_SendChar(LCD1, 'V', DIRECTION_UP);
		while(1);
		#elif ADCPROJECT ==3 // non-linear sensors
		read=ADC_ReadLiner(LINER_SENSOR1);
		if (lastRead!=read){
			lastRead=read;
			LCD_ClearScreen(LCD1);
			LCD_SendNumber(LCD1, read, DIRECTION_UP);
			LCD_SetCursor(LCD1, 16);
			read=ADC_ReadNonLiner(NONLINER_SENSOR_1, 10);
			LCD_SendFloat(LCD1, read, 1, DIRECTION_UP);
		}
		#endif
		
	}
	
}


#elif PROJECT_CODE == 9 // external interrupt
#include "memory_map.h"
#include "std_types.h"
#include "utils.h"
#include "MCAL/DIO_Interface.h"
#include "MCAL/External_Interrupt_Interface.h"
#define F_CPU 8000000UL
#include <util/delay.h>
void fun(){
	DIO_TogglePin(PC0);
}
int main(void)
{
	DIO_Init();
	EXT_INT_Init(EXT0, FALL_EDGE, fun);
	sei();
	while(1){
		
	}
}

#elif PROJECT_CODE == 10 // temp filter
#include "std_types.h"
#include "memory_map.h"
#include "MCAL/DIO_Interface.h"
#include "MCAL/ADC_Interface.h"
#include "MCAL/External_Interrupt_Interface.h"
#include "HAL/LCD_Interface.h"
#include "APP/TempFilter.h"

#define F_CPU	8000000UL
#include <util/delay.h>

u8 presed=0;
void fun(void){
	presed=1;
}

int main(void){
	DIO_Init();
	ADC_Init(AREF, ADC_SCALER_64);
	EXT_INT_Init(EXT0, FALL_EDGE, fun);
	LCD_Init();
	TempFilter_Init(LINER_SENSOR1);
	s32 temp=0;
	sei();
	while(1){
		TempFilter_Runnuble(LINER_SENSOR1);

		LCD_ClearScreen(LCD1);
		
		LCD_SetCursor(LCD1,0);
		temp=TempFilter_GetRead(LINER_SENSOR1);
		LCD_SendNumber(LCD1, temp, DIRECTION_UP);

		LCD_SetCursor(LCD1, 16);
		temp=TempFilter_GetInst(LINER_SENSOR1);
		LCD_SendNumber(LCD1, temp, DIRECTION_UP);
		
		
		_delay_ms(300);
	}
}

#elif PROJECT_CODE == 11 //Timer
#include "std_types.h"
#include "utils.h"
#include "memory_map.h"
#include "MCAL/DIO_Interface.h"
#define F_CPU	8000000UL
#include <util/delay.h>

int main(){
	DIO_Init();
	sei();
	TCCR0=0x02;
	SetBit(TIMSK,0);
	TCNT0=6;
	
	while (1){
		
	}
}

ISR(VECT_TIM0_OVF){
	TCNT0=6;
	static u8 c;
	c++;
	if (c%2==0){
		DIO_TogglePin(PC0);
	}
	if (c%4==0){
		DIO_TogglePin(PC1);
	}
	if (c%10==0){
		DIO_TogglePin(PC2);
		if (c==20)c=0;
	}
	
}

#elif PROJECT_CODE == 12 // Timer with motor and pot control speed
#include "std_types.h"
#include "MCAL/DIO_Interface.h"
#include "MCAL/ADC_Interface.h"
#include "MCAL/External_Interrupt_Interface.h"
#include "MCAL/Timers.h"
#include "SERVICES/Timers_Services.h"
#include "HAL/Motors_Interface.h"
#include "HAL/LCD_Interface.h"

#define F_CPU	8000000UL
#include <util/delay.h>
MOTOR_Direction_t direction= MOTOR_CCW;

void fun(void){
	if (direction== MOTOR_CCW)
	{
		direction=MOTOR_CW;
		}else{
		direction=MOTOR_CCW;
	}
	Motor_Direction(M1, direction);
}

int main(void){
	u8 speed=0;
	DIO_Init();
	ADC_Init( AREF, ADC_SCALER_64);
	TIMER0_Init(TIMER0_FASTPWM_MODE, TIMER0_SCALER_8);
	TIMER0_OC0Mode(OC0_INVERTING);
	TIMER0_OC_InterruptDisable();
	TIMER0_OV_InterruptDisable();
	EXT_INT_Init(EXT0, FALL_EDGE, fun);
	Motor_Init();
	Motor_Start(M1, direction);
	LCD_Init();
	OCR0=255;
	sei();
	while(1){
		LCD_ClearScreen(LCD1);
		speed= (u8)(((u16)ADC_ReadLiner(LINER_SENSOR1)*100)/(u16)1024);
		TIMER0_FastPWM(speed);
		LCD_SendNumber(LCD1, OCR0, DIRECTION_UP);
		_delay_ms(300);
	}
}

#elif PROJECT_CODE == 13 //ultrasonic

#include "memory_map.h"
#include "MCAL/DIO_Interface.h"
#include "MCAL/Timers.h"
#include "HAL/LCD_Interface.h"
#include "HAL/UltraSonic_Interface.h"

#define F_CPU	8000000UL
#include <util/delay.h>

int main(void){
	u16 d=0;
	u8 i=0;
	sei();
	DIO_Init();
	Timer1_Init(TIMER1_NORMAL_MODE, TIMER1_SCALER_8);
	
	LCD_Init();
	Ultrasonic_Init();
	LCD_SendString(LCD1, "Distance", DIRECTION_UP);
	while(1){
		Ultrasonic_Runnable();
		LCD_SetCursor(LCD1, 8);
		LCD_SendNumber(LCD1, i+1, DIRECTION_UP);
		LCD_SendString(LCD1, "= ", DIRECTION_UP);
		d=Ultrasonic_GetDistance(i);
		LCD_SendNumber(LCD1, (s32)d, DIRECTION_UP);
		LCD_SendString(LCD1, "cm  ", DIRECTION_UP);
		_delay_ms(1000);
		i=++i%TOTAL_ULTRASONIC;
	}
}

#elif PROJECT_CODE == 14 // servo motor
#include "memory_map.h"
#include "MCAL/DIO_Interface.h"
#include "MCAL/Timers.h"
#include "HAL/ServoMotor_Interface.h"

#define F_CPU	8000000UL
#include <util/delay.h>

int main(void){
	u8 pos=0;
	DIO_InitPin(PD5, OUTPUT);
	DIO_InitPin(PD3, OUTPUT);
	DIO_WritePin(PD5, LOW);
	DIO_WritePin(PD3, HIGH);
	Timer1_Init(TIMER1_FASTPWM_OCRA_TOP_MODE, TIMER1_SCALER_8);
	Timer1_OCRB1Mode(OCRB_NON_INVERTING);
	ServoMotor_Init();
	while (1){
		if (pos>180){
			pos=0;
		}
		ServoMotor_SetPosition(SERVOMOTOR1, pos);
		_delay_ms(1000);
		pos=pos+30;

	}

}
#elif PROJECT_CODE == 15 // stepper motor
#include "memory_map.h"
#include "MCAL/DIO_Interface.h"
#include "HAL/stepperMotor_Interface.h"

#define F_CPU	8000000UL
#include <util/delay.h>

int main(){
	
	while(1){
		
	}
}
#elif PROJECT_CODE == 16 // rgb
#include "std_types.h"
#include "memory_map.h"
#include "MCAL/DIO_Interface.h"
#include "HAL/LCD_Interface.h"
#include "HAL/RGB_Interface.h"
#define F_CPU	8000000UL
#include <util/delay.h>

int main(void){
	RGB_Color_t color={0xfb, 0x76, 0x0e, 100};
	sei();
	DIO_Init();
	rgb_Init();
	rgb_setColor(RGB_LED1, color);
	_delay_ms(5000);
	color.blue=100;
	color.red=0;
	rgb_setColor(RGB_LED1, color);
	while (1){
		
	}

}

#elif PROJECT_CODE == 17 // uart
#include "std_types.h"
#include "memory_map.h"
#include "MCAL/DIO_Interface.h"
#include "MCAL/UART_Interface.h"
#include "MCAL/Timers.h"
#include "HAL/LCD_Interface.h"
#include "HAL/RGB_Interface.h"
#include "HAL/ServoMotor_Interface.h"
#include "SERVICES/UART_Services.h"
#define F_CPU	8000000UL
#include <util/delay.h>

int main(void){
	u8 i=0;
	sei();
	DIO_Init();
	uart_Init();
	DIO_WritePin(PB0, HIGH);
	uart_taskInit();
	ServoMotor_Init();
	rgb_Init();
	LCD_Init();
	
	u8 pattern[7]={0x04, 0x0A, 0x04, 0x15, 0x0E, 0x04, 0x0A};
	u8 pattern2[7]={0x00, 0x0E, 0x19, 0x19, 0x0E, 0x00, 0x00};

	#define PATTERN_MAN			1
	#define PATTERN_BULLET		2
	LCD_GenerateChar(LCD1, pattern, PATTERN_MAN);
	LCD_GenerateChar(LCD1, pattern2, PATTERN_BULLET);
	
	while(1){
		
		LCD_SetCursor(LCD1,0);
		LCD_SendChar(LCD1, PATTERN_MAN, DIRECTION_UP);
		LCD_SendChar(LCD1, PATTERN_BULLET, DIRECTION_UP);
		LCD_SetCursor(LCD1,15);
		LCD_SendChar(LCD1, PATTERN_MAN, DIRECTION_UP);
		LCD_SetCursor(LCD1,1);
		for (i=2; i<15; i++){
			LCD_SetCursor(LCD1,i-1);
			LCD_SendChar(LCD1, ' ', DIRECTION_UP);
			LCD_SetCursor(LCD1,i);
			LCD_SendChar(LCD1, PATTERN_BULLET, DIRECTION_UP);
			_delay_ms(200);
		}
		LCD_SetCursor(LCD1,i-1);
		LCD_SendChar(LCD1, ' ', DIRECTION_UP);
		LCD_SendChar(LCD1, ' ', DIRECTION_UP);
		for (i=0; i<10; i++){
			LCD_SetCursor(LCD1, 0);
			LCD_SendChar(LCD1, ' ', DIRECTION_UP);
			LCD_SetCursor(LCD1, 16);
			LCD_SendChar(LCD1, PATTERN_MAN, DIRECTION_UP);
			_delay_ms(100);
			LCD_SetCursor(LCD1, 16);
			LCD_SendChar(LCD1, ' ', DIRECTION_UP);
			LCD_SetCursor(LCD1, 0);
			LCD_SendChar(LCD1, PATTERN_MAN, DIRECTION_UP);
			_delay_ms(100);
		}
		
	}
}
#elif PROJECT_CODE == 18 // SPI master
#include "MCAL/DIO_Interface.h"
#include "MCAL/SPI_Interface.h"
#include "HAL/LCD_Interface.h"
#define F_CPU	8000000UL
#include <util/delay.h>
int main(void){
	u8 i='A', d, str[]="Mohammed 0";
	sei();
	DIO_Init();
	spi_Init(SPI_MASTER);
	LCD_Init();
	LCD_SendString(LCD1, "Master", DIRECTION_UP);
	while(1){
		if (str[9]<'9'){
			str[9]++;
			spi_MasterSendReceiveStr(str);
		}
		DIO_TogglePin(PC0);
		LCD_SetCursor(LCD1, 16);
		LCD_SendString(LCD1, str, DIRECTION_UP);
		_delay_ms(500);
	}
}
#elif PROJECT_CODE == 19 // iic and eeprom
#include "MCAL/DIO_Interface.h"
#include "MCAL/iic_Interface.h"
#include "HAL/LCD_Interface.h"
#define F_CPU	8000000UL
#include <util/delay.h>

int main(void){
	u8 i=0, *data;
	sei();
	DIO_Init();
	LCD_Init();
	iic_Init(0x55, IIC_MASTER);
	
	LCD_SendString(LCD1, "TWI Master", DIRECTION_UP);
	_delay_ms(1000);
	iic_MasterSendArr(0x50, "Mohammed", 6);
	while(1){
		LCD_SetCursor(LCD1, 14);
		LCD_SendNumber(LCD1, ++i, DIRECTION_UP);
		_delay_ms(500);
		
	}
	
}

#elif PROJECT_CODE == 20 // internal eeprom
#include "MCAL/DIO_Interface.h"
#include "MCAL/eepromInternal_Interface.h"
#include "HAL/LCD_Interface.h"
#define F_CPU	8000000UL
#include <util/delay.h>

int main(void){
	u8 i=0, data, flag=1;
	sei();
	DIO_Init();
	LCD_Init();
	eepromInt_Int();
	
	LCD_SendString(LCD1, "Write: ", DIRECTION_UP);
	LCD_SetCursor(LCD1, 16);
	LCD_SendString(LCD1, "Read: ", DIRECTION_UP);
	
	eepromInt_Write(500, 20);
	eepromInt_Read(500, &data);
	if (data==20){
		DIO_WritePin(PC0, HIGH);
	}
	_delay_ms(2000);
	while(1){
		if (flag)
		{
			LCD_SetCursor(LCD1, 10);
			LCD_SendNumber(LCD1, i, DIRECTION_UP);
		
			eepromInt_Write(i, i);
		}
		eepromInt_Read(i, &data);
		
		LCD_SetCursor(LCD1, 26);
		LCD_SendNumber(LCD1, data, DIRECTION_UP);
		
		_delay_ms(500);
		i++;
		if (i==13){
			flag=0;
			i=0;
		}
	}
	
}


#elif PROJECT_CODE == 21 // bluetooth driver test

#include "std_types.h"
#include "memory_map.h"
#include "MCAL/DIO_Interface.h"
#include "MCAL/UART_Interface.h"
#include "SERVICES/UART_Services.h"
#include "HAL/LCD_Interface.h"
#include "HAL/bluetooth_Interface.h"
#define F_CPU	8000000UL
#include <util/delay.h>

int main(void){
	u8 c;
	DIO_Init();
	LCD_Init();
	uart_EnableInterrupt_RX();
	uart_Init();
	sei();
	while(1){
		if (uart_recieveAsync(&c)){
			LCD_SendChar(LCD1, c, DIRECTION_UP);
			uart_sendStringAsync("Done");
		}
	}


}


#elif PROJECT_CODE == 22 //FREERTOS


#include "MCAL/DIO_Interface.h"
#include "MCAL/eepromInternal_Interface.h"
#include "HAL/SevSeg_Interface.h"
//#include "HAL/LCD_Interface.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "My_Tasks.h"

#define F_CPU	8000000UL
#include <util/delay.h>


SemaphoreHandle_t btn1Press;
SemaphoreHandle_t btn2Press;
SemaphoreHandle_t btn3Press;

int main(void){
	
	taskInitEcu();
	
	btn1Press=xSemaphoreCreateBinary();
	btn2Press=xSemaphoreCreateBinary();
	btn3Press=xSemaphoreCreateBinary();
	
	xTaskCreate(sevseg_2_update,
	NULL,
	configMINIMAL_STACK_SIZE,
	NULL,
	1,
	NULL);
	
	xTaskCreate(task_button,
	NULL,
	configMINIMAL_STACK_SIZE,
	NULL,
	1,
	NULL);
	
	xTaskCreate(task_Normal,
	NULL,
	configMINIMAL_STACK_SIZE,
	NULL,
	1,
	NULL);
	xTaskCreate(task_Reset,
	NULL,
	configMINIMAL_STACK_SIZE,
	NULL,
	1,
	NULL);
	xTaskCreate(task_Edit,
	NULL,
	configMINIMAL_STACK_SIZE,
	NULL,
	1,
	NULL);
	vTaskStartScheduler();
	
}


#elif PROJECT_CODE == 23 // 4 PWM
#include "std_types.h"
#include "utils.h"
#include "memory_map.h"
#include "MCAL/Timers.h"

#define F_CPU	8000000UL
#include <util/delay.h>

int main(void){
	DIO_Init();
	/*init timer 0*/
	// set pwm mode
	SetBit(TCCR0,WGM00);
	SetBit(TCCR0,WGM01);
	
	//set scale 1 mhz
	TCCR0&=0XF8;//0b11111000
	TCCR0|=3;
	
	// set non inverting mode clear on compare match
	ClearBit(TCCR0,COM00);
	SetBit(TCCR0,COM01);
	
	/*init timer 2*/
	// set pwm mode
	SetBit(TCCR2,WGM20);
	SetBit(TCCR2,WGM21);
	
	//set scale 1 mhz
	TCCR2&=0XF8;//0b11111000
	TCCR2|=3;
	
	// set non inverting mode clear on compare match
	ClearBit(TCCR2,COM20);
	SetBit(TCCR2,COM21);
	
	///*init timer 1*/
	// set pwm mode 8-bit
	SetBit(TCCR1A,WGM10);
	ClearBit(TCCR1A,WGM11);
	SetBit(TCCR1B,WGM12);
	ClearBit(TCCR1B,WGM13);
	//set scale 1 mhz
	TCCR1B&=0XF8;
	TCCR1B|=3;
	
	// set non inverting mode clear on compare match
	SetBit(TCCR1A,COM1A1);//channel A
	ClearBit(TCCR1A,COM1A0);
	SetBit(TCCR1A,COM1B1);//channel b
	ClearBit(TCCR1A,COM1B0);
	

	/**********************************************/
	
	while (1){
	OCR0=128;
	OCR2=128;
	OCR1A=128;
	OCR1B=128;
	_delay_ms(2000);
	OCR0=255;
	OCR2=128;
	OCR1A=255;
	OCR1B=128;
	_delay_ms(2000);
	OCR0=128;
	OCR2=255;
	OCR1A=128;
	OCR1B=255;
	_delay_ms(2000);
	OCR0=255;
	OCR2=255;
	OCR1A=255;
	OCR1B=255;
	_delay_ms(2000);
		
	}
}

#endif //for program code
