#include <lpc21xx.h>
#include "header.h"

#define TRIG (1<<7)
#define ECHO (1<<11)

unsigned int ultrasonic_distance()
{
    unsigned int time=0;

    IODIR0=TRIG;
    IOCLR0=TRIG;
    delay_microsec(2);

    IOSET0=TRIG;
    delay_microsec(10);
    IOCLR0=TRIG;

    //////////// WAIT FOR ECHO
    while(!(IOPIN0&ECHO));

    ///////////MEASURE ECHO HIGH DURATION
    T0TCR=0x02;
    T0PR=14;
    T0TC=0;
    T0TCR=0x01;

    while(IOPIN0&ECHO);

    T0TCR=0;
    time=T0TC;
    time=time/58;

    if(time>=30)
        return 0;

    return 30-time;
}

void delay_microsec(int p)
{
    T0TCR=0x02;
    T0PR=15-1;
    T0PC=T0TC=0;
    T0TCR=0x01;

    while(T0TC<p);

    T0TCR=0;
}
