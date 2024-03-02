# SDSU_Mechatronics_USB_Protocol

USB CDC Robotics Protocol to replace CAN communications between linux computer and embedded system.
This is also intended to abandon ROS2 based protocol from before 

## Building

Each project can be built separately or by using the [install.sh] script

## Getting Started

    git clone https://github.com/4n3m4i1/SDSU_Mechatronics_USB_Protocol

`client_c` - Static binary which will run on linux side and bridge the python client and embedded system

`client_py` - Software-friendly python wrapper that hides implementation details and exposes nice endpoints to the user, will link to protocol .SO

`hardware` - Embedded program (in the future multiple) for specific hardware implementation of USB (as of now supports SAM4E)   

`protocol` - Public Headers and definitions that define our specific implementation of a USB messaging protocol

## Maintainers

[@Conner Sommerfield](https://github.com/Repo-Factory/)  

[@Joseph De Vico](https://github.com/4n3m4i1)  

