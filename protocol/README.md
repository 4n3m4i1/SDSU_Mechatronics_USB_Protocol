# USB_Protocol

## Building

mkdir build && cd build && cmake .. && make && sudo make install

## Linking

Building will create a dynamic library and install to /usr/local/lib as well as make the protocol's public headers available in /usr/local/include. You can use protocol functions by including with #include <usb_protocol.h>

## Getting Started

`actions` - This is where the user can set which functions will be called for the associated topic/subtopic

`subtopics` - This will contain actual implementation of subsystems 

`parser` - The parser will take in a message (presumably sent over USB) and call the appropriate function

## Example CMake

    include_directories(
        src/utils/include
        src/main/include
        src/protocol/include
        src/protocol/include/parser
        src/protocol/include/subtopics
        src/protocol/include/actions
        src/protocol/util
    )

    file(GLOB USB_PROTOCOL_SOURCES 
        src/protocol/src/parser/usb_parse.c
        src/protocol/src/parser/usb_flags.c
        src/protocol/src/subtopics/system.c
        src/protocol/src/subtopics/power.c
        src/protocol/src/subtopics/motor.c
        src/protocol/src/actions/usb_actions.c
    )

    file(GLOB USB_PROTOCOL_HEADERS 
        src/protocol/include/mech_usb_protocol.h
        src/protocol/include/parser/usb_parse.h
        src/protocol/include/parser/usb_flags.h
        src/protocol/include/parser/msg_types.h
        src/protocol/include/subtopics/system.h
        src/protocol/include/subtopics/power.h
        src/protocol/include/subtopics/motor.h
        src/protocol/include/actions/usb_actions.h
        src/protocol/util/byte.h
    )

    add_library(mechatronics_usb_protocol STATIC ${USB_PROTOCOL_SOURCES} ${USB_PROTOCOL_HEADERS})
    target_link_libraries(${PROJECT_NAME} mechatronics_usb_protocol)

## Maintainers

[@Conner Sommerfield](https://github.com/Repo-Factory/)  