/*
* ADC.c
*
* Created: 2024-03-17 1:35:30 PM
*  Author: Mohammed
*/
#include "..\std_types.h"
#include "..\memory_map.h"
#include "..\utils.h"
#include "ADC_Interface.h"
extern const u16 nonLinerSensors[TOTAL_NONLINER_SENSOR][TOTAL_POINTS][2];
extern const ADC_Channel_t NonLinearSensorsChannels [TOTAL_NONLINER_SENSOR];
extern const ADC_Channel_t LinearSensorsChannels[TOTAL_LINER_SENSOR];
void ADC_Init(ADC_V_Ref_t ref, ADC_Prescaler_t prescaler){
	switch(ref){
		case AREF:
		ClearBit(ADMUX, REFS1);
		ClearBit(ADMUX, REFS0);
		break;
		case AVCC:
		SetBit(ADMUX, REFS1);
		ClearBit(ADMUX, REFS0);
		break;
		case V256:
		SetBit(ADMUX, REFS1);
		SetBit(ADMUX, REFS0);
		break;
	}
	
	ADCSRA&=0xf8;
	ADCSRA|=prescaler;
}

u16 ADC_ReadLiner(ADC_LinerSensors_t sensor){
	u16 result;
	SetBit(ADCSRA, ADEN);
	ADMUX&=0xe0;
	ADMUX|=LinearSensorsChannels[sensor];
	SetBit(ADCSRA, ADSC);
	while (ReadBit(ADCSRA, ADSC));
	result= (ADCL);
	result|=(ADCH<<8);
	ClearBit(ADCSRA, ADEN);
	return result;
}

s32 ADC_ReadNonLiner(ADC_NonLinerSensor_t sensor, u16 amplification){
	u8 i;
	u16 read=ADC_ReadLiner(NonLinearSensorsChannels[sensor]);
	for(i=1; i<TOTAL_POINTS; i++){
		if (read<nonLinerSensors[sensor][i][0]){
			return LinerMapping(nonLinerSensors[sensor][i-1][0], nonLinerSensors[sensor][i-1][1]*amplification,
			nonLinerSensors[sensor][i][0],nonLinerSensors[sensor][i][1]*amplification, read);
		}
	}
}