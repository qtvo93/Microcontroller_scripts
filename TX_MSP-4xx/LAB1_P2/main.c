#include "msp.h"


/**
 * main.c
 */
char s[]= "China, India and U.S.A. are the 3 largest countries by population – in the order 1,2,3.";
char x;
uint16_t total = 0;
uint16_t lower = 0;
uint16_t upper = 0;
uint16_t number = 0;
uint16_t blank = 0;
uint16_t special = 0;


void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;
    while(*(s+total)!= '\0')
    {
        x=*(s+total);
        if ((x >= 'A') && (x <= 'Z'))
            upper++;
        else if ((x >= 'a') && (x <= 'z'))
            lower++;
        else if ((x >= '0') && (x <= '9'))
            number++;
        else if (x ==' ')
            blank++;
        else
            special++;

         total++;
    }
    while(1);
}
