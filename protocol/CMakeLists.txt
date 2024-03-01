cmake_minimum_required(VERSION 3.5.0)

project(mechatronics_usb_protocol)

file(GLOB SOURCES 
    src/parser/usb_parse.c
    src/parser/usb_flags.c
    src/subtopics/system.c
    src/subtopics/power.c
    src/subtopics/motor.c
    src/actions/usb_actions.c
)

file(GLOB HEADERS 
    include/usb_protocol.h
    include/parser/usb_parse.h
    include/parser/usb_flags.h
    include/parser/msg_types.h
    include/subtopics/system.h
    include/subtopics/power.h
    include/subtopics/motor.h
    include/actions/usb_actions.h
    util/byte.h
)

include_directories(
    include
    include/parser
    include/subtopics
    include/actions
    util
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})
add_library(${PROJECT_NAME}_static STATIC ${SOURCES})
add_executable(${PROJECT_NAME}.bin usb_test.c)
target_link_libraries(${PROJECT_NAME}.bin ${PROJECT_NAME})
install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(TARGETS ${PROJECT_NAME}_static DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include/${PROJECT_NAME})