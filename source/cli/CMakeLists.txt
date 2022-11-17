# FreeRTOS Classic Distribution
# Copyright (C) 2022 Amazon.com, Inc. or its affiliates. All Rights Reserved.
# SPDX-License-Identifier: MIT

add_library( FreeRTOS_cli STATIC EXCLUDE_FROM_ALL )
target_sources( FreeRTOS_cli
                PRIVATE
                cli_conf.c
                cli_main.c
                cli_pki.c
                cli_rngtest.c
                cli_utils.c )

target_sources( FreeRTOS_cli
                PUBLIC
                cli_prv.h )

target_include_directories( FreeRTOS_cli PUBLIC
                            . )

target_link_libraries( FreeRTOS_cli PRIVATE FreeRTOS::Kernel )

add_library( FreeRTOS::CLI ALIAS FreeRTOS_cli )

