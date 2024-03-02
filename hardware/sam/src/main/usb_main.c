#include "usb_enable.h"
#include "usb_timer.h"
#include <mechatronics_usb_protocol/usb_protocol.h>

#define USB_PACKET_SIZE_BYTES 4
#define TIMER_PERIOD 100
#define CLEAR_BUFFER(buffer, size) \
                                    do { \
                                        for (int i = 0; i < (size); i++) { \
                                            (buffer)[i] = 0; \
                                        } \
                                    } while(0)
#define ARE_EQUAL(buffer, msg) memcmp(buffer, &msg, sizeof(buffer)) == 0

static unsigned char buffer[USB_PACKET_SIZE_BYTES] = {0};

void enter_loop(void)
{
    for (;;)
    {
        if (udi_cdc_getc() == INIT_BYTE)
        {
            const unsigned char meta_flags_byte = udi_cdc_getc();
            const MetaFlags meta_flags = EXTRACT_META_FLAGS(meta_flags_byte);
            const unsigned char msg_size = meta_flags.MSG_SIZE - 2;
            udi_cdc_read_buf(buffer, msg_size);
            HANDLE_MESSAGE(buffer, msg_size);
        }   
        CLEAR_BUFFER(buffer, USB_PACKET_SIZE_BYTES);
    }
}

void timer_callback(void)
{
    // Handle CAN and device polling
}

int main(void) 
{
    start_usb_cdc();
    set_timer_callback(&timer_callback, TIMER_PERIOD);
    enter_loop();
}