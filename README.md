# Door-lock-security-system
A security system for a door by locking it with a password. The Project is based on ATmega32 using two ECUs.

First controller: HMI_ECU is just responsible for interaction with the user just takes inputs through keypad and display messages on the LCD.

Second controller: CONTROL_ECU is responsible for all the processing and decisions in the system like password checking, open the door and activate the system alarm.

The Ecus communicated with each other using UART protocol.

Drivers Used in this Project: GPIO ,LCD ,Keypad ,DC_Motor , ,I2C(TWI) ,EEPROM ,UART ,Timer Driver,Buzzer.
