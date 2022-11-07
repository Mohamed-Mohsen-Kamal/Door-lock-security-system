/*
 ======================================================================================
 Name        : HMI_ECU.c

 Author      : Mohamed Mohsen Kamal Mousa

 Description : Door locker security system and this controller is just responsible
 for interaction with the user just take inputs through keypad
  and display messages on the LCD.

 Date        : 31/10/2022
 ======================================================================================
 */
#include"HMI_ECU.h"
#include<avr/io.h>
#include"lcd.h"
#include"keypad.h"
#include "util/delay.h"
#include"timer.h"
#include"uart.h"
#include <avr/interrupt.h>

/*******************************************************************************
 *                                Types definitions                            *
 *******************************************************************************/

uint8 i=0;
uint8 g_count=0;
uint8 check=0;
uint8 option=0;
uint8 wrong_pass_counter=0;
uint8 password[PASS_SIZE];
uint8 pass2[PASS_SIZE];


Timer1_ConfigType timer_Config = {0,7813,F_CPU_1024,CTC};
UART_ConfigType uartConfig = {Asynchronous,Enabled_Even,one_bit,eight_bit,9600};

/*******************************************************************************
 *                      Functions definitions                                  *
 *******************************************************************************/
/*
 * Description:The Function is responsible for getting the password from the user.
 *
 */
void pass_init(uint8 *pass)

{

	LCD_moveCursor(1,11);
	for(i=0;i<6;i++)
	{
		while ((KEYPAD_getPressedKey() != ENTER_BUTTON) && (i == 5));
		pass[i]=KEYPAD_getPressedKey();
		_delay_ms (KEYPAD_DELAY_TIME);
		LCD_displayCharacter('*');
	}
	_delay_ms (KEYPAD_DELAY_TIME);

}

/*
 * Description:The Function sends the pass to the other controller using UART.
 *
 */
void sendPassword (uint8 *pass )

{
	for(i=0;i<5;i++)
	{
		UART_sendByte(pass[i]);
	}
	_delay_ms (UART_DELAY_TIME);

}

/*
 * Description:The Function that displays the main options.
 *
 */
void optionsDisplay (void)
{
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "- :Change PW");
	LCD_displayStringRowColumn(1, 0, "+ :Open Door");
}

/*
 * Description:The Function that shows the state of the door.
 *
 */
void openDoor (void)
{
	Timer1_init(&timer_Config);
	LCD_clearScreen();
	LCD_displayString("Opening door");

	while(g_count<15);
	g_count=0;

	LCD_clearScreen();
	LCD_displayString("Door is open");

	while(g_count<3);
	g_count=0;

	LCD_clearScreen();
	LCD_displayString("Locking door");

	while (g_count < 15);
	g_count = 0;

	Timer1_deInit();

}

/*
 * Description:The Function is responsible for dealing with entering
 *  three consecutive wrong passwords
 *
 */
void wrong_pass_cons(void)
{
	Timer1_init(&timer_Config);
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "Wrong for 3rd ");
	LCD_displayStringRowColumn(1, 0, "Locking system");

	while(g_count<60);
	g_count=0;

	Timer1_deInit();

}

/*
 * Description:A Function that represents the callback function.
 * It handles the timer.
 *
 */
void timer_counter(void)
{
	g_count++ ;
}


int main(void)
{
	SREG |= (1<<7);      /*Enable general interrupt module */
	LCD_init();
	UART_init(&uartConfig);
	Timer1_setCallBack(timer_counter);

	while(check==0)
	{
		LCD_clearScreen();
		LCD_displayStringRowColumn(0, 0, "please enter ");
		LCD_displayStringRowColumn(1, 0, "your pass: ");
		pass_init(password);
		_delay_ms(UART_DELAY_TIME); /*Delay to control seening andd
		                              receiving via UART */
		sendPassword(password);

		LCD_clearScreen();
		LCD_displayStringRowColumn(0, 0, "plz re-enter the");
		LCD_displayStringRowColumn(1, 0, "same pass: ");
		pass_init(pass2);
		_delay_ms(UART_DELAY_TIME);
		sendPassword( pass2 );
		_delay_ms(UART_DELAY_TIME);

		check = UART_recieveByte();
		_delay_ms(UART_DELAY_TIME);

		if(check)
		{
			LCD_clearScreen();
			LCD_displayString("Correct Password");
		}

		else
		{
			LCD_clearScreen();
			LCD_displayString("Wrong Password");
		}

		_delay_ms(2000);

	}



	while(1)
	{
		optionsDisplay();
		option = KEYPAD_getPressedKey();
		_delay_ms(KEYPAD_DELAY_TIME);
		UART_sendByte(option);
		_delay_ms(UART_DELAY_TIME);
		if(option == '+')
		{
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0, "please enter ");
			LCD_displayStringRowColumn(1, 0, "your pass: ");
			pass_init(password);
			_delay_ms(UART_DELAY_TIME);
			sendPassword(password);
			_delay_ms(UART_DELAY_TIME);
			check = 0;
			check = UART_recieveByte();
			if(check)
			{
				openDoor();
			}

			else
			{

				wrong_pass_counter = UART_recieveByte();

				if(wrong_pass_counter >=3)
				{
					wrong_pass_cons();
				}

				else
				{
					LCD_clearScreen();
					LCD_displayStringRowColumn(0, 0, "Wrong password ");
					LCD_displayStringRowColumn(1, 0, "Back to main ");
					_delay_ms(2000);
				}

			}

		}
		else if(option == '-')
		{
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0, "please enter ");
			LCD_displayStringRowColumn(1, 0, "old pass: ");
			pass_init(password);
			_delay_ms(UART_DELAY_TIME);
			sendPassword(password);

			check = 0;
			check = UART_recieveByte();


			if(check)
			{
				LCD_clearScreen();
				LCD_displayStringRowColumn(0, 0, "please enter ");
				LCD_displayStringRowColumn(1, 0, "new pass: ");

				pass_init(password);
				_delay_ms(UART_DELAY_TIME);
				sendPassword(password);

				LCD_clearScreen();
				LCD_displayStringRowColumn(0, 0, "Confirm your ");
				LCD_displayStringRowColumn(1, 0, "new pass: ");

				pass_init( pass2 );
				_delay_ms(UART_DELAY_TIME);
				sendPassword( pass2 );
				_delay_ms(UART_DELAY_TIME);

				check = 0;
				check = UART_recieveByte();

				if(check)
				{
					LCD_clearScreen();
					LCD_displayString("Password Changed");
					_delay_ms(2000);
				}

				else
				{
					LCD_clearScreen();
					LCD_displayString("Wrong Password");
					_delay_ms(2000);
				}
			}

			else
			{
				wrong_pass_counter = UART_recieveByte();
				if(wrong_pass_counter >=3)
				{
					wrong_pass_cons();
				}

				else
				{
					LCD_clearScreen();
					LCD_displayStringRowColumn(0, 0, "Wrong password ");
					LCD_displayStringRowColumn(1, 0, "Back to main ");
					_delay_ms(2000);
				}
			}
		}

	}
	return 0;
}
