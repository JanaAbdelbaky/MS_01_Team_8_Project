# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.12)

# Include build functions from Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
set(CMAKE_TOOLCHAIN_FILE "$ENV{PICO_SDK_PATH}/pico_toolchain.cmake")

# Set name of project (as PROJECT_NAME) and C/C standards
project(blink C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize Pico SDK
pico_sdk_init()

# Add executable source files
add_executable(${PROJECT_NAME} 
    main.c
    sound.c
    LD.c
    motor.c
    led.c
    ultrasonic.c
)

# Include FreeRTOS directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/FreeRTOS-Kernel/include
    ${CMAKE_CURRENT_LIST_DIR}/FreeRTOS-Kernel/portable/GCC/ARM_CM0
    ${CMAKE_CURRENT_LIST_DIR}/FreeRTOSConfig
)

# Specify FreeRTOS source files
file(GLOB FREERTOS_SOURCE
    ${CMAKE_CURRENT_LIST_DIR}/FreeRTOS-Kernel/portable/MemMang/heap_4.c
    ${CMAKE_CURRENT_LIST_DIR}/FreeRTOS-Kernel/portable/GCC/ARM_CM0/port.c
    ${CMAKE_CURRENT_LIST_DIR}/FreeRTOS-Kernel/croutine.c
    ${CMAKE_CURRENT_LIST_DIR}/FreeRTOS-Kernel/event_groups.c
    ${CMAKE_CURRENT_LIST_DIR}/FreeRTOS-Kernel/list.c
    ${CMAKE_CURRENT_LIST_DIR}/FreeRTOS-Kernel/queue.c
    ${CMAKE_CURRENT_LIST_DIR}/FreeRTOS-Kernel/tasks.c
    ${CMAKE_CURRENT_LIST_DIR}/FreeRTOS-Kernel/timers.c
)

# Add FreeRTOS source files to the project
target_sources(${PROJECT_NAME} PRIVATE ${FREERTOS_SOURCE})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR})



# Create map/bin/hex/uf2 files
pico_add_extra_outputs(${PROJECT_NAME})

# Link libraries
target_link_libraries(${PROJECT_NAME} 
    pico_stdlib
    hardware_pwm
)

# Enable USB output, disable UART output
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)
