# FreeRTOS Classic Distribution
# Copyright (C) 2022 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
# SPDX-License-Identifier: MIT

set(LLHTTP_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/llhttp)

check_init_submodule( llhttp )

add_library( llhttp STATIC EXCLUDE_FROM_ALL )

target_sources( llhttp
                PRIVATE
                ${LLHTTP_SOURCE_DIR}/src/api.c
                ${LLHTTP_SOURCE_DIR}/src/http.c
                ${LLHTTP_SOURCE_DIR}/src/llhttp.c )

target_sources( llhttp
                PUBLIC
                ${LLHTTP_SOURCE_DIR}/include/llhttp.h )

target_include_directories( llhttp
                            PUBLIC ${LLHTTP_SOURCE_DIR}/include )

