/* 
 * Use to configure callback on timer
 */

#include <asf.h>
#include "usb_enable.h"

#define CLOCK_CONFIGURE_CONST 1000
static volatile int callback_period;

void systick_init(void)
{
    SysTick_Config(SystemCoreClock/CLOCK_CONFIGURE_CONST);
    NVIC_EnableIRQ(SysTick_IRQn);
}

volatile static void(*timer_callback)(void)=NULL;
void set_timer_callback(const void(*callback)(void), const int frequency)
{
    systick_init();
    callback_period = frequency;
    timer_callback = callback;
}

volatile static int tickcount=0;
void SysTick_Handler(void)
{
	if (++tickcount==callback_period)
	{
        if (usb_enabled && timer_callback) 
        {
            timer_callback();
        }
		tickcount = 0;
	}
}