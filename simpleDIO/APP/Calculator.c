/*
 * Calculator.c
 *
 * Created: 2024-03-16 7:32:50 AM
 *  Author: Mohammed
 */ 
#include "..\std_types.h"
s16 str2num(u8* str){
	s16 num = 0;
	u8 i=0;
	while (str[i]){
		num=num*10+str[i]-'0';
		i++;
	}
	return num;
}

u32 Solve_Equation(u8 equation[11]){
	s32 result=0;
	return result;
}