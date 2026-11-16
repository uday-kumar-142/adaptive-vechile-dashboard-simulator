#include<stdio.h>
#include"header.h"

int main()
{
    char s[30];
    int pot,temp,ultra;
    extern CAN1 c;

    eint0_init();
    can1_init();
    IODIR0=7<<4;
    IOSET0=7<<4;
    eint0_init();
    uart0_init(9600);
    adc_init();

    while(1)
    {
        pot=adc_read(0);
        pot=(120*pot)/1023;
        c.byteA|=pot<<8;

        temp=adc_read(1);
        temp=(3.3*100*temp)/1023;
        c.byteA|=temp<<16;

        c.byteB=ultrasonic_distance();

        sprintf(s,"pot=%dtemp=%d",pot,temp);
        uart0_string(s);
        uart0_string("\r\n");

        can1_tx(c);

        c.byteA=c.byteA&0xff;
        delay_sec(10);
    }
}
