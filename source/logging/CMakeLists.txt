# FreeRTOS Classic Distribution
# Copyright (C) 2022 Amazon.com, Inc. or its affiliates. All Rights Reserved.
# SPDX-License-Identifier: MIT

add_library( FreeRTOS_logging STATIC EXCLUDE_FROM_ALL )
target_sources( FreeRTOS_logging
                PRIVATE
                # cli_uart_drv.c
                logging.c )

target_sources( FreeRTOS_logging
                PUBLIC
                logging.h
                logging_levels.h )

target_include_directories( FreeRTOS_logging PUBLIC
                            .
                            ../include )

target_link_libraries( FreeRTOS_logging PRIVATE FreeRTOS::Kernel )

add_library( FreeRTOS::Logging ALIAS FreeRTOS_logging )
