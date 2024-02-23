/* 
 * Follow ASFs API to Enable USB Peripheral
 */

#include <asf.h>
#include "usb_enable.h"

volatile bool usb_enabled = false;
bool my_callback_cdc_enable(void)
{
    return usb_enabled = true;
}
void my_callback_cdc_disable(void)
{
    usb_enabled = false;
}

void usb_init(void)
{
    udc_start();
    udi_cdc_comm_enable();
    udi_cdc_data_enable();
}

void interrupt_init(void)
{
    irq_initialize_vectors();
    cpu_irq_enable();
}

void start_usb_cdc(void)
{
    sysclk_init();
    interrupt_init();
    board_init();
    usb_init();
}