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
#define RESET 34000ul
#define DEBOUNCE _delay_ms(110)
int state = 0;
volatile int random1 = 1;        //ints bij buzzer
volatile int random2 = 1;
volatile int random3 = 1;
volatile int tellerbocht = 2;
void init()
{
    DDRD &= ~(1<<PD3); //D18, ir rechts voor
    PORTD |= (1<<PD3);
    DDRF &= ~(1<<PF1); //A1, ir links voor
    PORTF |= (1<<PF1);
    DDRF &= ~(1<<PF2); //A2, ir bomen rechts
    PORTF |= (1<<PF2);
    DDRF &= ~(1<<PF3);//A3, ir bomen links
    PORTF |= (1<<PF3);
    DDRD &= ~(1<<PD2);// D19, voren detecteren
    PORTD |= (1<<PD2);
    DDRF &= ~(1<<PF5);//A5, eind van balk detectie
    PORTF |= (1<<PF5);
    DDRB |= (1<<PB0);  //53, links leds
    PORTB &= ~(1<<PB0);
    DDRB |= (1<<PB1);   //52, leds rechts
    PORTB &= ~(1<<PB1);
}

ISR(TIMER3_OVF_vect)
{
    random1 = 1;
    random2 = 1;
    TCNT3 = RESET;
    TCCR3B = 0;
}

ISR(TIMER4_OVF_vect)
{
    tellerbocht++;

}

void sensoren()
{
        if ((PIND & (1<<PD3)))       //beide zijkanten checken, rechtdoor
        {
        if ((PINF & (1<<PF1)))
        {
            DEBOUNCE;
            state = 1;
        }
        }

        if ((PINF & (1<<PF1))==0)                    //rechts checken, links corigeren
        {
            DEBOUNCE;
            state = 5;
        }

        if ((PIND & (1<<PD3))==0)                   //links checken, rechts corigeren
        {
            DEBOUNCE;
            state = 4;
        }
        if ((PIND & (1<<PD3))==0)       //beide zijkanten checken, stoppen
        {
        if ((PINF & (1<<PF1))==0)
        {
            DEBOUNCE;
            state = 0;
        }
        }
       if(tellerbocht >= 2)                      //te vroeg achtersensor aan 2 moet groter
        {
            if (PINF & (1<<PF5))                 //balk checken, grote bocht
        {
        DEBOUNCE;
        state = 3;
        }
        }


}
void veiligheidsensor()
{
   if ((PIND & (1<<PD2))==0)                        //voren iets, staan stil
    {
        state = 0;
    }
}

void bochtveiligheid()
{
    if ((PIND & (1<<PD2))==0)                        //voren iets, staan stil
    {
        state = 6;
    }
    else
    {
        state = 3;
    }
}
void vroem()
{
    h_bridge_set_percentage(30);
}

void plantsensoraan()
{
    if(random1 == 1)
    {
        if ((PINF & (1<<PF2))==0)                    //bomen rechts, staan stil
        {
            state = 2;
            random1 = 0;
        }
    }

    if (random2 == 1)
    {
        if ((PINF & (1<<PF3))==0)                    //bomen links, staan stil
        {
            state = 2;
            random2 = 0;
        }
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
        TCCR3B |= ((1<<CS32)|(0<<CS31)|(1<<CS30));
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
    if (random3 == 1)
    {
    servo1_set_percentage(-20);
    DEBOUNCE;
    if ((PIND & (1<<PD3))==0)                    //links checken, rechts corigeren
    {
        state = 1;
       tellerbocht = 0;
        TCNT4 = 0;
        random3 = 2;
    }
    }
    if (random3 == 2)
    {
    servo1_set_percentage(20);
    DEBOUNCE;
    if ((PINF & (1<<PF1))==0)                    //links checken, rechts corigeren
    {
        state = 1;
       tellerbocht = 0;
        TCNT4 = 0;
        random3 = 1;
    }
    }
}

int main(void)
{
    TCCR3A = 0;
    TCCR3B = 0;
    TIMSK3 |= (1<<TOIE3);
    TCNT3 = RESET;

    TCCR4A = 0;
    TCCR4B |= ((1<<CS42)|(0<<CS41)|(1<<CS40));
    TIMSK4 |= (1<<TOIE4);

    sei();
    init_h_bridge();    //d12,13
    init_servo();       //d11
    init();
    while(1)

    {

        switch(state)

        {
        case(0):
            rem();
            stuurvooruit();
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
            vroem();
            bochtveiligheid();
            grotebocht();//bocht
            break;

        case(4):
            stuurlinks();
            vroem();
            sensoren();
            plantsensoraan();
            veiligheidsensor();
            break;

        case(5):
            stuurrechts();
            vroem();
            sensoren();
            plantsensoraan();
            veiligheidsensor();
            break;

        case(6):
            rem();
            bochtveiligheid();
        }
    }


    return 0;
}

