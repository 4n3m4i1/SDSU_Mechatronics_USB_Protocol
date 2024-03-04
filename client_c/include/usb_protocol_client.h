#ifndef USB_PROTOCOL_CLIENT
#define USB_PROTOCOL_CLIENT

#include <mechatronics_usb_protocol/usb_protocol.h>

/* All Available Public APIs for Embedded System */

int sys_kill();
int move_motors(const byte_t* thrusts);

#endif