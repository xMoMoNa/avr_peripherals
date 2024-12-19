/*
 * utils.h
 *
 * Created: 2024-01-30 1:47:54 PM
 *  Author: Mohammed
 */ 


#ifndef UTILS_H_
#define UTILS_H_


#define ReadBit(reg, bit) (((reg)>>(bit))&1)
#define SetBit(reg, bit) ((reg)=(reg)|(1<<(bit)))
#define ClearBit(reg, bit) ((reg)=(reg)&~(1<<(bit)))
#define ToggleBit(reg, bit) ((reg)=(reg)^(1<<(bit)))
#define SetPort(reg) ((reg)=-1)
#define ClearPort(reg) ((reg)=0)
#define LinerMapping(X_min, Y_min, X_max, Y_max, X_point)	(Y_min)+((X_point)-(X_min))*((s32)(Y_max)-(Y_min))/((X_max)-(X_min))


#endif /* UTILS_H_ */