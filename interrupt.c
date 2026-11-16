#include<lpc21xx.h>
#include"header.h"

int left,right,head;
CAN1 c;

////////////////////////////////////////////////
void EXINT0_handeler()__irq
{
    left^=1;
    delay_ms(900);

    if(left)
    {
        uart0_string("left on\r\n");
        c.byteA=0x1;
        //c.byteB=0;
        IOCLR0=1<<6;
    }
    else
    {
        uart0_string("left off\r\n");
        IOSET0=1<<6;
        c.byteA=0x11;
        //c.byteB=0;
    }

    can1_tx(c);
    EXTINT=(1<<0);
    VICVectAddr=0;
}

////////////////////////////////////////////////
void EXINT1_handeler()__irq
{
    head^=1;
    delay_ms(900);

    if(head)
    {
        uart0_string("head on\r\n");
        c.byteA=0x2;
        //c.byteB=0;
        IOCLR0=1<<5;
    }
    else
    {
        uart0_string("head off\r\n");
        IOSET0=1<<5;
        c.byteA=0x22;
        //c.byteB=0;
    }

    can1_tx(c);
    EXTINT=(1<<1);
    VICVectAddr=0;
}

//////////////////////////////////////////////////////////
void EXINT2_handeler()__irq
{
    right^=1;
    delay_ms(900);

    if(right)
    {
        uart0_string("right on\r\n");
        c.byteA=0x3;
        //c.byteB=0;
        IOCLR0=1<<4;
    }
    else
    {
        uart0_string("right off\r\n");
        IOSET0=1<<4;
        c.byteA=0x33;
        //c.byteB=0;
    }

    can1_tx(c);
    EXTINT=(1<<2);
    VICVectAddr=0;
}

///////////////////////////////////////////////////////////
void eint0_init()
{
    c.id=0x123;
    c.dlc=8;
    c.rtr=0;
    c.ff=0;

    PINSEL1|=1;
    PINSEL0|=0xA0000000;

    EXTMODE|=7;
    EXTPOLAR=0;

    //VICIntSelect=0;

    VICVectCntl0=(1<<5)|14;
    VICVectAddr0=(unsigned int)EXINT0_handeler;

    VICVectCntl1=(1<<5)|15;
    VICVectAddr1=(unsigned int)EXINT1_handeler;

    VICVectCntl2=(1<<5)|16;
    VICVectAddr2=(unsigned int)EXINT2_handeler;

    VICIntEnable=(7<<14);
}

///////////////////////////////////////////////////////////
