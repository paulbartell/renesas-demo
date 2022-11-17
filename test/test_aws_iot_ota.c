/*
 * FreeRTOS Reference Integration
 *
 * Copyright (C) 2022 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 * SPDX-License-Identifier: MIT
 *
 */

#include "logging_levels.h"
#define LOG_LEVEL    LOG_ERROR
#include "logging.h"

#include "FreeRTOS.h"

extern void vMQTTAgentTask( void * );
extern void vOTAUpdateTask( void * );

int RunOtaE2eDemo( void )
{
    BaseType_t xResult;

    xResult = xTaskCreate( vMQTTAgentTask, "MQTTAgent", 2048, NULL, 10, NULL );
    configASSERT( xResult == pdTRUE );

    xResult = xTaskCreate( vOTAUpdateTask, "OTAUpdate", 4096, NULL, tskIDLE_PRIORITY + 1, NULL );
    configASSERT( xResult == pdTRUE );

    return 0;
}
