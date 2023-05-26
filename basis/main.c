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
#include <avr/interrupt.h>

#define RESETSERVO 25536ul
ISR(TIMER1_OVF_vect)
{
    PORTH |= (1<<PH5);
}

ISR(TIMER1_COMPA_vect)
{
    PORTH &= ~(1<<PH5);
}

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
    h_bridge_set_percentage(0);
}

void alarm()
{
    //1 pinnetje aan en uit schakelen voor 2x
}

void stuurlinks()
{
    //servo
}

void stuurrechts()
{
    //servo
}

void stuurvooruit()
{
    TCNT1 = RESETSERVO;
    OCR1A = RESETSERVO + 4000ul;
    TIMSK1 |= ((1 << OCIE1A)|(1 << TOIE1));

}

int state = 1;
int main(void)
{
    init_h_bridge();
    TCCR1A = 0;
    TCCR1B |= (1 << CS11);
    sei();
    DDRH |= (1<<PH5);
    PORTH &= ~(1<<PH5);

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
