cmake_minimum_required(VERSION 3.12)

project(sam)

set(MCU "cortex-m4")
set(FPU "softfp") 

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I/usr/local/include")

add_executable(
    ${PROJECT_NAME}
    src/ASF/common/services/sleepmgr/sam/sleepmgr.c 
    src/ASF/common/services/usb/class/cdc/device/udi_cdc.c 
    src/ASF/common/services/usb/udc/udc.c 
    src/ASF/common/utils/stdio/read.c 
    src/ASF/sam/drivers/pio/pio_handler.c 
    src/ASF/sam/drivers/udp/udp_device.c 
    src/ASF/sam/drivers/usart/usart.c 
    src/ASF/common/utils/stdio/write.c 
    src/ASF/common/services/usb/class/cdc/device/udi_cdc_desc.c 
    src/ASF/common/services/serial/usart_serial.c 
    src/ASF/sam/drivers/can/can.c 
    src/ASF/sam/drivers/matrix/matrix.c 
    src/ASF/sam/drivers/pio/pio.c 
    src/ASF/sam/drivers/uart/uart.c 
    src/ASF/common/services/clock/sam4e/sysclk.c 
    src/ASF/common/utils/interrupt/interrupt_sam_nvic.c 
    src/ASF/sam/boards/sam4e_xplained_pro/init.c 
    src/ASF/sam/drivers/pmc/pmc.c 
    src/ASF/sam/drivers/pmc/sleep.c 
    src/ASF/sam/utils/cmsis/sam4e/source/templates/exceptions.c 
    src/ASF/sam/utils/cmsis/sam4e/source/templates/gcc/startup_sam4e.c 
    src/ASF/sam/utils/cmsis/sam4e/source/templates/system_sam4e.c 
    src/ASF/sam/utils/syscalls/gcc/syscalls.c 
    
    src/main/src/usb_enable.c
    src/main/src/usb_timer.c
    src/main/usb_main.c
)

include_directories(
    src/ 
    src/ASF/ 
    src/ASF/common/ 
    src/ASF/common/boards/ 
    src/ASF/common/services/ 
    src/ASF/common/services/clock/ 
    src/ASF/common/services/clock/sam4e/ 
    src/ASF/common/services/gpio/ 
    src/ASF/common/services/gpio/sam_gpio/ 
    src/ASF/common/services/ioport/ 
    src/ASF/common/services/ioport/sam/ 
    src/ASF/common/services/serial/ 
    src/ASF/common/services/serial/sam_uart/ 
    src/ASF/common/services/sleepmgr/ 
    src/ASF/common/services/sleepmgr/sam/ 
    src/ASF/common/services/usb/ 
    src/ASF/common/services/usb/class/ 
    src/ASF/common/services/usb/class/cdc/ 
    src/ASF/common/services/usb/class/cdc/device/ 
    src/ASF/common/services/usb/udc/ 
    src/ASF/common/utils/ 
    src/ASF/common/utils/interrupt/ 
    src/ASF/common/utils/stdio/ 
    src/ASF/common/utils/stdio/stdio_serial/ 
    src/ASF/sam/ 
    src/ASF/sam/boards/ 
    src/ASF/sam/boards/sam4e_xplained_pro/ 
    src/ASF/sam/drivers/ 
    src/ASF/sam/drivers/can/ 
    src/ASF/sam/drivers/matrix/ 
    src/ASF/sam/drivers/pio/ 
    src/ASF/sam/drivers/pmc/ 
    src/ASF/sam/drivers/uart/ 
    src/ASF/sam/drivers/udp/ 
    src/ASF/sam/drivers/usart/ 
    src/ASF/sam/utils/ 
    src/ASF/sam/utils/cmsis/ 
    src/ASF/sam/utils/cmsis/sam4e/ 
    src/ASF/sam/utils/cmsis/sam4e/include/ 
    src/ASF/sam/utils/cmsis/sam4e/include/component/ 
    src/ASF/sam/utils/cmsis/sam4e/include/instance/ 
    src/ASF/sam/utils/cmsis/sam4e/include/pio/ 
    src/ASF/sam/utils/cmsis/sam4e/source/ 
    src/ASF/sam/utils/cmsis/sam4e/source/templates/ 
    src/ASF/sam/utils/cmsis/sam4e/source/templates/gcc/ 
    src/ASF/sam/utils/fpu/ 
    src/ASF/sam/utils/header_files/ 
    src/ASF/sam/utils/linker_scripts/ 
    src/ASF/sam/utils/linker_scripts/sam4e/ 
    src/ASF/sam/utils/linker_scripts/sam4e/sam4e16/ 
    src/ASF/sam/utils/linker_scripts/sam4e/sam4e16/gcc/ 
    src/ASF/sam/utils/make/ 
    src/ASF/sam/utils/preprocessor/ 
    src/ASF/sam/utils/syscalls/ 
    src/ASF/sam/utils/syscalls/gcc/ 
    src/ASF/thirdparty/ 
    src/ASF/thirdparty/CMSIS/ 
    src/ASF/thirdparty/CMSIS/Include/ 
    src/ASF/thirdparty/CMSIS/Lib/ 
    src/ASF/thirdparty/CMSIS/Lib/GCC/ 
    src/config/
)

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

add_library(mech_usb_protocol ${USB_PROTOCOL_SOURCES})
target_link_libraries(${PROJECT_NAME} mech_usb_protocol)

target_compile_options(${PROJECT_NAME} PRIVATE
    -mcpu=${MCU}
    -mthumb
    -Wall
    -O2
    -I/usr/local/include
    -D__SAM4E16E__
    -DDEBUG
    -DBOARD=SAM4E_XPLAINED_PRO
    -Dscanf=iscanf
    -DARM_MATH_CM4=true
    -Dprintf=iprintf
    -D__SAM4E16E__
)

# Add linker options
target_link_options(${PROJECT_NAME} PRIVATE
    -mcpu=${MCU}
    -mthumb
    -T ${CMAKE_SOURCE_DIR}/src/ASF/sam/utils/linker_scripts/sam4e/sam4e16/gcc/flash.ld
    -Wl,-Map=${PROJECT_NAME}.map
    -Wl,--start-group
    -larm_cortexM4lf_math_${FPU}
    -lm
    -Wl,--end-group
    -L"${CMAKE_SOURCE_DIR}/src/ASF/thirdparty/CMSIS/Lib/GCC"
    -Wl,--gc-sections
    -Wl,--entry=Reset_Handler
    -Wl,--cref
)