# FreeRTOS Classic Distribution
# Copyright (C) 2022 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
# SPDX-License-Identifier: MIT

#
# FreeRTOS Kernel
#
check_init_submodule( kernel )
add_library( FreeRTOS_Kernel STATIC EXCLUDE_FROM_ALL )

# Kernel source files
target_sources( FreeRTOS_Kernel
                PRIVATE
                kernel/event_groups.c
                kernel/list.c
                kernel/queue.c
                kernel/stream_buffer.c
                kernel/tasks.c
                kernel/timers.c )

# Kernel Headers
target_include_directories( FreeRTOS_Kernel
                            PUBLIC
                            kernel/include
                            ../config )

target_sources( FreeRTOS_Kernel
                PUBLIC
                kernel/include/FreeRTOS.h
                kernel/include/StackMacros.h
                kernel/include/atomic.h
                kernel/include/croutine.h
                kernel/include/deprecated_definitions.h
                kernel/include/event_groups.h
                kernel/include/list.h
                kernel/include/message_buffer.h
                kernel/include/mpu_prototypes.h
                kernel/include/mpu_wrappers.h
                kernel/include/portable.h
                kernel/include/projdefs.h
                kernel/include/queue.h
                kernel/include/semphr.h
                kernel/include/stack_macros.h
                kernel/include/stream_buffer.h
                kernel/include/task.h
                kernel/include/timers.h )


# FreeRTOS Kernel Port source files
if( "${CMAKE_C_COMPILER_ID}" MATCHES "Clang" OR "${CMAKE_C_COMPILER_ID}" MATCHES "GNU" )

    target_sources( FreeRTOS_Kernel
                    PRIVATE
                    kernel/portable/GCC/RX600v2/port.c )

    target_include_directories( FreeRTOS_Kernel
                                PUBLIC
                                kernel/portable/GCC/RX600v2 )

    target_sources( FreeRTOS_Kernel
                    PUBLIC
                    kernel/portable/GCC/RX600v2/portmacro.h )

elseif( "${CMAKE_C_COMPILER_ID}" MATCHES "IAR" )
    target_sources( FreeRTOS_Kernel
                    PRIVATE
                    kernel/portable/IAR/RXv2/port.c
                    kernel/portable/IAR/RXv2/port_asm.s )

    target_include_directories( FreeRTOS_Kernel
                                PUBLIC
                                kernel/portable/IAR/RXv2 )

    target_sources( FreeRTOS_Kernel
                    PUBLIC
                    kernel/portable/IAR/RXv2/portmacro.h )

elseif( "${CMAKE_C_COMPILER_ID}" MATCHES "RXC" )
    target_sources( FreeRTOS_Kernel
                    PRIVATE
                    kernel/portable/Renesas/RX600v2/port.c
                    kernel/portable/Renesas/RX600v2/port_asm.src )

    target_include_directories( FreeRTOS_Kernel
                                PUBLIC
                                kernel/portable/Renesas/RX600v2 )

    target_sources( FreeRTOS_Kernel
                    PUBLIC
                    kernel/portable/Renesas/RX600v2/portmacro.h )
endif()

# Heap 4
target_sources( FreeRTOS_Kernel
                PRIVATE
                kernel/portable/MemMang/heap_4.c )

target_link_libraries( FreeRTOS_Kernel PUBLIC FreeRTOS::Logging )
target_link_libraries( FreeRTOS_Kernel PUBLIC platform_config )

add_library( FreeRTOS::Kernel ALIAS FreeRTOS_Kernel )