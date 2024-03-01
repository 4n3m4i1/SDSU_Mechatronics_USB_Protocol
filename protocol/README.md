# USB_Protocol

## Building

mkdir build && cd build && cmake .. && make && sudo make install

## Linking

Building will create a dynamic library and install to /usr/local/lib as well as make the protocol's public headers available in /usr/local/include. You can use protocol functions by including with #include <usb_protocol.h>

## Getting Started

`actions` - This is where the user can set which functions will be called for the associated topic/subtopic

`subtopics` - This will contain actual implementation of subsystems 

`parser` - The parser will take in a message (presumably sent over USB) and call the appropriate function

## Maintainers

[@Conner Sommerfield](https://github.com/Repo-Factory/)  