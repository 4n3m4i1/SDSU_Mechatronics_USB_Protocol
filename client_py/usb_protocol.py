""" 
    Alias C Header File Definitions as Easy Functions for Software to Call using Python Binding
"""

import ctypes
from dataclasses import dataclass

LIBRARY_PATH = "path.so"
USB_MSGS = ctypes.CDLL(LIBRARY_PATH)

@dataclass
class USB_Message():
    topic_id: int
    subtopic_id: int
    flags: int
    data : bytes
    reserved: int