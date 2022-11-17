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

#include "FreeRTOS.h"
#include "task.h"

#include "platform_api.h"
#include "logging.h"

/**
 * @brief Initialize logging for use prior to starting the scheduler.
 */
void vPlatformLoggingInitEarly( void )
{
    configASSERT( xTaskGetSchedulerState() != taskSCHEDULER_RUNNING );

}

/**
 * @brief Initialize logging while the scheduler is running.
 */
void vPlatformLoggingInit( void )
{

}

/**
 * @brief Send a log message prior to starting the scheduler.
 *
 * This api call may block.
 *
 * @param pcBuffer
 * @param uxLength
 */
void vPlatformLoggingWriteEarly( const char * pcBuffer,
                                 const size_t uxLength )
{
    configASSERT( xTaskGetSchedulerState() != taskSCHEDULER_RUNNING );


}

/**
 * @brief
 *
 * @param pcBuffer
 * @param uxLength
 */
void vPlatformLoggingWrite( const char * pcBuffer,
                            const size_t uxLength )
{

}

/**
 * @brief
 *
 */
void vPlatformLoggingDyingGasp( void )
{

}

/**
 * @brief
 *
 */
void vPlatformLoggingDeInit( void )
{

}

BaseType_t xPortIsInsideInterrupt( void )
{
    return pdFALSE;
}

