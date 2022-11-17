/*
 * FreeRTOS Renesas RX Reference Integration
 *
 * Copyright (C) 2022 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * SPDX-License-Identifier: MIT
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

#ifndef PLATFORM_API_H
#define PLATFORM_API_H

#include "FreeRTOS.h"
#include "task.h"

void vPlatformLoggingInit( void );
void vPlatformLoggingInitEarly( void );

void vPlatformLoggingWriteEarly( const char * pcBuffer,
                                 const size_t uxLength );

void vPlatformLoggingWrite( const char * pcBuffer,
                            const size_t uxLength );

void vPlatformLoggingDyingGasp( void );

void vPlatformLoggingDeInit( void );

void vPlatformWatchdogInit( void );
void vPlatformWatchdogStart( TickType_t uxTimeoutMs );
void vPlatformWatchdogStop( void );
void vPlatformWatchdogPing( void );

void vPlatformReset( void );

#endif /* PLATFORM_API_H */