cmake_minimum_required(VERSION 3.5.0)

project(mechatronics_usb_client)

file(GLOB SOURCES 
    src/usb_protocol_client.c
    src/usb_device_handle.c
)

file(GLOB HEADERS 
    include/usb_protocol_client.h
    include/usb_device_handle.h
)

include_directories(
    include
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_link_libraries(${PROJECT_NAME} mechatronics_usb_protocol)
install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include/${PROJECT_NAME})