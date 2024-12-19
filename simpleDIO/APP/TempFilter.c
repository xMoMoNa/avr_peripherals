/*
* TempFilter.c
*
* Created: 3/27/2024 6:46:34 AM
*  Author: Mohammed
*/
#include "..\std_types.h"
#include "..\MCAL\ADC_Interface.h"
#include "TempFilter.h"

static u16 temp=0, tmp, tempArr[10];
static u8 i=0;

void TempFilter_Init(ADC_LinerSensors_t sensor){
	temp=ADC_ReadLiner(sensor);
};

void TempFilter_Runnuble(ADC_LinerSensors_t sensor){
	static u8 flag=0;
	static u16 sum=0;
	tmp=ADC_ReadLiner(sensor);
	sum+=tmp;
	sum-=tempArr[i];
	tempArr[i++]=tmp;
	if (i==10){
		i=0;
		flag=1;
	}
	
	if (flag){
		temp=sum/10;
	}
	else{
		temp=sum/i;
	}
}

s32 TempFilter_GetRead(ADC_LinerSensors_t sensor){
	return (s32)205*temp/1024-55;
}

s32 TempFilter_GetInst(ADC_LinerSensors_t sensor){
	return (s32)205*ADC_ReadLiner(sensor)/1024-55;
}