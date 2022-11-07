/******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.h
 *
 * Description: Header file for the buzzer driver
 *
 * Author: Mohamed Mohsen
 *
 *******************************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_

#include"std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define BUZZER_PORT  PORTA_ID
#define BUZZER_PIN   PIN0_ID

/*******************************************************************************
 *                      Functions Declarations                                  *
 *******************************************************************************/

/*
 * Description: A function to initialize the buzzer.
 *
 */
void Buzzer_init(void);

/*
 * Description: A function to enable the buzzer.
 *
 */
void Buzzer_on(void);

/*
 * Description: A function to disable the buzzer.
 *
 */
void Buzzer_off(void);


#endif /* BUZZER_H_ */
