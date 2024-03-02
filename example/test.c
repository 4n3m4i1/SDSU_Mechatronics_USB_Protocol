#include <mechatronics_usb_protocol/usb_protocol.h>

void main(void)
{
    init_robot_actions();
    const byte_t message[6] = {INIT_BYTE, EMPTY_FIELD, SYSTEM, SYSTEM_KILL, EMPTY_FIELD, EMPTY_FIELD};
    HANDLE_MESSAGE(message);
}