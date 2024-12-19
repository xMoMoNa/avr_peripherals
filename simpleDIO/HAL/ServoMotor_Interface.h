/*
 * ServoMotor_Interface.h
 *
 * Created: 4/4/2024 12:37:27 PM
 *  Author: Mohammed
 */ 


#ifndef SERVOMOTOR_INTERFACE_H_
#define SERVOMOTOR_INTERFACE_H_

typedef enum{
	SERVOMOTOR1,
	TOTAL_SERVOMOTOR
}ServoMotor_t;

void ServoMotor_Init(void);
void ServoMotor_SetPosition(ServoMotor_t servo, u16 pos);
void ServoMotor_stop(void);

#endif /* SERVOMOTOR_INTERFACE_H_ */