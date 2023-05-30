/*
 * servo.h - XvR 2020
 */

#ifndef _SERVO_H_
#define _SERVO_H_


// The settings below are for the Mega, modify
// in case you want to use other pins
#define PORT_1	PORTH
#define PIN_1	PH5
#define DDR_1	DDRH


void init_servo(void);
void servo1_set_percentage(signed char percentage);


#endif /* _SERVO_H_ */
