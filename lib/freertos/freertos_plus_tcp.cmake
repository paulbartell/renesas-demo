# FreeRTOS Classic Distribution
# Copyright (C) 2022 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
# SPDX-License-Identifier: MIT

set( PLUS_TCP_SRC_DIR plus-tcp/source )
set( PLUS_TCP_UTILS_DIR plus-tcp/tools/tcp_utilities )
set( PLUS_TCP_PORT_DIR ${PLUS_TCP_SRC_DIR}/portable )

option(CONFIG_NET_IP_STACK_FREERTOS_PLUS_TCP "Use FreeRTOS+TCP as the IP stack." ON)

if(CONFIG_NET_IP_STACK_FREERTOS_PLUS_TCP)
    option(CONFIG_NET_IP_STACK_BUFFER_ALLOCATION_STATIC "Use static buffer allocation for FreeRTOS+TCP (BufferAllocation1)" OFF)
    option(CONFIG_NET_IP_STACK_BUFFER_ALLOCATION_DYNAMIC "Use dynamic buffer allocation for FreeRTOS+TCP (BufferAllocation2)" ON)

    check_init_submodule( plus-tcp )

    add_library( FreeRTOS_TCP STATIC EXCLUDE_FROM_ALL )

    target_sources( FreeRTOS_TCP
                    PRIVATE
                    ${PLUS_TCP_SRC_DIR}/FreeRTOS_ARP.c
                    ${PLUS_TCP_SRC_DIR}/FreeRTOS_DHCP.c
                    ${PLUS_TCP_SRC_DIR}/FreeRTOS_DNS.c
                    ${PLUS_TCP_SRC_DIR}/FreeRTOS_DNS_Cache.c
                    ${PLUS_TCP_SRC_DIR}/FreeRTOS_DNS_Callback.c
                    ${PLUS_TCP_SRC_DIR}/FreeRTOS_DNS_Networking.c
                    ${PLUS_TCP_SRC_DIR}/FreeRTOS_DNS_Parser.c
                    ${PLUS_TCP_SRC_DIR}/FreeRTOS_ICMP.c
                    ${PLUS_TCP_SRC_DIR}/FreeRTOS_IP.c
                    ${PLUS_TCP_SRC_DIR}/FreeRTOS_IP_Timers.c
                    ${PLUS_TCP_SRC_DIR}/FreeRTOS_IP_Utils.c
                    ${PLUS_TCP_SRC_DIR}/FreeRTOS_Sockets.c
                    ${PLUS_TCP_SRC_DIR}/FreeRTOS_Stream_Buffer.c
                    ${PLUS_TCP_SRC_DIR}/FreeRTOS_TCP_IP.c
                    ${PLUS_TCP_SRC_DIR}/FreeRTOS_TCP_Reception.c
                    ${PLUS_TCP_SRC_DIR}/FreeRTOS_TCP_State_Handling.c
                    ${PLUS_TCP_SRC_DIR}/FreeRTOS_TCP_Transmission.c
                    ${PLUS_TCP_SRC_DIR}/FreeRTOS_TCP_Utils.c
                    ${PLUS_TCP_SRC_DIR}/FreeRTOS_TCP_WIN.c
                    ${PLUS_TCP_SRC_DIR}/FreeRTOS_Tiny_TCP.c
                    ${PLUS_TCP_SRC_DIR}/FreeRTOS_UDP_IP.c
                    ${PLUS_TCP_UTILS_DIR}/tcp_dump_packets.c
                    ${PLUS_TCP_UTILS_DIR}/tcp_mem_stats.c
                    ${PLUS_TCP_UTILS_DIR}/tcp_netstat.c )

    target_include_directories( FreeRTOS_TCP
                                PUBLIC ${PLUS_TCP_SRC_DIR}/include
                                PUBLIC ${PLUS_TCP_UTILS_DIR}/include )

    target_sources( FreeRTOS_TCP
                    PUBLIC
                    ${PLUS_TCP_SRC_DIR}/include/FreeRTOSIPConfigDefaults.h
                    ${PLUS_TCP_SRC_DIR}/include/FreeRTOS_ARP.h
                    ${PLUS_TCP_SRC_DIR}/include/FreeRTOS_DHCP.h
                    ${PLUS_TCP_SRC_DIR}/include/FreeRTOS_DNS.h
                    ${PLUS_TCP_SRC_DIR}/include/FreeRTOS_DNS_Cache.h
                    ${PLUS_TCP_SRC_DIR}/include/FreeRTOS_DNS_Callback.h
                    ${PLUS_TCP_SRC_DIR}/include/FreeRTOS_DNS_Globals.h
                    ${PLUS_TCP_SRC_DIR}/include/FreeRTOS_DNS_Networking.h
                    ${PLUS_TCP_SRC_DIR}/include/FreeRTOS_DNS_Parser.h
                    ${PLUS_TCP_SRC_DIR}/include/FreeRTOS_ICMP.h
                    ${PLUS_TCP_SRC_DIR}/include/FreeRTOS_IP.h
                    ${PLUS_TCP_SRC_DIR}/include/FreeRTOS_IP_Private.h
                    ${PLUS_TCP_SRC_DIR}/include/FreeRTOS_IP_Timers.h
                    ${PLUS_TCP_SRC_DIR}/include/FreeRTOS_IP_Utils.h
                    ${PLUS_TCP_SRC_DIR}/include/FreeRTOS_Sockets.h
                    ${PLUS_TCP_SRC_DIR}/include/FreeRTOS_Stream_Buffer.h
                    ${PLUS_TCP_SRC_DIR}/include/FreeRTOS_TCP_IP.h
                    ${PLUS_TCP_SRC_DIR}/include/FreeRTOS_TCP_Reception.h
                    ${PLUS_TCP_SRC_DIR}/include/FreeRTOS_TCP_State_Handling.h
                    ${PLUS_TCP_SRC_DIR}/include/FreeRTOS_TCP_Transmission.h
                    ${PLUS_TCP_SRC_DIR}/include/FreeRTOS_TCP_Utils.h
                    ${PLUS_TCP_SRC_DIR}/include/FreeRTOS_TCP_WIN.h
                    ${PLUS_TCP_SRC_DIR}/include/FreeRTOS_UDP_IP.h
                    ${PLUS_TCP_SRC_DIR}/include/FreeRTOS_errno_TCP.h
                    ${PLUS_TCP_SRC_DIR}/include/IPTraceMacroDefaults.h
                    ${PLUS_TCP_SRC_DIR}/include/NetworkBufferManagement.h
                    ${PLUS_TCP_SRC_DIR}/include/NetworkInterface.h
                    ${PLUS_TCP_UTILS_DIR}/include/tcp_dump_packets.h
                    ${PLUS_TCP_UTILS_DIR}/include/tcp_mem_stats.h
                    ${PLUS_TCP_UTILS_DIR}/include/tcp_netstat.h )

    if(CONFIG_NET_IP_STACK_BUFFER_ALLOCATION_STATIC)
        target_sources( FreeRTOS_TCP PRIVATE
                        ${PLUS_TCP_PORT_DIR}/BufferManagement/BufferAllocation_1.c )
    elseif(CONFIG_NET_IP_STACK_BUFFER_ALLOCATION_DYNAMIC)
        target_sources( FreeRTOS_TCP PRIVATE
                        ${PLUS_TCP_PORT_DIR}/BufferManagement/BufferAllocation_2.c )
    else()
        message(FATAL_ERROR "No FreeRTOS+TCP buffer allocation scheme was configured. Define either CONFIG_NET_IP_STACK_BUFFER_ALLOCATION_STATIC or CONFIG_NET_IP_STACK_BUFFER_ALLOCATION_DYNAMIC.")
    endif()

    target_link_libraries(FreeRTOS_TCP PRIVATE FreeRTOS::Kernel FreeRTOS::Logging )

    #### Compiler Support ####

    # GNU GCC / LLVM Clang / ARM Clang
    if( "${CMAKE_C_COMPILER_ID}" MATCHES "Clang" OR "${CMAKE_C_COMPILER_ID}" MATCHES "GNU" )
        target_include_directories( FreeRTOS_TCP
                                    PUBLIC ${PLUS_TCP_PORT_DIR}/Compiler/GCC )

        target_sources( FreeRTOS_TCP
                        PUBLIC
                        ${PLUS_TCP_PORT_DIR}/Compiler/GCC/pack_struct_start.h
                        ${PLUS_TCP_PORT_DIR}/Compiler/GCC/pack_struct_end.h )

    elseif( "${CMAKE_C_COMPILER_ID}" MATCHES "IAR" )
        target_include_directories( FreeRTOS_TCP
                                    PUBLIC ${PLUS_TCP_PORT_DIR}/Compiler/IAR )

        target_sources( FreeRTOS_TCP
                        PUBLIC
                        ${PLUS_TCP_PORT_DIR}/Compiler/IAR/pack_struct_start.h
                        ${PLUS_TCP_PORT_DIR}/Compiler/IAR/pack_struct_end.h )

    elseif( "${CMAKE_C_COMPILER_ID}" MATCHES "RXC" )
        target_include_directories( FreeRTOS_TCP
                                    PUBLIC ${PLUS_TCP_PORT_DIR}/Compiler/Renesas )

        target_sources( FreeRTOS_TCP
                        PUBLIC
                        ${PLUS_TCP_PORT_DIR}/Compiler/Renesas/pack_struct_start.h
                        ${PLUS_TCP_PORT_DIR}/Compiler/Renesas/pack_struct_end.h )
    endif()

    #### Target Support ####
    if(CONFIG_TARGET_RX)
        target_sources( FreeRTOS_TCP
                        PRIVATE
                        ${PLUS_TCP_PORT_DIR}/NetworkInterface/RX/NetworkInterface.c
                        ${PLUS_TCP_PORT_DIR}/NetworkInterface/RX/ether_callback.c )
    endif()

    # Export namespaced target
    add_library( FreeRTOS::TCP ALIAS FreeRTOS_TCP )
endif()
