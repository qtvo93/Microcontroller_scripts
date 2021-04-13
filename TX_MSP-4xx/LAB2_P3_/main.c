#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "uart_functions.h"

int main(void)
{

    WDT_A_hold (WDT_A_BASE); /* Stop watchdog timer */

    initUART (); /* Initialize UART. */
    writeString ("LED FLASHING WITH SECS INTERVAL: ");
/* Set P1.0, to output direction */

 /* Set DCO to 12 MHz. */
    CS_setDCOCenteredFrequency (CS_DCO_FREQUENCY_12);

    GPIO_setAsOutputPin(GPIO_PORT_P6,GPIO_PIN4);
    GPIO_setOutputLowOnPin(GPIO_PORT_P6,GPIO_PIN4);

    GPIO_setAsInputPinWithPullDownResistor(GPIO_PORT_P6,GPIO_PIN0);//set up external switch on P6.0
        /* Main loop that runs on the board */
    while(1){
           if(GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN0)==GPIO_INPUT_PIN_HIGH)//check if external switch is pressed

                GPIO_setOutputLowOnPin(GPIO_PORT_P6,GPIO_PIN4);
            else

                GPIO_setOutputHighOnPin(GPIO_PORT_P6,GPIO_PIN4);
            }

}
