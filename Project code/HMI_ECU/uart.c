 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.c
 *
 * Description: Source file for the UART AVR driver
 *
 * Author: Mohamed Mohsen
 *
 *******************************************************************************/
#include "uart.h"

#include"common_macros.h"

#include "avr/io.h" /* To use the UART Registers */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType * Config_Ptr)
{
	uint16 ubrr_value=0;

	/************************** UCSRB Description **************************
		 * RXCIE = 0 Disable USART RX Complete Interrupt Enable
		 * TXCIE = 0 Disable USART Tx Complete Interrupt Enable
		 * UDRIE = 0 Disable USART Data Register Empty Interrupt Enable
		 * RXEN  = 1 Receiver Enable
		 * TXEN  = 1 Transmitter Enable
		 * UCSZ2 = 0 For 8-bit data mode
		 * RXB8 & TXB8 not used for 8-bit data mode
		 ***********************************************************************/
	UCSRB=(1<<TXEN) | (1<<RXEN);

	UCSRA=(1<<U2X);

	/************************** UCSRC Description **************************
		 * URSEL   = 1 The URSEL must be one when writing the UCSRC
		 * UMSEL   = 0 Asynchronous Operation
		 * UPM1:0  = 10 Even parity bit
		 * USBS    = 0 One stop bit
		 * UCSZ1:0 = 11 For 8-bit data mode
		 * UCPOL   = 0 Used with the Synchronous operation only
		 ***********************************************************************/
	UCSRC=(1<<URSEL);
	UCSRC=(UCSRC & 0xBF) | ((Config_Ptr->mode)<<6);
	UCSRC=(UCSRC & 0xCF) | ((Config_Ptr->parity)<<4);
	UCSRC=(UCSRC & 0xF7) | ((Config_Ptr->stop_bit)<<3);
	UCSRC=(UCSRC & 0xF9) | ((Config_Ptr->char_size)<<1);

	ubrr_value = (uint16)(((F_CPU / (Config_Ptr->baud_rate * 8UL))) - 1);
	UBRRH=ubrr_value>>8;
	UBRRL=ubrr_value;
}

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(uint8 data)
{
	/*
	 * UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one
	 */
	while(BIT_IS_CLEAR(UCSRA,UDRE));

	/*
	 * Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now
	 */
	UDR=data;
}

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void)
{
	/* RXC flag is set when the UART receive data so wait until this flag is set to one */
	while(BIT_IS_CLEAR(UCSRA,RXC));

	/*
	 * Read the received data from the Rx buffer (UDR)
	 * The RXC flag will be cleared after read the data
	 */
	return UDR;
}

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8* str)
{
	uint8 i=0;

	/* Send the whole string */
	while(str[i]!='\0')
	{
		UART_sendByte(str[i]);
		i++;
	}
}

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *str)
{
	uint8 i=0;

	/* Receive the first byte */
	str[i]=UART_recieveByte();

	/* Receive the whole string until the '#' */
	while(str[i]!='#')
	{
		i++;
		str[i]=UART_recieveByte();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	str[i]='\0';
}