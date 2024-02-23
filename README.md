# SDSU_Mechatronics_USB_Protocol
USB CDC Robotics Protocol + ROS2 Replacement IPC

## Building

We need to fill this out, gcc is cool but if we do that we should script out the build process and put it in install.sh
Otherwise we can use CMake

## Getting Started

Clone this repository

    git clone https://github.com/4n3m4i1/SDSU_Mechatronics_USB_Protocol

`client_py` - Software-friendly python wrapper that hides implementation details and exposes nice endpoints to the user, will link to protocol SO

`hardware` - Embedded program (in the future multiple) for specific hardware implementation of USB (as of now supports SAM4E)   

`protocol` - Public Headers and definitions that define our specific implementation of a USB messaging protocol

`server` - Static binary which will run on linux side and bridge the python client and embedded system

## Maintainers

[@Joseph De Vico](https://github.com/4n3m4i1)
[@Conner Sommerfield](https://github.com/Repo-Factory/)