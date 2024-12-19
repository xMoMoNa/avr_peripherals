/*
* ADC_Cfg.c
*
* Created: 2024-03-21 5:41:23 AM
*  Author: Mohammed
*/
#include "..\std_types.h"
#include "..\MCAL\ADC_Interface.h"
/*
You must define in interface layer:
1- LINER_SENSORS names.
2- NONLINER_SENSORS names
3- if we have non-liner sensors define how many point you take to interpolate.
*/
const ADC_Channel_t NonLinearSensorsChannels [TOTAL_NONLINER_SENSOR]={};
const ADC_Channel_t LinearSensorsChannels[TOTAL_LINER_SENSOR]={ADC0};
const u16 nonLinerSensors[TOTAL_NONLINER_SENSOR][TOTAL_POINTS][2]={
	{{0,0},{50,10},{55,30},{70,50},{500,100},{1024,1024}}
};
/*
6 point taked
x	y
0	0
50	10
55	30
70	50
500	100
1024	1024
*/