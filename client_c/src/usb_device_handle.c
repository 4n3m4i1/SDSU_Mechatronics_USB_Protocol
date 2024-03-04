#include "usb_device_handle.h"
#include <stdio.h>

#define FILE_PERMISSION_SETTINGS 0666
#define SERIAL_FILE "/dev/ttyACM1"

int read_message(const byte_t* buffer, const int msg_size)
{
    int serial_file = open(SERIAL_FILE, O_RDONLY);
    if (serial_file == -1) {
        return 1;
    }
    read(serial_file, (void*)buffer, msg_size);
    close(serial_file);
}

int send_message(const byte_t* message, const int msg_size)
{
    int serial_file = open(SERIAL_FILE, O_WRONLY | O_CREAT | O_TRUNC, FILE_PERMISSION_SETTINGS);
    if (serial_file == -1) {
        return 1;
    }
    write(serial_file, message, msg_size);
    close(serial_file);
}

