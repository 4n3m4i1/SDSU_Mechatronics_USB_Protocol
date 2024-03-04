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
            const unsigned char meta_flags_byte = udi_cdc_getc();
            const MetaFlags meta_flags = EXTRACT_META_FLAGS(meta_flags_byte);
            const unsigned char msg_size = meta_flags.MSG_SIZE-2;
            udi_cdc_read_buf(buffer, msg_size);
            HANDLE_MESSAGE(buffer, msg_size);
        }   
        SET_LIGHT_OFF();
        CLEAR_BUFFER(buffer, USB_PACKET_SIZE_BYTES);
    }
}

void test(const byte_t* data)
{
    SET_LIGHT_ON();
}

int main(void) 
{
    init_robot_actions();
    set_robot_action(MOTORS, MOTOR_MOVE, &test);
    start_usb_cdc();
    set_timer_callback(&timer_callback, TIMER_PERIOD);
    enter_loop();
}