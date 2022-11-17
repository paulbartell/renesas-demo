/*
 * FreeRTOS Reference Integration
 *
 * Copyright (C) 2022 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 * SPDX-License-Identifier: MIT
 *
 */

#ifndef _UNITY_CONFIG_H
#define _UNITY_CONFIG_H

#include "logging.h"

#ifdef UNITY_INCLUDE_PRINT_FORMATTED
    #error "Do Not set UNITY_INCLUDE_PRINT_FORMATTED"
#endif

#define TEST_PRINTF                LogSys

extern void TEST_io_putchar( char c );
extern void TEST_io_flush( void );
extern void TEST_NotifyTestStart( void );
extern void TEST_NotifyTestFinished( void );

#define UNITY_OUTPUT_CHAR( c )     TEST_putchar( c )
#define UNITY_OUTPUT_FLUSH()       TEST_io_flush()
#define UNITY_OUTPUT_START()       TEST_NotifyTestStart()
#define UNITY_OUTPUT_COMPLETE()    TEST_NotifyTestFinished()

#endif
