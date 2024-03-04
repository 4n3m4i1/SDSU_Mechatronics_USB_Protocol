#!/usr/bin/env python3

import subprocess
import os
import signal
import time

openocd_path = "/usr/bin/openocd"
gdb_path = "/usr/bin/arm-none-eabi-gdb"

openocd_config = "openocd_sam.cfg"
gdb_script = "gdb_sam.txt"

command = "sudo rm -r build && mkdir build && cd build && cmake .. && make"
build_process = subprocess.run(command, shell=True)

openocd_cmd = f"{openocd_path} -f {openocd_config}"
openocd_process = subprocess.Popen(openocd_cmd, shell=True)
openocd_pid = openocd_process.pid

time.sleep(.25)

gdb_cmd = f"{gdb_path} -x {gdb_script} build/sam"
gdb_process = subprocess.Popen(gdb_cmd, shell=True)

gdb_process.wait()
os.kill(openocd_pid, signal.SIGTERM)