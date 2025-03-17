#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
    while(1);
}
#endif
uint32_t FS=120000000*2; //120 MHz
void timer0A_handler(void);
uint8_t switch_state=0;
uint32_t button=0;
uint8_t modo=0;
int
main(void)
{
    
    SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480), 120000000);

  
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);

    //enable the timer peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    // Set timer
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    // Set the count time for Timer
    TimerLoadSet(TIMER0_BASE, TIMER_A, FS);
    //Enable processor interrupts
    IntMasterEnable();
    // Enable Interrupt
    IntEnable(35);//INT_TIMER0A_TM4C129
    // Enable timer A interrupt
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    // Enable the timer
    TimerEnable(TIMER0_BASE, TIMER_A);

   
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)) {}
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)) {}
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0)) {}

    
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, 0x03); // PN0 y PN1
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, 0x11); // PF0 y PF4
    GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, 0x01); // PJ0 (USR_SW1) y PJ1 (USR_SW2)

    GPIOPadConfigSet(GPIO_PORTJ_BASE, 0x01, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    GPIOPinWrite(GPIO_PORTN_BASE, 0x03, 0x00); // Apaga PN0 y PN1
    GPIOPinWrite(GPIO_PORTF_BASE, 0x11, 0x00); // Apaga PF0 y PF4            

    
    while(1)
    {
        uint8_t buttonState = GPIOPinRead(GPIO_PORTJ_BASE, 0x01);
        // Changing the timer delay
        if (buttonState == 0x00 && modo==0) 
        {
            modo++;
            while(buttonState == 0x00){ buttonState = GPIOPinRead(GPIO_PORTJ_BASE, 0x01);}
            FS = 120000000 * 1;
            TimerLoadSet(TIMER0_BASE, TIMER_A, FS);
        }
        if (buttonState == 0x00 && modo==1) 
        {
            modo=0;
            while(buttonState == 0x00){ buttonState = GPIOPinRead(GPIO_PORTJ_BASE, 0x01);}
            FS = 120000000 * 0.5;
            TimerLoadSet(TIMER0_BASE, TIMER_A, FS);
        }
    }
}
void timer0A_handler(void)
{

    switch_state++;

    // Clear timer
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    // Sequence 1
    if (switch_state == 1)  // 0 -> 0000
    {
        GPIOPinWrite(GPIO_PORTN_BASE, 0x03, 0x00);
        GPIOPinWrite(GPIO_PORTF_BASE, 0x11, 0x00);
    }
    else if (switch_state == 2)  // 1 -> 0001
    {
        GPIOPinWrite(GPIO_PORTN_BASE, 0x03, 0x00);
        GPIOPinWrite(GPIO_PORTF_BASE, 0x11, 0x01);
    }
    else if (switch_state == 3)  // 2 -> 0010
    {
        GPIOPinWrite(GPIO_PORTN_BASE, 0x03, 0x00);
        GPIOPinWrite(GPIO_PORTF_BASE, 0x11, 0x10);
    }
    else if (switch_state == 4)  // 3 -> 0011
    {
        GPIOPinWrite(GPIO_PORTN_BASE, 0x03, 0x00);
        GPIOPinWrite(GPIO_PORTF_BASE, 0x11, 0x11);
    }
    else if (switch_state == 5)  // 4 -> 0100
    {
        GPIOPinWrite(GPIO_PORTN_BASE, 0x03, 0x01);
        GPIOPinWrite(GPIO_PORTF_BASE, 0x11, 0x00);
    }
    else if (switch_state == 6)  // 5 -> 0101
    {
        GPIOPinWrite(GPIO_PORTN_BASE, 0x03, 0x01);
        GPIOPinWrite(GPIO_PORTF_BASE, 0x11, 0x01);
    }
    else if (switch_state == 7)  // 6 -> 0110
    {
        GPIOPinWrite(GPIO_PORTN_BASE, 0x03, 0x01);
        GPIOPinWrite(GPIO_PORTF_BASE, 0x11, 0x10);
    }
    else if (switch_state == 8)  // 7 -> 0111
    {
        GPIOPinWrite(GPIO_PORTN_BASE, 0x03, 0x01);
        GPIOPinWrite(GPIO_PORTF_BASE, 0x11, 0x11);
    }
    else if (switch_state == 9)  // 8 -> 1000
    {
        GPIOPinWrite(GPIO_PORTN_BASE, 0x03, 0x02);
        GPIOPinWrite(GPIO_PORTF_BASE, 0x11, 0x00);
    }
    else if (switch_state == 10)  // 9 -> 1001
    {
        GPIOPinWrite(GPIO_PORTN_BASE, 0x03, 0x02);
        GPIOPinWrite(GPIO_PORTF_BASE, 0x11, 0x01);
    }
    else  
    {
        switch_state = 0;
    }
    
    
}
