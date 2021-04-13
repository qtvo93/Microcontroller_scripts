#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard includes. */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

/* User-specific includes. */
#include "uart_functions.h"


uint16_t ovf =0;

    const Timer_A_ContinuousModeConfig continuousModeConfig=
    {
     TIMER_A_CLOCKSOURCE_ACLK,
    TIMER_A_CLOCKSOURCE_DIVIDER_1,
     TIMER_A_TAIE_INTERRUPT_ENABLE,
     TIMER_A_DO_CLEAR
    };

    const Timer_A_CaptureModeConfig captureModeConfig=
    {
     TIMER_A_CAPTURECOMPARE_REGISTER_2,
     TIMER_A_CAPTUREMODE_RISING_EDGE,
     TIMER_A_CAPTURE_INPUTSELECT_CCIxA,
     TIMER_A_CAPTURE_SYNCHRONOUS,
     TIMER_A_CAPTURECOMPARE_INTERRUPT_ENABLE,
     TIMER_A_OUTPUTMODE_OUTBITVALUE
    };
     uint8_t i=0;
     uint32_t j=0;
     float Timeint;
     volatile uint16_t CaptureValues[2]={0,0};

     int main(void)

     { MAP_WDT_A_holdTimer();

       CS_setReferenceOscillatorFrequency(CS_REFO_32KHZ);
       CS_initClockSignal(CS_ACLK,CS_REFOCLK_SELECT,CS_CLOCK_DIVIDER_4);
       GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P2,     GPIO_PIN5,GPIO_PRIMARY_MODULE_FUNCTION);
     Timer_A_configureContinuousMode(TIMER_A0_BASE, &continuousModeConfig);
       Timer_A_initCapture(TIMER_A0_BASE, &captureModeConfig);
       Timer_A_enableCaptureCompareInterrupt (TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2);
       Interrupt_enableInterrupt(INT_TA0_N);
        Interrupt_enableMaster();
       Timer_A_clearCaptureCompareInterrupt(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2);
       Timer_A_startCounter(TIMER_A0_BASE,TIMER_A_CONTINUOUS_MODE);

        while(1)
       {

     }
 }

 void TA0_N_IRQHandler(void)
 {  writeFloat(Timeint);
    uint32_t status = Timer_A_getInterruptStatus(TIMER_A0_BASE);
    if(status ==1){
        Timer_A_clearInterruptFlag (TIMER_A0_BASE);
        ovf++;
    }
    else if (status == 0){
               if(i==0){
            CaptureValues[i]=Timer_A_getCaptureCompareCount(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2);
            ovf=0;
            i++;
        }
        else if(i>0)
       {
           CaptureValues[i]=Timer_A_getCaptureCompareCount(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2);
          Timeint=(float)(CaptureValues[i]-CaptureValues[i-1]+ovf*65536)/8000.0f;
            i=0;
       }
       Timer_A_clearCaptureCompareInterrupt(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2);
    }

  }
