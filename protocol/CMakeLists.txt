cmake_minimum_required(VERSION 3.5.0)

project(mechatronics_usb_protocol)

file(GLOB SOURCES src/*.c)
file(GLOB HEADERS include/*.h)

include_directories(include)

add_library(${PROJECT_NAME} SHARED ${SOURCES})
install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include/${PROJECT_NAME})