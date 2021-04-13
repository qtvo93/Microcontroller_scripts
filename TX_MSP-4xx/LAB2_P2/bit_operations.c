/* Functions that implement bit-level operations
 *
 */

#include <stdint.h>
#include "bit_operations.h"

uint8_t
countBits (uint8_t v)
{
    uint8_t count = 0;

    unsigned short i;

    /*for loop is to iterate from 7th to 0th bit to check which bits are set */
    for (i = 1 << 7; i > 0; i = i / 2)
    {
    if(v & i)
    {
    count++;
    }
    }
    return count;

}

int
isPowerOfTwo (uint8_t v)
{
    int status = 0;
    uint8_t temp = v - 1;
    if(temp & v)
    {
        status = 0;
    }
    else
    {
        status = 1 ;
    }
    return status;
}

uint8_t
rearrangeBits (uint8_t n)
{
    uint8_t i, value =0;
    int bit1 = 0;
    int bit0 = 0;
    int count = 7, j;

    for (i = 1 << 7; i > 0; i = i / 2)
    {
    if(n & i)
    {
    bit1++;
    }
    else
    {
    bit0++;
    }
    }

    i=0;
    for(j=0; j<bit1; j++)
    {

    i= 1 << count--;
    value = value | i ;
    }

    return value;

}
