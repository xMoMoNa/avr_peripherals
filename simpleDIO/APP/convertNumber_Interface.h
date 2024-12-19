/*
 * convertNumber_Interface.h
 *
 * Created: 2024-03-16 10:19:34 AM
 *  Author: Mohammed
 */ 


#ifndef CONVERTNUMBER_INTERFACE_H_
#define CONVERTNUMBER_INTERFACE_H_

typedef enum{
	Dec=1,
	Bin=2,
	Hex=3,
	}NumberType_t;
typedef enum{
	CONTINUE,
	RETURN
	}convert_State_t;
s32 Convert2Dec(NumberType_t type );
void Screen_Welcome(void);
NumberType_t Screen_Convert_From(void);
NumberType_t Screen_Convert_To(void);
convert_State_t Screen_Converter(NumberType_t from, NumberType_t to);

#endif /* CONVERTNUMBER_INTERFACE_H_ */