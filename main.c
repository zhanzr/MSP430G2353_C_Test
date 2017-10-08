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
	uint16_t* p_r4;
	uint16_t r14;
	uint16_t r15;

	TA0CTL |= BIT2;
	if(0 != (BIT0 & TA0CCTL0))
	{
		*(uint8_t*)0x021d = 0x11;
		*(uint8_t*)0x021e = 0;
	}
	TA0CCTL0 &= ~BIT0;
	TA0CCR0 = 0x010c;
	TA0CCTL1 &= ~BIT0;
	TA0CCR1 = 0x0044;
	if(*(uint8_t*)0x021d >= 0x0a)
	{
		p_r4 = 0x0200;
	}
	else
	{
		if(*(uint8_t*)0x021d >= 8)
		{
			p_r4 = 0x0201;
		}
		else
		{
			p_r4 = 0x0202;
		}
	}

	while(0==(TA0CCTL1 & BIT0))
	{
		;
	}

	MeasCAOut_fcb2();

	*(uint8_t*)0x0206 = *(uint8_t*)0x0206 / 4;

	*p_r4 = *p_r4 / 2;

	*(uint8_t*)0x021d = *(uint8_t*)0x021d - 1;
	if(0 != *(uint8_t*)0x021d)
	{
		goto COM_A_ISR_EXIT_F5E4;
	}

	*(uint8_t*)0x0201 = *(uint8_t*)0x0201 & 0xc0;
	if(0 == *(uint8_t*)0x021e)
	{
		TA0CCR0 = 0x01c8;

	}
	else
	{
		goto l_f180;
	}

	while(0==(TA0CCTL0 & BIT0))
	{
		;
	}

	TA0CTL |= BIT2;
	TA0CCR0 = 0x0878;
	TA0CCTL0 &= ~BIT0;
	*(uint16_t*)0x0212 = *(uint16_t*)0x0200;
	//CLRC
	*(uint8_t*)0x0202 = *(uint8_t*)0x0202 / 2;

	r14 = *(uint8_t*)0x0202;
	*(uint8_t*)0x021c = r14;
	r15 = *(uint8_t*)0x0200;
	r15 += *(uint8_t*)0x0201;
	r15 += r14;
	*(uint8_t*)0x0220 = r15;
	if((r14 == 0x3c) || (r14 == 0x4f))
	{
		*(uint16_t*)0x0210 |= BIT0;
		*(uint8_t*)0x021d = 8;
	}
	else
	{
		*(uint16_t*)0x0210 &= ~BIT0;
		*(uint8_t*)0x021d = 0x11;
	}

	*(uint8_t*)0x0240 = f_fa06(*(uint16_t*)0x0212);
	if(*(uint8_t*)0x0240 == *(uint8_t*)0x0203)
	{
		*(uint8_t*)0x021a &= ~BIT6;
		*(uint16_t*)0x0210 |= BIT1;
		if(BIT1 & *(uint8_t*)0x021a)
		{
			goto l_f170;
		}
		else
		{
			goto l_f174;
		}
	}
	else
	{
		r14 = *(uint8_t*)0x0240;
		r15 = *(uint8_t*)0x0203;
		r15 ++;
		if(r15 == r14)
		{
			*(uint8_t*)0x021a |= BIT6;
			*(uint16_t*)0x0210 |= BIT1;
			if(BIT4 & *(uint8_t*)0x021a)
			{
				goto l_f170;
			}
			else
			{
				goto l_f174;
			}
		}
		else
		{
			goto l_f170;
		}
	}
l_f170:
	*(uint16_t*)0x0210 &= ~BIT1;
l_f174:
	*(uint8_t*)0x021e = 1;
	*(uint8_t*)0x021f = 2;
	goto COM_A_ISR_EXIT_F5E4;

l_f180:

COM_A_ISR_EXIT_TA0IFG_F5E0:
	TA0CCTL0 |= BIT0;
COM_A_ISR_EXIT_F5E4:
	CACTL1 &= ~BIT0;
//	BIC.W   #0x0010,0x0008(SP)
//	POP.W   R14
//	POP.W   R15
//	POP.W   R12
//	POP.W   R13
}

//TODO:Unclear feature
void f_f888(void)
{
	uint8_t r14;
	uint8_t r15;

	*(uint16_t*)0x0210 &= ~BIT6;
	r14 = *(uint8_t*)0x0224 & 0x0F;
	*(uint8_t*)0x023e = r14;
	r15 = 0;
	if(0==BIT0 & r14)
	{
		*(uint8_t*)0x023d = BIT1;
		r14 = 0xc0;
	}
	else
	{
		*(uint8_t*)0x023e = 1 + *(uint8_t*)0x023e;
		*(uint8_t*)0x023d = BIT3;
		r14 = *(uint8_t*)0x0224;
	}

//l_f8b8 whole

l_f8c0:
	TA0CCR0 = 0x998;
	TA0CTL |= TACLR;
	TA0CCTL0 &= ~TAIFG;
	CACTL1 &= ~CAIFG;
l_f8d2:
	if(CAIFG & CACTL1)
	{
		TA0CTL |= TACLR;
		TA0CCTL0 &= ~TAIFG;
		if(r14 >= 0)
		{
			TA0CCR0 = 0x0028;
			while(0 == TA0CCTL0 & TAIFG)
			{
				;
			}
		}
		else
		{
			TA0CCR0 = 0x0302;

			while(0==(BIT0 & TA0CCTL0))
			{
				;
			}

			TA0CCTL0 &= ~BIT0;
			TA0CCR0 = 0x042e;
			MeasCAOut_fcb2();
			if(0==*(uint16_t*)0x0206)
			{
				*(uint16_t*)0x0210 |= BIT6;
				return;
			}

			while(0==(BIT0 & TA0CCTL0))
			{
				;
			}
		}
	}
	else
	{
		//l_f8f2->l_f8f9
		if(TA0CCTL0 & BIT0)
		{
			*(uint16_t*)0x0210 |= BIT6;
			return;
		}
		else
		{
			goto l_f8d2;
		}
	}

	P1OUT |= BIT2;
	TA0CCTL0 &= ~BIT0;
	TA0CCR0 += 0x01e0;
	while(0==(BIT0 & TA0CCTL0))
	{
		;
	}

	P1OUT &= ~BIT2;
	TA0CCTL0 &= ~BIT0;
	TA0CCR0 = 0x074e;
	while(0==(BIT0 & TA0CCTL0))
	{
		;
	}

	r14 <<= 1;
	*(uint8_t*)0x023d = *(uint8_t*)0x023d - 1;
	if(0 != *(uint8_t*)0x023d)
	{
		goto l_f8c0;
	}
	if(1 == *(uint8_t*)0x023e)
	{
		return;
	}
	r15 ++;
	if(r15 != *(uint8_t*)0x023e)
	{
		r14 = *(uint8_t*)(0x0224 + r15);
		goto l_f8c0;
	}
	TA0CTL |= BIT2;
	TA0CCR0 = 0x07d0;
	TA0CCTL0 &= ~BIT0;
	CACTL1 &= ~BIT0;

	do{
		if(BIT0 & CACTL1)
		{
			*(uint8_t*)0x0210 &= ~BIT4;
			return;
		}
	}while(0 == (BIT0 & TA0CCTL0));
//
//l_f984:
//	*(uint16_t*)0x0210 |= BIT6;
//	return;
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

    WDTCTL = WDTPW | WDTHOLD;
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
	    WDTCTL = WDT_ARST_250;
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
void main(void) {
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
    goto l_f676;
l_f648:
	*((uint16_t*)0x0216) = 0;
	*((uint8_t*)0x0247) = *((uint8_t*)0x0247) + 1;
l_f650:
	*((uint16_t*)0x0216) = *((uint16_t*)0x0216) + 1;
l_f654:
	if(0x00a0 != *((uint16_t*)0x0218))
	{
		if(0==(0x0220 & *((uint16_t*)0x0210)))
		{
			if(0x00a0 != *((uint16_t*)0x0246))
			{
				// Stop watchdog timer
			    WDTCTL = WDTPW | WDTHOLD;
			    __bis_SR_register(CPUOFF);
			}
		}
	}
l_f676:
	WDTCTL = WDT_ARST_250;

	if(0x00a0 == *((uint16_t*)0x0218))
	{
		*((uint16_t*)0x0218) = 0;
		if(0x64 == *((uint8_t*)0x020c))
		{
				if(0==BIT2 & *((uint8_t*)0x021a))
				{
					f_fbcc();
				}
				*((uint8_t*)0x021a) = 0x3d;
		}
		else
		{
			if(0x65 == *((uint8_t*)0x020c))
			{
				*((uint8_t*)0x021a) = 0x38;
			}
			else
			{
				if(0x67 == *((uint8_t*)0x020c))
				{
					if(0==BIT2 & *((uint8_t*)0x021a))
					{
						f_fbcc();
					}
					*((uint8_t*)0x021a) = 5;
				}
				else
				{
					*((uint8_t*)0x021a) = 0;
				}
			}
		}
	}
l_f6d0:
	if(0x00a0 == *((uint8_t*)0x0246))
	{
		*((uint8_t*)0x0246) = 0;
		if(BIT5 & *((uint16_t*)0x0210))
		{
			if((0x64 == *((uint8_t*)0x020c)) || (0x65 == *((uint8_t*)0x020c)))
			{
				*((uint8_t*)0x0246) = *((uint8_t*)0x021b) | BIT1;
				goto l_f726;
			}
			else
			{
				*((uint8_t*)0x0246) = *((uint8_t*)0x021b) | BIT0;
				goto l_f726;
			}
		}
		else
		{
			goto l_f700;
		}
	}
	else
	{
		goto l_f7aa;
	}
l_f700:
	if(0 != *((uint8_t*)0x021b) & BIT0)
	{
		*((uint8_t*)0x021b) &= ~BIT0;
		goto l_f726;
	}

	if(0 != *((uint8_t*)0x021b) & BIT1)
	{
		if((0x64 == *((uint8_t*)0x020c)) || (0x65 == *((uint8_t*)0x020c)))
		{
			*((uint8_t*)0x021b) &= ~BIT1;
		}
	}
l_f726:
	if(0 != *((uint16_t*)0x0210) & BIT9)
	{
		*((uint8_t*)0x0246) = *((uint8_t*)0x021b) | BIT1;
	}
	else if((0 != *((uint8_t*)0x021b) & BIT1) &&
		(0x64 != *((uint8_t*)0x020c)) &&
		(0x65 != *((uint8_t*)0x020c)))
	{
		*((uint8_t*)0x021b) &= ~BIT1;
	}

	if(0 != *((uint8_t*)0x021b))
	{
		if(0 == *((uint8_t*)0x0247))
		{
			TA1CTL = 0x0214;
			TA1CCR0 = 0x1388;
			TA1CCTL0 &= ~BIT0;
			*((uint16_t*)0x0216) = 0;
			P2OUT &= BIT1;
			*((uint8_t*)0x0247) = BIT0;
		}
		else
		{
			goto l_f776;
		}
	}
	else
	{
		goto l_f792;
	}
l_f776:
	*((uint8_t*)0x0245) = 0x28;
	if(0 != *((uint8_t*)0x021b) & BIT1)
	{
		*((uint16_t*)0x0214) = 0x00fa;
		goto l_f7aa;
	}
	else
	{
		*((uint16_t*)0x0214) = 0x190;
		goto l_f7aa;
	}
l_f792:
	TA1CTL = 0;
	TA1CCTL0 &= ~BIT0;
	*((uint8_t*)0x0247) = 0;
	*((uint16_t*)0x0216) = 0;
	P2OUT &= ~BIT1;
	P2OUT &= ~BIT2;
l_f7aa:
	if(0==(TA1CCTL0 & BIT0))
	{
		goto l_f654;
	}
	TA1CCTL0 &= ~BIT0;
	if(*((uint8_t*)0x0247) < 6)
	{
		goto l_f7e0;
	}
	if(*((uint16_t*)0x0216) >= *((uint8_t*)0x0245))
	{
		goto l_f7cc;
	}
	P2OUT |= BIT1;
	goto l_f650;
l_f7cc:
	if(*((uint16_t*)0x0216) >= *((uint16_t*)0x0214))
	{
		goto l_f7da;
	}
	P2OUT &= ~BIT1;
	goto l_f650;
l_f7da:
	*((uint16_t*)0x0216) = 0;
	goto l_f650;
l_f7e0:
	if(*((uint8_t*)0x0247) != 1)
	{
		goto l_f800;
	}
	if(*((uint16_t*)0x0216) != 0)
	{
		goto l_f7f2;
	}
	P2OUT &= ~BIT2;
	goto l_f650;
l_f7f2:
	if(*((uint16_t*)0x0216) >= 0x0096)
	{
		goto l_f648;
	}
	P2OUT &= ~BIT2;
	goto l_f650;
l_f800:
	if(*((uint8_t*)0x0247) != 2)
	{
		goto l_f820;
	}
	if(*((uint16_t*)0x0216) >= 2)
	{
		goto l_f812;
	}
	P2OUT |= BIT2;
	goto l_f650;
l_f812:
	if(*((uint16_t*)0x0216) >= 0x0096)
	{
		goto l_f648;
	}
	P2OUT &= ~BIT2;
	goto l_f650;
l_f820:
	if(*((uint8_t*)0x0247) != 3)
	{
		goto l_f842;
	}
	if(*((uint16_t*)0x0216) >= 2)
	{
		goto l_f834;
	}
	P2OUT |= BIT2;
	goto l_f650;
l_f834:
	if(*((uint16_t*)0x0216) >= 0x0096)
	{
		goto l_f648;
	}
	P2OUT &= ~BIT2;
	goto l_f650;
l_f842:
	if(*((uint8_t*)0x0247) != 4)
	{
		goto l_f864;
	}
	if(*((uint16_t*)0x0216) >= 0x001e)
	{
		goto l_f856;
	}
	P2OUT |= BIT2;
	goto l_f650;
l_f856:
	if(*((uint16_t*)0x0216) >= 0x0096)
	{
		goto l_f648;
	}
	P2OUT &= ~BIT2;
	goto l_f650;
l_f864:
	if(*((uint8_t*)0x0247) != 5)
	{
		goto l_f650;
	}
	if(*((uint16_t*)0x0216) >= 0x0032)
	{
		goto l_f87a;
	}
	P2OUT |= BIT2;
	goto l_f650;
l_f87a:
	if(*((uint16_t*)0x0216) >= 0x0096)
	{
		goto l_f648;
	}
	P2OUT &= ~BIT2;
	goto l_f650;

	return;
}
