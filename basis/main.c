/*
<<<<<<< Updated upstream
haiiiiiiii
=======
daan is brokko
>>>>>>> Stashed changes
 */
#include <avr/io.h>
#include "h_bridge.h"
#include "h_bridge.c"
#include "servo.h"
#include "servo.c"
#include <avr/interrupt.h>
#include <util/delay.h>

void vroem()
{
    h_bridge_set_percentage(50);
}

void plantsensoraan()
{
    //sensoren aan
}

void rem()
{
    h_bridge_set_percentage(-10);
    _delay_ms(10);
    h_bridge_set_percentage(0);

}

void alarm()
{
    //1 pinnetje aan en uit schakelen voor 2x
}

void stuurlinks()
{
    servo1_set_percentage(-100);
    _delay_ms(200);
    stuurrechts();

}

void stuurrechts()
{
   servo1_set_percentage(100);
   _delay_ms(200);
   stuurlinks();
}

void stuurvooruit()
{
    //
}

int state = 5;
int main(void)
{
  init_servo();
    while(1)
    {
        //sensoren checken

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
