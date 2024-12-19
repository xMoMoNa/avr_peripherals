/*
 * stepperMotor_Interface.h
 *
 * Created: 4/4/2024 2:20:34 PM
 *  Author: Mohammed
 */ 


#ifndef STEPPERMOTOR_INTERFACE_H_
#define STEPPERMOTOR_INTERFACE_H_

typedef enum{
	STEPPERMOTOR1,
	TOTAL_STEPPERMOTOR
}StepperMotor_t;

typedef union{
struct{
	DIO_Pin_t pin1;
	DIO_Pin_t pin2;
	DIO_Pin_t pin3;
	DIO_Pin_t pin4;
};
DIO_Pin_t pin[4];	
}StepperMotor_Pins_t;


typedef enum{
	MOTOR_CW=0,
	MOTOR_CCW
}MOTOR_Direction_t;


void StepperMotor_Init(void);
void StepperMotor_Rotate(StepperMotor_t stepper, u16 angle, MOTOR_Direction_t direction);

#endif /* STEPPERMOTOR_INTERFACE_H_ */