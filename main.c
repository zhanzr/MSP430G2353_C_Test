#include <stdint.h>
#include <msp430.h>

//Information Section
//Please erase all the chip to make sure that all the unused location are filled with 0xff
#pragma RETAIN(ic1052)
#pragma location=0x1052
const uint16_t ic1052[] = {0x3240, 0x0077, 0xb080, 0xd42d, 0xffa9, 0x0064, 0x0000};

#pragma RETAIN(ic1060)
#pragma location=0x1060
const uint16_t ic1060[] = {0x0000};

#pragma RETAIN(ic10c0)
#pragma location=0x10c0
const uint16_t ic10c0[] = {0x8e22, 0x16fe};

#pragma RETAIN(ic10da)
#pragma location=0x10da
const uint16_t ic10da[] = {0x1010, 0x8000, 0x0000, 0x7f8b, 0x02eb, 0x0374, 0x7ff4, 0x01be, 0x0210, 0x08fe};

#pragma RETAIN(ic10f6)
#pragma location=0x10f6
const uint16_t ic10f6[] = {0x0801, 0x8f9a, 0x8ea1, 0x8d95, 0x86d0};

#pragma RETAIN(code_f000_f041)
#pragma SET_DATA_SECTION("text")
#pragma location=0xF000
const uint16_t code_f000_f041[] = {
		0x0000, 0x0700, 0x5A0B, 0x010B, 0x0001, 0x0E5A, 0x0101, 0x5A00,
		0x0303, 0x0001, 0x075A, 0x0104, 0x5A00, 0x040C, 0x0001, 0x0000,
		0x8600, 0x000C, 0x0000, 0x0001, 0x0000, 0x0200, 0x000D, 0x0000,
		0x0903, 0x0000, 0x0100, 0x5100, 0x091B, 0x0103, 0x36A2, 0x0612, 0xFF02};

#pragma RETAIN(ram_0210)
#pragma location=0x0210
uint8_t ram_0210[0x38] = {0};

#define COMPARATOR_A0 11
__attribute__((interrupt(COMPARATOR_A0))) void COM_A0_ISR()    {
}

void PortInit(void)
{
	P1DIR = 0x00fc;
	P1OUT = 0;
	P2SEL = 0;
	P2DIR = 0xff;
	P2OUT = 0;
}

void ComparatorInit(void)
{
	CACTL2 = 0x0e;
	CAPD = 0x03;
	CACTL1 = 0x0a;
}

void f_fcc2(uint8_t* r13, uint8_t* r12, uint8_t r14)
{
	while(r14!=0)
	{
		*r12 = *r13;
		r13++;
		r12++;
		r14--;
	}
}

uint16_t f_fb0c(uint16_t i_r12)
{
	uint16_t r12 = i_r12;

	uint16_t r15 = 0;
	uint16_t r14 = 0;

	for(r15 = 0; r15 < 15; r15++)
	{
		r14 <<= 2;
		if(r12 < *(uint8_t*)(0xf037 + r15))
		{

		}
		else if(r12 >= *(uint8_t*)(0xf03c + r15))
		{
			r14 |= 0x0003;
			r12 -= *(uint8_t*)(0xf03c + r15);
		}

		r14 |= 0x0001;
		r12 -= *(uint8_t*)(0xf037 + r15);
	}

	r12 = r14;
	r12 &= 0xff00;
	r12 <<= 6;

	r14 &= 0xff;
	r12 += r14;

	return r12;
}

void f_fa6a(void)
{
	if(-1 == *(int16_t*)0x1020)
	{
		f_fcc2((uint8_t*)0x1053, (uint8_t*)0x0203, 0x0d);
	}
	else
	{
		f_fcc2((uint8_t*)0x1013, (uint8_t*)0x0203, 0x0d);
	}

	if(*(uint8_t*)0x0203 < 0xf3)
	{
		*((uint8_t*)0x0203) = 1;

		*((uint16_t*)0x0204) = f_fb0c(1);
	}

	if((0x64 == *((uint8_t*)0x020c)) || (0x65 == *((uint8_t*)0x020c)) || (0x67 == *((uint8_t*)0x020c)))
	{

	}
	else
	{
		*((uint8_t*)0x020c) = 0x66;
	}
}

void f_fb96(void)
{
	*((uint8_t*)0x0241) = 0;
	*((uint8_t*)0x0242) = 0;
	*((uint8_t*)0x0243) = 0;
	*((uint8_t*)0x0244) = 0;

	*((uint8_t*)0x021a) = 0;

	*((uint16_t*)0x0218) = 0x00a0;

	*((uint8_t*)0x021b) = 0;
	*((uint8_t*)0x0247) = 0;
	*((uint8_t*)0x0246) = 0;

	*((uint16_t*)0x0216) = 0;

	P2OUT &= ~(0x02);
	P2OUT &= ~(0x04);

	*((uint16_t*)0x0210) = 0;
}


void f_fbcc(void)
{
	uint8_t r14;

	*((uint8_t*)0x021a) = 0x39;
	TA1CTL = *((uint16_t*)0x02d4);
	TA1CCR0 = *((uint16_t*)0x88b8);

	for(r14=0x0a; r14!=0; r14--)
	{
	    while(0==(TA1CCTL0 && TAIFG))
	    {
	    	;
	    }
	    TA1CCTL0 &= ~TAIFG;
	    WDTCTL = 0x5a0d;
	}

	TA1CTL = 0;
}

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;
    BCSCTL1 |= 0x80;
    BCSCTL2 = 0;
    BCSCTL3 = 0x20;
    _BIS_SR(OSCOFF);

    PortInit();
    ComparatorInit();
    f_fa6a();
    f_fb96();
    TA0CTL = 0x0224;
    TA0CCR0 = 0xea60;

    while(0==(TA0CCTL0 && TAIFG))
    {
    	;
    }

    __enable_interrupt();

	while(1) {
	}

	return 0;
}
