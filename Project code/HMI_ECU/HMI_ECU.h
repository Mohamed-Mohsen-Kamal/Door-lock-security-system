/*
 ======================================================================================
 Name        : HMI_ECU.h

 Author      : Mohamed Mohsen Kamal Mousa

 Description : Door locker security system and this controller is just responsible
 for interaction with the user just take inputs through keypad
  and display messages on the LCD.

 Date        : 31/10/2022
 ======================================================================================
 */
#ifndef HMI_ECU_H_
#define HMI_ECU_H_
#include"std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define KEYPAD_DELAY_TIME 500

#define UART_DELAY_TIME 50  /*Delay to control sending and
		                              receiving via UART */
#define PASS_SIZE 5

#define ENTER_BUTTON        '='

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description:The Function is responsible for getting the password from the user.
 *
 */
void pass_init(uint8 *pass);

/*
 * Description:The Function sends the pass to the other controller using UART.
 *
 */
void sendPassword (uint8 *pass );

/*
 * Description:The Function that displays the main options.
 *
 */
void optionsDisplay (void);

/*
 * Description:The Function that shows the state of the door.
 *
 */
void openDoor (void);

/*
 * Description:The Function is responsible for dealing with entering
 *  three consecutive wrong passwords
 *
 */
void wrong_pass_cons(void);

/*
 * Description:A Function that represents the callback function.
 * It handles the timer.
 *
 */
void timer_counter(void);

#endif /* HMI_ECU_H_ */

