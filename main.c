#include <stdint.h>
#include <msp430.h>

void SimpleDelay(uint32_t d)
{
	volatile uint32_t i;
	i = d*100;
	do i--;
	while(i != 0);
}
/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
	// Set P1.0 and P1.6 to output direction
	P1DIR |= ((1<<6) | (1<<0));
	P1OUT = 0;

	while(1) {
		//Toggle P1.0 and P1.6
		P1OUT ^= ((1<<6) | (1<<0));

		SimpleDelay(20);
	}

	return 0;
}
