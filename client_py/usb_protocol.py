#!/usr/bin/env python3

""" 
    Alias C Header File Definitions as Easy Functions for Software to Call using Python Binding
"""

import ctypes
from dataclasses import dataclass

SYS_LIB_PATH = "/usr/local/lib/"
USB_LIB_NAME = "libmechatronics_usb_protocol.so"
USB_LIB_PATH = SYS_LIB_PATH + USB_LIB_NAME
USB_PROTOCOL = ctypes.CDLL(USB_LIB_PATH)

@dataclass
class USB_Message():
    topic_id: int
    subtopic_id: int
    flags: int
    data : bytes
    reserved: int

if __name__ == "__main__":
    USB_PROTOCOL.init_robot_actions()
    message = [
        0xAB, 0x01, 0x00, 0x00, 
        0x00, 0x00, 0x01, 0x02, 
        0x03, 0x04, 0x05, 0x06, 
        0x07, 0x00, 0x00, 0x00]
    message_bytes = bytes(message)
    USB_PROTOCOL.HANDLE_MESSAGE(message_bytes)
    init_byte = ctypes.c_int.in_dll(USB_PROTOCOL, "INIT_BYTE")
    device_topic_t = ctypes.c_int
    enum = device_topic_t.in_dll(USB_PROTOCOL, 'SYSTEM').value
    print(init_byte)
    print(enum)
