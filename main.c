#include<stdio.h>
#include <LPC21xx.H>
#include "header.h"

#define LED (1<<18) //P0.18

CAN1 r;

main()
{
    char s[50];
    unsigned int pot=0,temp=0,ultra=0;

    can1_init();
    uart0_init(9600);

    IODIR0=7<<4;

    while(1)
    {
        uart0_string("waiting nodeB\r\n");

        can1_rx(&r);

        uart0_string("===============================================\r\n\r\n\r\n");

        if(r.rtr==0)
        {
            if(r.id==0x123)
            {
                switch(r.byteA&0xFF)
                {
                    case 0x1:
                        IOCLR0=1<<6;
                        IOSET0=1<<4;
                        uart0_string("left indicator on\r\n");
                        break;

                    case 0x11:
                        IOSET0=1<<6;
                        uart0_string("left indicator off\r\n");
                        break;

                    case 0x2:
                        IOCLR0=1<<5;
                        uart0_string("HEAD light on\r\n");
                        break;

                    case 0x22:
                        IOSET0=1<<5;
                        uart0_string("HEAD light off\r\n");
                        break;

                    case 0x3:
                        IOCLR0=1<<4;
                        IOSET0=1<<6;
                        uart0_string("right indicator on\r\n");
                        break;

                    case 0x33:
                        IOSET0=1<<4;
                        uart0_string("right indicator off\r\n");
                        break;

                    default:
                        uart0_string("wrong data\r\n");
                }

                pot=(r.byteA>>8)&0xff;
                temp=(r.byteA>>16)&0xff;
                ultra=r.byteB&0xff;

                sprintf(s,"speed=%d KM/h\r\ntempreature=%d'c\r\nfule=%d L\r\n",pot,temp,ultra);
                uart0_string(s);

                uart0_string("===============================================\r\n\r\n\r\n");
            }
        }
    }
}
