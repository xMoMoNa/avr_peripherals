/*
 * Motors_Interface.h
 *
 * Created: 2024-03-07 4:52:43 AM
 *  Author: Mohammed
 */ 


#ifndef MOTORS_INTERFACE_H_
#define MOTORS_INTERFACE_H_
#include "..\std_types.h"

typedef enum{
	MOTOR_CW=0,
	MOTOR_CCW
	}MOTOR_Direction_t;
typedef struct{
	DIO_Pin_t in1;
	DIO_Pin_t in2;
	DIO_Pin_t enable;
	}MOTOR_Pin_t;
typedef enum{
	M1=0,
//	M2,
//	M3,
//	M4,
	TOTAL_MOTORS
	}MOTOR_t;
	
void Motor_Init();
void Motor_Start(MOTOR_t motor, MOTOR_Direction_t direction);
void Motor_Direction(MOTOR_t motor, MOTOR_Direction_t direction);
void Motor_Speed(u8 speed);
void Motor_Stop(MOTOR_t motor);


#endif /* MOTORS_INTERFACE_H_ */