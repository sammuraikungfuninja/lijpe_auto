/*
 * servo.h - XvR 2020
 */

#ifndef _SERVO_H_
#define _SERVO_H_


// The settings below are for the Mega, modify
// in case you want to use other pins
#define PORT_1	PORTB
#define PIN_1	PB5
#define DDR_1	DDRB


void init_servo(void);
void servo1_set_percentage(signed char percentage);


#endif /* _SERVO_H_ */
