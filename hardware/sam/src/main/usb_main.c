#include "usb_enable.h"
#include "usb_timer.h"
#include "mech_usb_protocol.h"
#include "usb_actions.h"
#include "led_f.h"

#define USB_PACKET_SIZE_BYTES 32
#define TIMER_PERIOD 100
#define CLEAR_BUFFER(buffer, size) \
                                    do { \
                                        for (int i = 0; i < (size); i++) { \
                                            (buffer)[i] = 0; \
                                        } \
                                    } while(0)
#define ARE_EQUAL(buffer, msg) memcmp(buffer, &msg, sizeof(buffer)) == 0

static unsigned char buffer[USB_PACKET_SIZE_BYTES] = {0};

void timer_callback(void)
{

}

void enter_loop(void)
{
    for (;;)
    {
        const int byte = udi_cdc_getc();
        if (byte == INIT_BYTE)
        {
            SET_LIGHT_ON();
            const byte_t meta_flags = udi_cdc_getc();
            const byte_t msg_size = GET_MESSAGE_SIZE(meta_flags); 
            udi_cdc_read_buf(buffer, msg_size);
            HANDLE_MESSAGE(buffer, msg_size);
        }   
        SET_LIGHT_OFF();
        CLEAR_BUFFER(buffer, USB_PACKET_SIZE_BYTES);
    }
}

void set_robot_actions()
{
    init_robot_actions();
}

int main(void) 
{
    set_robot_actions();
    start_usb_cdc();
    set_timer_callback(&timer_callback, TIMER_PERIOD);
    enter_loop();
}