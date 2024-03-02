#ifndef USB_DEVICE_HANDLE
#define USB_DEVICE_HANDLE

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <mechatronics_usb_protocol/byte.h>

int read_message(const byte_t* buffer, const int msg_size);
int send_message(const byte_t* message, const int msg_size);

#endif