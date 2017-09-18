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

uint8_t f_fb0c(uint8_t i_r12)
{
	uint8_t r12;
//
//	CLR.B   R15
//	CLR.W   R14
//	JMP     l_fb1c
//	l_fb12:
//	BIS.W   #0x0003,R14
//	SUB.B   0xf03c(R15),R12
//	l_fb1a:
//	INC.B   R15
//	l_fb1c:
//	CMP.B   #0x0005,R15
//	JHS     l_fb3a
//	RLA.W   R14
//	RLA.W   R14
//	CMP.B   0xf037(R15),R12
//	JLO     l_fb1a
//	CMP.B   0xf03c(R15),R12
//	JHS     l_fb12
//	BIS.W   #1,R14
//	SUB.B   0xf037(R15),R12
//	JMP     l_fb1a
//	l_fb3a:
//	MOV.W   R14,R12
//	AND.W   #0xff00,R12
//	RLA.W   R12
//	RLA.W   R12
//	RLA.W   R12
//	RLA.W   R12
//	RLA.W   R12
//	RLA.W   R12
//	AND.B   #-1,R14
//	ADD.W   R14,R12
//	RET
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

//		MOV.B   #1,R12
//		CALL    #f_fb0c
//		MOV.W   R12,&0x0204
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
//	CLR.B   &0x0241
//	CLR.B   &0x0242
//	CLR.B   &0x0243
//	CLR.B   &0x0244
//	CLR.B   &0x021a
//	MOV.W   #0x00a0,&0x0218
//	CLR.B   &0x021b
//	CLR.B   &0x0247
//	CLR.B   &0x0246
//	CLR.W   &0x0216
//	BIC.B   #2,&P2OUT
//	BIC.B   #4,&P2OUT
//	BR      #f_fcde
//
//f_fbcc:
//	MOV.B   #0x0039,&0x021a
//	MOV.W   #0x02d4,&TA1CTL
//	MOV.W   #0x88b8,&TA1CCR0
//	MOV.B   #0x000a,R14
//	JMP     l_fbf6
//l_fbe4:
//	BIT.W   #1,&TA1CCTL0
//	JLO     l_fbe4
//	BIC.W   #1,&TA1CCTL0
//	MOV.W   #0x5a0d,&WDTCTL
//	ADD.B   #-1,R14
//l_fbf6:
//	TST.B   R14
//	JNE     l_fbe4
//	CLR.W   &TA1CTL
//	RET
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
