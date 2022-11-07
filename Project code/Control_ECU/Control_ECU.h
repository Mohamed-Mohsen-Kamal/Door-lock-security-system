/*
 * Control_ECU.h
/*
 ======================================================================================
 Name        : Control_ECU.h

 Author      : Mohamed Mohsen Kamal Mousa

 Description : Door locker security system and this controller is responsible for
  all the processing and decisions in the system like password checking,
  open the door and activate the system alarm.

 Date        : 1/11/2022
 ======================================================================================
 */

#ifndef CONTROL_ECU_H_
#define CONTROL_ECU_H_
#include"std_types.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define KEYPAD_DELAY        500
#define UART_DELAY          50  /*Delay to control sending and
		                              receiving via UART */
#define PASS_SIZE           5

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description:The Function that receives the password from
 * the user.
 */
void receivePassword(uint8 *pass1);

/*
 * Description:The Function makes sure that the passwords aare identical
 *
 */
uint8 sendConfirmation(uint8 *pass1, uint8 *pass2 );

/*
 * Description:The Function controls the fan direction and state.
 *
 */
void openDoor(void);

/*
 * Description:The Function is responsible for dealing with entering
 *  three consecutive wrong passwords.
 *  It enables the buzzer for one minute.
 *
 */
void wrongPass(void);

/*
 * Description:The Function stores the right password in EEPROM.
 *
 */
void sendPassToEeprom(uint8 *pass1);

/*
 * Description:The Function is responsible for receiving
 *  the password from EEPROM to compare it with the user's pass.
 *
 */
void receivePassFromEeprom(uint8 *pass1);

/*
 * Description:A Function that represents the callback function.
 * It handles the timer.
 *
 */
void timerCounter(void);




#endif /* CONTROL_ECU_H_ */
