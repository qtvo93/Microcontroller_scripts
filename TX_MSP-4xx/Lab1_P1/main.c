#include "msp.h"

uint16_t A=0xC34E;
uint16_t B=0x0077;
uint16_t C= 0xABCD;
uint16_t X;
uint16_t Y;
/**
 * main.c
 */
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;
	X = ~(A & B)| C;
	Y = ~ B & (A^C);

	while(1);
}
