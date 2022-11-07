/******************************************************************************
 *
 * Module: DC_MOTOR
 *
 * File Name: dc_motor.c
 *
 * Description: Source file for the DC_MOTOR driver
 *
 * Author: Mohamed Mohsen
 *
 *******************************************************************************/
#include"dc_motor.h"
#include"gpio.h"
#include"common_macros.h"


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description : The Function is responsible for
 *   setup the direction for the two motor pins
 *   through the GPIO driver.
 *   As an initialization, The motor is at rest.
 */
void DcMotor_Init(void)
{
	GPIO_setupPinDirection(Motor_Port,Motor_Input1,PIN_OUTPUT);
	GPIO_setupPinDirection(Motor_Port,Motor_Input2,PIN_OUTPUT);
	GPIO_writePin(Motor_Port,Motor_Input1,LOGIC_LOW);
	GPIO_writePin(Motor_Port,Motor_Input2,LOGIC_LOW);
}

/*
 * Description:A Function to select the motor mode as clock-wise(CW)
 * or anti clock-wise(A_CW) or OFF.
 *  It sends the speed to PWM module to achieve the correct duty-cycle.
 */

void DcMotor_Rotate(DcMotor_State state)
{
	if(state==stop)
	{
		GPIO_writePin(Motor_Port,Motor_Input1,LOGIC_LOW);
		GPIO_writePin(Motor_Port,Motor_Input2,LOGIC_LOW);
	}
	else if(state==A_CW)
	{
		GPIO_writePin(Motor_Port,Motor_Input1,LOGIC_LOW);
		GPIO_writePin(Motor_Port,Motor_Input2,LOGIC_HIGH);
	}
	else if(state==CW)
	{
		GPIO_writePin(Motor_Port,Motor_Input1,LOGIC_HIGH);
		GPIO_writePin(Motor_Port,Motor_Input2,LOGIC_LOW);
	}


}
