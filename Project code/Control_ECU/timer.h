 /******************************************************************************
 *
 * Module: Timer
 *
 * File Name: timer.h
 *
 * Description: Header file for the timer1 driver
 *
 * Author: Mohamed Mohsen
 *
 *******************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_

#include"std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define TIMER1_MAX_VALUE 65535

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024,EXTERNAL_FAALLING,EXTERNAL_RISING
}Timer1_Prescaler;

typedef enum
{
	NORMAL,CTC
}Timer1_Mode;

typedef struct {
uint16 initial_value;
uint16 compare_value; // it will be used in compare mode only.
Timer1_Prescaler prescaler;
Timer1_Mode mode;
} Timer1_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description: A function that initialize a timer1 with dynamic configurations.
 *
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr);

/*
 * Description: A function that make a timer1 equal 0.
 *
 */
void Timer1_deInit(void);

/*
 * Description: Function to set the Call Back function address.
 */
void Timer1_setCallBack(void(*a_ptr)(void));








#endif /* TIMER_H_ */
