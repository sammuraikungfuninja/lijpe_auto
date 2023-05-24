/*
haiiiiiiii
 */
#include <avr/io.h>
#include "h_bridge.h"
#include "h_bridge.c"

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

int state;
int main(void)
{
    init_h_bridge();

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
