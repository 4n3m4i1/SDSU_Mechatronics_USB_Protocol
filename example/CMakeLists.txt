cmake_minimum_required(VERSION 3.5.0)

project(test)

file(GLOB SOURCES 
    test.c
)

include_directories(
    include
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} mechatronics_usb_protocol)