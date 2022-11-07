/******************************************************************************
 *
 * Module: Timer
 *
 * File Name: timer.c
 *
 * Description: Source file for the timer1 driver
 *
 * Author: Mohamed Mohsen
 *
 *******************************************************************************/
#include"timer.h"
#include<avr/io.h>
#include"common_macros.h"
#include<avr/interrupt.h>

/*******************************************************************************
 *                         Types Definition                                   *
 *******************************************************************************/

/* A global pointer to function to set the callback function. */
void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description: ISR of timer1 overflow mode.
 *
 */
ISR(TIMER1_OVF_vect)
{
	if (*g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}

/*
 * Description: ISR of timer1 compare mode.
 *
 */
ISR(TIMER1_COMPA_vect)
{
	if (*g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}

/*
 * Description: A function that initialize a timer1 with dynamic configurations.
 *
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr)
{
	TCCR1A=0;
	TCNT1=Config_Ptr->initial_value;

	SET_BIT(TCCR1A,FOC1A);
	SET_BIT(TCCR1A,FOC1B);

	TCCR1B=(TCCR1B & 0xF8) | (Config_Ptr->prescaler);


	if(Config_Ptr->mode==NORMAL)
	{
		SET_BIT(TIMSK,TOIE1);

	}

	else if((Config_Ptr->mode)==CTC)

	{
		SET_BIT(TCCR1B,WGM12);

		OCR1A=Config_Ptr->compare_value;

		SET_BIT(TIMSK,OCIE1A);


	}

}

/*
 * Description: A function that make a timer1 equal 0.
 *
 */
void Timer1_deInit(void)
{
	TCNT1=0;
	OCR1A=0;
	TCCR1A=0;
	TCCR1B=0;
	CLEAR_BIT(TIMSK, TOIE1); /* disable interrupts for overflow mode */
	CLEAR_BIT(TIMSK, OCIE1A); /* disable interrupts for CTC mode */
	g_callBackPtr = NULL_PTR;
}

/*
 * Description: Function to set the Call Back function address.
 */
void Timer1_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr=a_ptr;
}


