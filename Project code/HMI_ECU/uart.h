 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Mohamed Mohsen
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_
#include"std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	Asynchronous,synchronous
}UART_Mode;
typedef enum
{
	Disabled,Enabled_Even=2,Enabled_Odd
}UART_Parity;

typedef enum
{
	one_bit,two_bit
}URT_StopBit;

typedef enum
{
	five_bit,six_bit,seven_bit,eight_bit,nine_bit=7
}UART_CharacterSize;


typedef struct
{
	UART_Mode mode;
	UART_Parity parity;
	URT_StopBit stop_bit;
	UART_CharacterSize char_size;
	uint32 baud_rate;
}UART_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                  *
 *******************************************************************************/
/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType * Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8* str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *str);







#endif /* UART_H_ */
