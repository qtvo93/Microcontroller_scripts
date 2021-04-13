/* Description: Skeleton code for the program monitor
 *
 * Author: Naga Kandasamy
*******************************************************************************/
/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>

/* User-specific includes. */
#include "uart_functions.h"
#include "blur_filter.h"


const Timer_A_ContinuousModeConfig continuousModeConfig=
    {
     TIMER_A_CLOCKSOURCE_ACLK,
     TIMER_A_CLOCKSOURCE_DIVIDER_1,
     TIMER_A_TAIE_INTERRUPT_ENABLE,
     TIMER_A_DO_CLEAR

    };
uint16_t time1=0;
uint16_t time2=0;
uint16_t ovf=0;
uint16_t cnt=0;

float timeint=0.0f;
uint32_t M;
/* Global variables containing the input and output images. */
image_t in, out;

int
main (void)
{
    /* Stop Watchdog  */
    MAP_WDT_A_holdTimer ();
    initUART ();

    // Set up LFXT and from that derive ACLK at 32 KHz
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,GPIO_PIN0|GPIO_PIN1,GPIO_PRIMARY_MODULE_FUNCTION);
    CS_setExternalClockSourceFrequency(32768,48000000);
    CS_initClockSignal(CS_ACLK,CS_LFXTCLK_SELECT,CS_CLOCK_DIVIDER_1);

    // Set up DCOCLK at 12 MHz and from that derive CPU clock MCLK at 12 MHz
        CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_12);
        CS_initClockSignal(CS_MCLK,CS_DCOCLK_SELECT,CS_CLOCK_DIVIDER_1);
        CS_setReferenceOscillatorFrequency (CS_REFO_128KHZ); // Reference oscillator is set to 32KHz
        CS_initClockSignal (CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_8);
        M=CS_getMCLK();
        WDT_A_initWatchdogTimer(WDT_A_CLOCKSOURCE_ACLK,WDT_A_CLOCKITERATIONS_32K);


        // Configure Timer A1 in continuous mode and start it, clear overflow
        Timer_A_configureContinuousMode(TIMER_A1_BASE, &continuousModeConfig);
        Interrupt_enableInterrupt(INT_TA1_N);
        Interrupt_enableMaster();
        WDT_A_startTimer();
            acquireImage (&in, MIN_VALUE, MAX_VALUE, SIZE); // Acquire image

                blurFilter (&in, &out); // Process image
            writeString("Done.............");
            WDT_A_holdTimer();
            while(1);
        }

        // Interrupt Handler to count overflows
        void TA1_N_IRQHandler(void)
                {
                    Timer_A_clearInterruptFlag(TIMER_A1_BASE);
                    ovf++;
                }



