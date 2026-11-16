#include<lpc21xx.h>
#include "header.h"

void adc_init()
{
    PINSEL1|=0x15400000;
    ADCR=0X00200400;
}

unsigned int adc_read(unsigned int ch_num)
{
    unsigned int temp=0;

    ADCR|=(1<<ch_num);
    ADCR|=(1<<24);

    while(((ADDR>>31)&1)==0);

    ADCR^=1<<24;
    ADCR^=(1<<ch_num);

    temp=(ADDR>>6)&0X3FF;

    return temp;
}
