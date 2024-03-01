cmake_minimum_required(VERSION 3.5.0)

project(mechatronics_usb_protocol)

file(GLOB SOURCES 
    src/parser/usb_parse.c
    src/subtopics/system.c
    src/subtopics/power.c
    src/subtopics/motor.c
    src/actions/usb_actions.c
)

file(GLOB HEADERS 
    include/parser/msg_types.h
    include/parser/usb_parse.h
    include/subtopics/system.h
    include/subtopics/power.h
    include/subtopics/motor.h
    include/topics/usb_topics.h
)

include_directories(
    include/parser
    include/subtopics
    include/topics
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})
add_executable(${PROJECT_NAME}.bin main.c)
target_link_libraries(${PROJECT_NAME}.bin ${PROJECT_NAME})
install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include/${PROJECT_NAME})