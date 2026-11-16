#include <lpc21xx.h>

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;
typedef signed int s32;

void delay_ms(unsigned int ms);
void delay_sec(unsigned int sec);

void eint0_init(void);

void ultrasonic_init(void);
unsigned int ultrasonic_distance(void);
unsigned int fuel_percentage(unsigned int tank_depth);

void adc_init(void);
int adc_read(int ch_num);

void uart0_init(unsigned int baud);
void uart0_tx(unsigned char data);
unsigned char uart0_rx(void);
void uart0_string(char *p);

typedef struct CAN1_MSG
{
    u32 id;
    u32 byteA;
    u32 byteB;
    u8 rtr;
    u8 dlc;
    u8 ff; //ide
} CAN1;

extern void can1_tx(CAN1 v);
extern void can1_init(void);
extern void can1_rx(CAN1 *ptr);
