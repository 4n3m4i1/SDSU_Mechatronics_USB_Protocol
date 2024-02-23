cmake_minimum_required(VERSION 3.5.0)

project(mechatronics_usb_protocol_server)

file(GLOB SOURCES src/*.c)
file(GLOB HEADERS include/*.h)

include_directories(include)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
install(TARGETS ${PROJECT_NAME} DESTINATION lib)
