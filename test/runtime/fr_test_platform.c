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

#include <stdint.h>

#include "FreeRTOS.h"

#include "platform_function.h"

/*-----------------------------------------------------------*/

extern UBaseType_t uxRand( void );

/*-----------------------------------------------------------*/

/**
 * @brief Global entry time into the application to use as a reference timestamp
 * in the #prvGetTimeMs function. #prvGetTimeMs will always return the difference
 * between the current time and the global entry time. This will reduce the chances
 * of overflow for the 32 bit unsigned integer used for holding the timestamp.
 */
static uint32_t ulGlobalEntryTimeMs;

/*-----------------------------------------------------------*/

void FRTest_TimeDelay( uint32_t delayMs )
{
    vTaskDelay( pdMS_TO_TICKS( delayMs ) );
}

/*-----------------------------------------------------------*/

/* MqttTestGetTimeMs -> FRTest_GetTimeMs*/

uint32_t FRTest_GetTimeMs( void )
{
    TickType_t xTickCount = 0;
    uint32_t ulTimeMs = 0UL;

    /* Get the current tick count. */
    xTickCount = xTaskGetTickCount();

    /* Convert the ticks to milliseconds. */
    ulTimeMs = ( uint32_t ) pdMS_TO_TICKS( xTickCount );

    /* Reduce ulGlobalEntryTimeMs from obtained time so as to always return the
     * elapsed time in the application. */
    ulTimeMs = ( uint32_t ) ( ulTimeMs - ulGlobalEntryTimeMs );

    return ulTimeMs;
}

/*-----------------------------------------------------------*/

typedef struct TaskParam
{
    StaticSemaphore_t joinMutexBuffer;
    SemaphoreHandle_t joinMutexHandle;
    FRTestThreadFunction_t threadFunc;
    void * pParam;
    TaskHandle_t taskHandle;
} TaskParam_t;

static void ThreadWrapper( void * pParam )
{
    TaskParam_t * pTaskParam = pParam;

    if( ( pTaskParam != NULL ) && ( pTaskParam->threadFunc != NULL ) && ( pTaskParam->joinMutexHandle != NULL ) )
    {
        pTaskParam->threadFunc( pTaskParam->pParam );

        /* Give the mutex. */
        xSemaphoreGive( pTaskParam->joinMutexHandle );
    }

    vTaskDelete( NULL );
}

/*-----------------------------------------------------------*/

FRTestThreadHandle_t FRTest_ThreadCreate( FRTestThreadFunction_t threadFunc,
                                          void * pParam )
{
    TaskParam_t * pTaskParam = NULL;
    FRTestThreadHandle_t threadHandle = NULL;
    BaseType_t xReturned;

    pTaskParam = malloc( sizeof( TaskParam_t ) );
    configASSERT( pTaskParam != NULL );

    pTaskParam->joinMutexHandle = xSemaphoreCreateBinaryStatic( &pTaskParam->joinMutexBuffer );
    configASSERT( pTaskParam->joinMutexHandle != NULL );

    pTaskParam->threadFunc = threadFunc;
    pTaskParam->pParam = pParam;

    xReturned = xTaskCreate( ThreadWrapper,    /* Task code. */
                             "ThreadWrapper",  /* All tasks have same name. */
                             8192,             /* Task stack size. */
                             pTaskParam,       /* Where the task writes its result. */
                             tskIDLE_PRIORITY, /* Task priority. */
                             &pTaskParam->taskHandle );
    configASSERT( xReturned == pdPASS );

    threadHandle = pTaskParam;

    return threadHandle;
}

/*-----------------------------------------------------------*/

int FRTest_ThreadTimedJoin( FRTestThreadHandle_t threadHandle,
                            uint32_t timeoutMs )
{
    TaskParam_t * pTaskParam = threadHandle;
    BaseType_t xReturned;
    int retValue = 0;

    /* Check the parameters. */
    configASSERT( pTaskParam != NULL );
    configASSERT( pTaskParam->joinMutexHandle != NULL );

    /* Wait for the thread. */
    xReturned = xSemaphoreTake( pTaskParam->joinMutexHandle, pdMS_TO_TICKS( timeoutMs ) );

    if( xReturned != pdTRUE )
    {
        LogWarn( ( "Waiting thread exist failed after %u %d. Task abort.", timeoutMs, xReturned ) );

        /* Return negative value to indicate error. */
        retValue = -1;

        /* There may be used after free. Assert here to indicate error. */
        configASSERT( 0 );
    }

    free( pTaskParam );

    return retValue;
}

/*-----------------------------------------------------------*/

void * FRTest_MemoryAlloc( size_t size )
{
    return pvPortMalloc( size );
}

/*-----------------------------------------------------------*/

void FRTest_MemoryFree( void * ptr )
{
    return vPortFree( ptr );
}

/*-----------------------------------------------------------*/

int FRTest_GenerateRandInt()
{
    return ( int ) uxRand();
}

/*-----------------------------------------------------------*/
