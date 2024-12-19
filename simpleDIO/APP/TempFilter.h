/*
 * TempFilter.h
 *
 * Created: 3/27/2024 6:46:50 AM
 *  Author: Mohammed
 */ 
 

#ifndef TEMPFILTER_H_
#define TEMPFILTER_H_
#include "..\MCAL\ADC_Interface.h"
void TempFilter_Init(ADC_LinerSensors_t sensor);
void TempFilter_Runnuble(ADC_LinerSensors_t sensor);
s32 TempFilter_GetRead(ADC_LinerSensors_t sensor);
s32 TempFilter_GetInst(ADC_LinerSensors_t sensor);

#endif /* TEMPFILTER_H_ */