/*
 * Motors.c
 *
 * Created: 2024-03-07 4:52:11 AM
 *  Author: Mohammed
 */
 #include "..\std_types.h"
 #include "..\utils.h"
 #include "..\MCAL\DIO_Interface.h"
 #include "..\HAL\Motors_Interface.h"
 
const MOTOR_Pin_t motors_Pins_Array[TOTAL_MOTORS];
 
 void Motor_Init(){
	 for(MOTOR_t motor_num=0; motor_num<TOTAL_MOTORS; motor_num++){
		 DIO_InitPin(motors_Pins_Array[motor_num].enable, OUTPUT);
		 DIO_InitPin(motors_Pins_Array[motor_num].in1, OUTPUT);
		 DIO_InitPin(motors_Pins_Array[motor_num].in2, OUTPUT);
	 }
 }
 void Motor_Start(MOTOR_t motor, MOTOR_Direction_t direction){
	 DIO_WritePin(motors_Pins_Array[motor].enable, HIGH);
	 switch(direction){
		 case MOTOR_CCW:
		 DIO_WritePin(motors_Pins_Array[motor].in1, HIGH);
		 DIO_WritePin(motors_Pins_Array[motor].in2, LOW);
		 break;
		 case MOTOR_CW:
		 DIO_WritePin(motors_Pins_Array[motor].in2, HIGH);
		 DIO_WritePin(motors_Pins_Array[motor].in1, LOW);
		 break;
	 }
 }
 void Motor_Direction(MOTOR_t motor, MOTOR_Direction_t direction){
	 switch(direction){
		 case MOTOR_CCW:
		 DIO_WritePin(motors_Pins_Array[motor].in1, HIGH);
		 DIO_WritePin(motors_Pins_Array[motor].in2, LOW);
		 break;
		 case MOTOR_CW:
		 DIO_WritePin(motors_Pins_Array[motor].in2, HIGH);
		 DIO_WritePin(motors_Pins_Array[motor].in1, LOW);
		 break;
	 }
	 
 }
 void Motor_Speed(u8 speed){
	 
 }
 void Motor_Stop(MOTOR_t motor){
	 DIO_WritePin(motors_Pins_Array[motor].enable, LOW);
 }
 
