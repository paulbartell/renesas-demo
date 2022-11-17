# FreeRTOS Classic Distribution
# Copyright (C) 2022 Amazon.com, Inc. or its affiliates. All Rights Reserved.
# SPDX-License-Identifier: MIT

# tinycbor used by the AWS IoT OTA library
check_init_submodule( tinycbor )
add_library( TinyCBOR STATIC EXCLUDE_FROM_ALL )

target_sources( TinyCBOR
                PRIVATE
                tinycbor/src/cborpretty.c
                tinycbor/src/cborpretty_stdio.c
                tinycbor/src/cborencoder.c
                tinycbor/src/cborencoder_close_container_checked.c
                tinycbor/src/cborerrorstrings.c
                tinycbor/src/cborparser.c
                tinycbor/src/cborparser_dup_string.c )

target_include_directories( TinyCBOR
                            PUBLIC
                            tinycbor/src )

target_sources( TinyCBOR
                PUBLIC
                tinycbor/src/cbor.h
                tinycbor/src/cborinternal_p.h
                tinycbor/src/cborjson.h
                tinycbor/src/compilersupport_p.h
                tinycbor/src/tinycbor-version.h
                tinycbor/src/utf8_p.h )
