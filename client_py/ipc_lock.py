""" 
    This lock is to make sure multiple processes don't write to USB device
    I think it will work but not sure, it uses a global file and checks if it exists to determine lock condition
"""

import os
import time

lock_file = '/tmp/USB_MECH.lock'
WRITE_MODE = 'w'
DUMMY_MSG  = 'LOCKED'
SLEEP_INTERVAL = 0.001

class InterProcessLock:
    def acquire(self):
        while os.path.exists(lock_file):
            time.sleep(SLEEP_INTERVAL)
        with open(lock_file, WRITE_MODE) as f:
            f.write(DUMMY_MSG) # This is to create the file, while it exists, no other process with IPC lock can write to USB device

    def release(self):
        if os.path.exists(lock_file):
            os.remove(lock_file)

    def __enter__(self):
        self.acquire()
        return self

    def __exit__(self, exc_type, exc_value, traceback):
        self.release()
        return False  
    
