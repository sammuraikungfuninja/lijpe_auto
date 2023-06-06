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
int state = 0;
int random1 = 0;        //ints bij buzzer
int random2 = 0;
void init()
{
    DDRF &= ~(1<<PF0); //A0, ir links voor
    PORTF |= (1<<PF0);
    DDRF &= ~(1<<PF1); //A1, ir rechts voor
    PORTF |= (1<<PF1);
    DDRF &= ~(1<<PF2); //A2, ir bomen rechts
    PORTF |= (1<<PF2);
    DDRF &= ~(1<<PF3);//A3, ir bomen links
    PORTF |= (1<<PF3);
    DDRF &= ~(1<<PF4);//A4, voren detecteren
    PORTF |= (1<<PF4);
    DDRF &= ~(1<<PF5);//A5, eind van balk detectie
    PORTF |= (1<<PF5);
    DDRB |= (1<<PB0);  //53, links leds
    PORTB &= ~(1<<PB0);
    DDRB |= (1<<PB1);   //52, leds rechts
    PORTB &= ~(1<<PB1);
}

void sensoren()
{
        if ((PINF & (1<<PF0))==0)       //beide zijkanten checken, rechtdoor
        {
        if ((PINF & (1<<PF1))==0)
        {
            state = 1;
        }
        }
        if (PINF & (1<<PF0))                   //links checken, rechts corigeren
        {
            state = 5;
        }
        if (PINF & (1<<PF1))                    //rechts checken, links corigeren
        {
            state = 4;
        }
            if (PINF & (1<<PF5)==0)                 //balk checken, grote bocht
        {
        state = 3;
        }


}
void veiligheidsensor()
{
    if (PINF & (1<<PF4)==0)                        //voren iets, staan stil
        {
            state = 0;
        }
}
void vroem()
{
    h_bridge_set_percentage(50);
}

void plantsensoraan()
{
if(random1 <= 0)
{
if ((PINF & (1<<PF2))==0)                    //bomen rechts, staan stil
{
state = 2;
random1 = 6000; //kan wisselen
}
}
else
{
    random1--;
}
if (random2 <= 0)
{
if ((PINF & (1<<PF3))==0)                    //bomen links, staan stil
{
state = 2;
random2 = 300; //kan wisselen
}
}
else
{
    random2--;
}
}


void rem()
{
    h_bridge_set_percentage(0);
}

void alarm()
{
        PORTB |= (1<<PB0);
        _delay_ms(500);
        PORTB &= ~(1<<PB0);
        PORTB |= (1<<PB1);
        _delay_ms(500);
        PORTB |= (1<<PB0);
        PORTB &= ~(1<<PB1);
        _delay_ms(500);
        PORTB &= ~(1<<PB0);
        PORTB |= (1<<PB1);
        _delay_ms(500);
        PORTB &= ~(1<<PB0);
        PORTB &= ~(1<<PB1);
}

void stuurlinks()
{
    servo1_set_percentage(-20);
}

void stuurrechts()
{
   servo1_set_percentage(20);
}

void stuurvooruit()
{
    servo1_set_percentage(0);
}

void grotebocht()
{

}

int main(void)
{
    init_h_bridge();    //d12,13
    init_servo();       //d11
    init();
    while(1)

    {
        //sensoren checken


        switch(state)

        {
        case(0):
            rem();
            sensoren();
            veiligheidsensor();
            break;

        case(1):
            stuurvooruit();
            vroem();
            sensoren();
            plantsensoraan();
            veiligheidsensor();//zij sensoren en sturen bijhouden
            break;

        case(2):
            rem();
            alarm();
            vroem();
            sensoren();
            veiligheidsensor();
            break;

        case(3):
            grotebocht();//bocht
            sensoren();
            veiligheidsensor();
            break;

        case(4):
            stuurlinks();
            sensoren();
            plantsensoraan();
            veiligheidsensor();
            break;

        case(5):
            stuurrechts();
            sensoren();
            plantsensoraan();
            veiligheidsensor();
            break;
        }
    }


    return 0;
}

