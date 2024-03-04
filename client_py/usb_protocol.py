#!/usr/bin/env python3

""" 
    Alias C Header File Definitions as Easy Functions for Software to Call using Python Binding
"""

import ctypes
from ipc_lock import InterProcessLock

SYS_LIB_PATH            = "/usr/local/lib/"
USB_CLIENT_NAME         = "libmechatronics_usb_client.so"
USB_CLIENT              = ctypes.CDLL(SYS_LIB_PATH + USB_CLIENT_NAME)

def sys_kill():
    with InterProcessLock():
        USB_CLIENT.sys_kill()
def move_motors(thrusts):
    with InterProcessLock():
        USB_CLIENT.move_motors(bytes(thrusts))
