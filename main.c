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
//	PUSH    R13
//		PUSH    R12
//		PUSH    R15
//		PUSH    R14
	TA0CTL |= 0x04;
	if(0 != (BIT0 & TA0CCTL0))
	{
		*(uint8_t*)0x021d = 0x11;
		*(uint8_t*)0x021e = 0;
	}

}

//TODO:Unclear feature
void f_f888(void)
{

}

//Flash Operation
void f_f98c(void)
{
	uint16_t* p_r15 = 0x0202;
	uint16_t* p_r14;
	uint8_t r13;

	if(0xFFFF != *((uint16_t*)0x1020))
	{
		p_r14 = 0x1052;
	}
	else
	{
		p_r14 = 0x1012;
	}

	WDTCTL = 0x5a80;
	FCTL2 = 0xa542;
	FCTL3 = 0xa500;
	FCTL1 = 0xa502;

	*p_r14 = 0;
	for(r13=0; r13<7; r13++)
	{
		*p_r14 = *p_r15;
		p_r14++;
		p_r15++;
	}

	*p_r14 = 0;
	FCTL1 = 0xa500;

	if(p_r14 >= 0x1040)
	{
		p_r14 = 0x1012;
	}
	else
	{
		p_r14 = 0x1052;
	}

	FCTL1 = 0xa502;
	*p_r14 = 0;
	FCTL3 = 0xa510;
	FCTL2 = 0xa500;
}

//TODO:Unclear feature
uint8_t f_fa06(uint16_t i_r12)
{
	uint8_t r_r12;
	uint8_t r_r14=0;

	if(BIT1 & i_r12)
	{
		r_r14 = BIT1;
	}
	else if(BIT0 & i_r12)
	{
		r_r14 = BIT0;
	}

	if(BIT3 & i_r12)
	{
		r_r14 += 6;
	}
	else if(BIT2 & i_r12)
	{
		r_r14 += 3;
	}

	if(BIT5 & i_r12)
	{
		r_r14 += 0x12;
	}
	else if(BIT4 & i_r12)
	{
		r_r14 += 9;
	}

	if((uint8_t)i_r12 < 0)
	{
		r_r14 += 0x36;
	}
	else if(BIT6 & i_r12)
	{
		r_r14 += 0x1b;
	}

	if((uint16_t)i_r12 < 0)
	{
		r_r14 += 0xa2;
	}
	else if(BITE & i_r12)
	{
		r_r14 += 0x51;
	}

	r_r12 = r_r14;

	return r_r12;
}

//TODO:Unclear feature
void f_fa6a(void)
{
	if(0xFFFF == *(uint16_t*)0x1020)
	{
		byte_memcpy_fcc2((uint8_t*)0x0203, (uint8_t*)0x1053, 0x0d);
	}
	else
	{
		byte_memcpy_fcc2((uint8_t*)0x0203, (uint8_t*)0x1013, 0x0d);
	}

	if(*(uint8_t*)0x0203 >= 0xf3)
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

//TODO:Unclear feature
void P1_2_fac4(void)
{
	if(0 == (*(uint8_t*)0x021a & 0x40))
	{
		if(0 == (*(uint8_t*)0x021a & 0x05))
		{
			P1OUT |= BIT2;
			TA0CTL |= TACLR;
			TA0CCTL0 &= ~TAIFG;

		    while(0==(TA0CCTL0 && TAIFG))
		    {
		    	;
		    }
			P1OUT &= ~BIT2;
		}
	}
	else
	{
		if(0 == (*(uint8_t*)0x021a & 0x28))
		{
			P1OUT |= BIT2;
			TA0CTL |= TACLR;
			TA0CCTL0 &= ~TAIFG;

		    while(0==(TA0CCTL0 && TAIFG))
		    {
		    	;
		    }
			P1OUT &= ~BIT2;
		}
	}
}

//TODO:Unclear feature
uint16_t f_fb0c(uint8_t i_r12)
{
	uint8_t r12 = i_r12;

	uint8_t r15 = 0;
	uint16_t r14 = 0;

	for(r15 = 0; r15 < 5; r15++)
	{
		r14 <<= 2;
		if(r12 >= *(uint8_t*)(0xf037 + r15))
		{
			if(r12 < *(uint8_t*)(0xf03c + r15))
			{
				r14 |= BIT0;
				r12 -= *(uint8_t*)(0xf03c + r15);
			}
			else
			{
				r14 |= 0x0003;
				r12 -= *(uint8_t*)(0xf03c + r15);
			}
		}
	}

	r12 = r14;
	r12 &= 0xff00;
	r12 <<= 6;

	r14 &= 0xff;
	r12 += r14;

	return r12;
}

//TODO:Unclear feature
void f_fb52(void)
{
	if(0 == (*(uint8_t*)0x021a & 0x24))
	{
		*(uint8_t*)0x021a |= BIT7;
		*(uint16_t*)0x0210 |= BIT3;
		*(uint8_t*)0x0226 = *(uint8_t*)0x0203;
	}
	else if(0 == (*(uint8_t*)0x021a & 0x4))
	{
		*(uint16_t*)0x0210 |= BIT3;
		*(uint8_t*)0x0226 = *(uint8_t*)0x0203;
	}
	else if(0 == (*(uint8_t*)0x021a & 0x20))
	{
		*(uint16_t*)0x0210 |= BIT3;
		*(uint8_t*)0x0226 = 1 + *(uint8_t*)0x0203;
	}
	else
	{
		;
	}
}

void ClearOut_fb96(void)
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

	P2OUT &= ~BIT1;
	P2OUT &= ~BIT2;

	*((uint16_t*)0x0210) = 0;
}

//TODO:Unclear feature
void f_fbcc(void)
{
	uint8_t r14;

	*((uint8_t*)0x021a) = 0x39;
	TA1CTL = 0x02d4;
	TA1CCR0 = 0x88b8;

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

//TODO:Unclear feature
void f_fc00(void)
{
	if(*(uint8_t*)0x021a < 0x40)
	{
		if(0 == (*(uint8_t*)0x021a & 0x05))
		{
			*(uint8_t*)0x0226 = *(uint8_t*)0x0203;
			f_f888();
		}

	}
	else
	{
		if(0 == (*(uint8_t*)0x021a & 0x28))
		{
			*(uint8_t*)0x0226 = 1 + *(uint8_t*)0x0203;
			f_f888();
		}
	}
}

//TODO: Unclear feature
uint16_t f_fc32(void)
{
	if(*(uint16_t*)0x0210 < 0x40)
	{
		*(uint16_t*)0x0210 &= ~BIT3;
		*(uint8_t*)0x023f = 0;
		return 0;
	}
	else
	{
		*(uint8_t*)0x023f = 1 + *(uint8_t*)0x023f;
		if(*(uint8_t*)0x023f == 0xFF)
		{
			*(uint16_t*)0x0210 |= ~BIT4;
		}
		return 1;
	}
}

//Make Flag
void MakeFlag_fc5a(void)
{
	*(uint8_t*)0x0241 = 0x00aa;
	*(uint8_t*)0x0242 = 0x0055;
	*(uint8_t*)0x0243 = 0x00cc;
	*(uint8_t*)0x0244 = 0x0033;
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

//System Initialization for C Runtime
//Clear 0x210 -> 0x248

//Repeating Test the Comparator Output
void MeasCAOut_fcb2(void)
{
	*(uint8_t*)0x0206 = 0;
	TestCAOut_fcd2();
	TestCAOut_fcd2();
	TestCAOut_fcd2();
}

void byte_memcpy_fcc2(uint8_t* dst, uint8_t* src, uint8_t sz)
{
	uint8_t cnt = sz;
	while(cnt--)
	{
		*dst++ = *src++;
	}
}

//Test the Comparator Output
void TestCAOut_fcd2(void)
{
	if(0 != (CACTL2 & BIT0))
	{
		*(uint8_t*)0x0206 = *(uint8_t*)0x0206 + 1;
	}
}

//Clear Var @ 0x0210
void Clr210_fcde(void)
{
	*((uint16_t*)0x0210) = 0;
}

/*
 * main.c
 */
int main(void) {
	// Stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;
    // Set DCO as 1MHz
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;
    BCSCTL1 |= 0x80;
    BCSCTL2 = 0;
    BCSCTL3 = 0x20;
    //Switch the OSC
    _BIS_SR(OSCOFF);

    PortInit();
    ComparatorInit();
    f_fa6a();
    ClearOut_fb96();
    TA0CTL = 0x0224;
    TA0CCR0 = 0xea60;

    while(0==(TA0CCTL0 && TAIFG))
    {
    	;
    }

    __enable_interrupt();

    f_fbcc();

	while(1) {
	}

	return 0;
}
