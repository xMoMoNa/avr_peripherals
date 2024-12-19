/*
* ADC_Interface.h
*
* Created: 2024-03-17 1:35:54 PM
*  Author: Mohammed
*/

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

typedef enum{
	//NONLINER_SENSOR_1,
	//NONLINER_SENSOR_2,
	//NONLINER_SENSOR_3,
	TOTAL_NONLINER_SENSOR
}ADC_NonLinerSensor_t;

typedef enum{
	LINER_SENSOR1,
	//LINER_SENSOR2,
	//LINER_SENSOR3,
	TOTAL_LINER_SENSOR
}ADC_LinerSensors_t;

/*define how many number of points take from curve to interpolate*/
#define TOTAL_POINTS 6

/***********************************************/
typedef enum{
	AREF,
	AVCC,
	V256
}ADC_V_Ref_t;

typedef enum{
	ADC0,
	ADC1,
	ADC2,
	ADC3,
	ADC4,
	ADC5,
	ADC6,
	ADC7
}ADC_Channel_t;

typedef enum{
	ADC_SCALER_2=1,
	ADC_SCALER_4,
	ADC_SCALER_8,
	ADC_SCALER_16,
	ADC_SCALER_32,
	ADC_SCALER_64,
	ADC_SCALER_128,
}ADC_Prescaler_t;

void ADC_Init(ADC_V_Ref_t ref, ADC_Prescaler_t prescaler);

u16 ADC_ReadLiner(ADC_LinerSensors_t sensor);

s32 ADC_ReadNonLiner(ADC_NonLinerSensor_t sensor, u16 amplification);

#endif /* ADC_INTERFACE_H_ */