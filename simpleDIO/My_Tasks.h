/*
 * My_Tasks.h
 *
 * Created: 5/3/2024 2:07:49 AM
 *  Author: Mohammed
 */ 


#ifndef MY_TASKS_H_
#define MY_TASKS_H_

typedef enum{
	STOPWATCH_MODE_PAUSE,
	STOPWATCH_MODE_RESUME,
	STOPWATCH_MODE_RESET,
	STOPWATCH_MODE_EDIT,
	STOPWATCH_MODE_NORMAL
}Stopwatch_Mode_t;
void taskInitEcu(void);
void sevseg_2_update(void *ptr);
void task_button(void *ptr);
void task_Normal(void *ptr);
void task_Reset(void *ptr);
void task_Edit(void *ptr);


#endif /* MY_TASKS_H_ */