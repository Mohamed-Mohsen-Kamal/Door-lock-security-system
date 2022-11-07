/******************************************************************************
 *
 * Module: DC_MOTOR
 *
 * File Name: dc_motor.h
 *
 * Description: Header file for the DC_MOTOR driver
 *
 * Author: Mohamed Mohsen
 *
 *******************************************************************************/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_
#include"std_types.h"

/*******************************************************************************
 *                         Definitions                                         *
 *******************************************************************************/

#define Motor_Port PORTB_ID
#define Motor_Input1 PIN1_ID
#define Motor_Input2 PIN2_ID

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

/*
 * Description : Enum contains the different modes of the motor.
 */

typedef enum
{
	stop,CW,A_CW
}DcMotor_State;

/*******************************************************************************
 *                         Functions Prototypes                                          *
 *******************************************************************************/

/*
 * Description : The Function is responsible for
 *   setup the direction for the two motor pins
 *   through the GPIO driver.
 *   As an initialization, The motor is at rest.

 */
void DcMotor_Init(void);

/*
 * Description:A Function to select the motor mode as clock-wise(CW)
 * or anti clock-wise(A_CW) or OFF.
 *  It sends the speed to PWM module to achieve the correct duty-cycle.
 */
void DcMotor_Rotate(DcMotor_State state);

#endif /* DC_MOTOR_H_ */
