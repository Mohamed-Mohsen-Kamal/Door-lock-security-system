/******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.c
 *
 * Description: Source file for the buzzer driver
 *
 * Author: Mohamed Mohsen
 *
 *******************************************************************************/
#include"buzzer.h"
#include"gpio.h"
#include"common_macros.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description: A function to initialize the buzzer.
 *
 */
void Buzzer_init(void)
{
	GPIO_setupPinDirection(BUZZER_PORT, BUZZER_PIN, PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_LOW);
}

/*
 * Description: A function to enable the buzzer.
 *
 */
void Buzzer_on(void)
{
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_HIGH);

}

/*
 * Description: A function to disable the buzzer.
 *
 */
void Buzzer_off(void)
{
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_LOW);
}
