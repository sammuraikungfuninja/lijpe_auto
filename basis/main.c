/*
<<<<<<< Updated upstream
haiiiiiiii
=======
daan is brokko
>>>>>>> Stashed changes
 */
 #ifndef F_CPU
#define F_CPU 16000000ul
 #endif
#include <avr/io.h>
#include "h_bridge.h"
#include "h_bridge.c"
#include "servo.h"
#include "servo.c"
#include <avr/interrupt.h>
#include <util/delay.h>
int state;
void init()
{
    DDRF &= ~(1<<PF0); //A0, ir links voor
    PORTF |= (1<<PF0);
    DDRF &= ~(1<<PF1); //A1, ir rechts voor
    PORTF |= (1<<PF1);
}
void vroem()
{
    h_bridge_set_percentage(100);
    _delay_ms(4000);
    state = 2;
}

void plantsensoraan()
{
    //sensoren aan
}

void rem()
{
    h_bridge_set_percentage(0);
}

void alarm()
{
    //1 pinnetje aan en uit schakelen voor 2x
}

void stuurlinks()
{
        servo1_set_percentage(-50);
}

void stuurrechts()
{
   servo1_set_percentage(50);
}

void stuurvooruit()
{
    servo1_set_percentage(0);
}


int main(void)
{
    init_h_bridge();    //d12,13
    init_servo();       //d11
    init();
    while(1)

    {
        //sensoren checken
        if (PINB & ((1<<PB0) & (1<<PB2)))
        {
        state = 1;
        }
        if ((PINB & (1<<PB0))==0)
        {
            state = 5;
        }
        if ((PINB & (1<<PB2))==0)
        {
            state = 4;
        }
     /*   if ((PINB & (1<<PB0) | (1<<PB1))==0)
        {
            state
        }*/
        switch(state)
        {
        case(0):
            rem();
            break;

        case(1):
            vroem();
            plantsensoraan();
            stuurvooruit();
            //zij sensoren en sturen bijhouden
            break;

        case(2):
            rem();
            alarm();
            //plant detect
            //alarm
            break;

        case(3):
            //bocht
            //plant sensoren uit
            break;

        case(4):
            stuurlinks();
            break;

        case(5):
            stuurrechts();
            break;
        }
    }


    return 0;
}
