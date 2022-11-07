/*
 ======================================================================================
 Name        : Control_ECU.c

 Author      : Mohamed Mohsen Kamal Mousa

 Description : Door locker security system and this controller is responsible for
  all the processing and decisions in the system like password checking,
  open the door and activate the system alarm.

 Date        : 1/11/2022
 ======================================================================================
 */

#include "Control_ECU.h"
#include<avr/io.h>
#include "gpio.h"
#include "util/delay.h"
#include "twi.h"
#include"uart.h"
#include"timer.h"
#include"dc_motor.h"
#include"buzzer.h"
#include<avr/interrupt.h>


/*******************************************************************************
 *                                Types definitions                            *
 *******************************************************************************/
uint8 i=0;
uint8 g_count=0;
uint8 check=0;
uint8 option=0;
uint8 wrong_pass_counter=0;
uint8 pass1[PASS_SIZE]={0};
uint8 pass2[PASS_SIZE]={0};
uint8 user_pass[PASS_SIZE]={0};
uint8 EepromPass[PASS_SIZE]={0};


Timer1_ConfigType timer_Config = {0,7813,F_CPU_1024,CTC};
UART_ConfigType uartConfig = {Asynchronous,Enabled_Even,one_bit,eight_bit,9600};

/*
 * Description:The Function that receives the password from
 * the user.
 */

/*******************************************************************************
 *                      Functions definitions                                  *
 *******************************************************************************/
void receivePassword(uint8 *pass1)
{
	for(i=0;i<PASS_SIZE;i++)
	{
		pass1[i]=UART_recieveByte();
	}
	_delay_ms(UART_DELAY);

}

/*
 * Description:The Function makes sure that the passwords aare identical
 *
 */
uint8 sendConfirmation(uint8 *pass1, uint8 *pass2 )
{
	for(i=0;i<PASS_SIZE;i++)
	{
		if(pass1[i] != pass2[i])
		{
			return 0;
		}
	}
	return 1;
}

/*
 * Description:The Function controls the fan direction and state.
 *
 */
void openDoor(void)
{
	Timer1_init(&timer_Config);

	DcMotor_Rotate(CW);
	while(g_count<15);
	g_count=0;

	DcMotor_Rotate(stop);
	while(g_count<3);
	g_count=0;

	DcMotor_Rotate(A_CW);
	while(g_count<15);
	g_count=0;
	DcMotor_Rotate(stop);

	Timer1_deInit();
}

/*
 * Description:The Function is responsible for dealing with entering
 *  three consecutive wrong passwords.
 *  It enables the buzzer for one minute.
 *
 */
void wrongPass(void)
{
	if(wrong_pass_counter>=3)
	{
		wrong_pass_counter=0;
		Timer1_init(&timer_Config);
		Buzzer_on();
		while(g_count<60);
		g_count=0;
		Buzzer_off();
		Timer1_deInit();
	}
}

/*
 * Description:The Function stores the right password in EEPROM.
 *
 */
void sendPassToEeprom(uint8 *pass1)
{
	for(i=0;i<5;i++)
	{
		EEPROM_writeByte((0x0311+i), pass1[i]);
		_delay_ms(UART_DELAY);
	}
}

/*
 * Description:The Function is responsible for receiving
 *  the password from EEPROM to compare it with the user's pass.
 *
 */
void receivePassFromEeprom(uint8 *pass1)
{
	for(i=0;i<5;i++)
	{
		EEPROM_readByte((0x0311+i),(pass1+i));
		_delay_ms(50);
	}
}

/*
 * Description:A Function that represents the callback function.
 * It handles the timer.
 *
 */
void timerCounter(void)
{
	g_count++;
}


int main(void)
{
	SREG|=(1<<7);
	EEPROM_init();
	Buzzer_init();
	DcMotor_Init();
	UART_init(&uartConfig);
	Timer1_setCallBack(timerCounter);


	while(check==0)
	{
		receivePassword(pass1);
		receivePassword(pass2);
		check=sendConfirmation(pass1,pass2);
		UART_sendByte(check);
		_delay_ms(UART_DELAY);
	}

	sendPassToEeprom(pass1);

	while(1)
	{
		receivePassFromEeprom(EepromPass);
		option=UART_recieveByte();
		_delay_ms(UART_DELAY);

		if(option=='+')
		{
			receivePassword(pass1);

			if(sendConfirmation(pass1,EepromPass))
			{
				wrong_pass_counter=0;
				UART_sendByte(1);
				_delay_ms(UART_DELAY);
				openDoor();

			}
			else
			{
				UART_sendByte(0);
				_delay_ms(UART_DELAY);
				wrong_pass_counter++;
				UART_sendByte(wrong_pass_counter);
				_delay_ms(UART_DELAY);
				wrongPass();
			}
		}

		else if(option=='-')
		{
			receivePassword(pass1);


			check = sendConfirmation(pass1, EepromPass);
			_delay_ms(UART_DELAY);
			UART_sendByte(check);

			if(check)
			{
				wrong_pass_counter = 0;
				receivePassword(pass1);


				receivePassword(user_pass);

				check = sendConfirmation(pass1, user_pass);
				_delay_ms(UART_DELAY);
				UART_sendByte(check);

				if(check)
				{
					sendPassToEeprom(pass1);
				}

				else
				{

				}

			}

			else
			{
				wrong_pass_counter++;
				UART_sendByte(wrong_pass_counter);
				_delay_ms(UART_DELAY);
				wrongPass();
			}

		}
	}






}
