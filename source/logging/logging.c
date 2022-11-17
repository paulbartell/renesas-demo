/*
 * FreeRTOS STM32 Reference Integration
 *
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

/* Standard includes. */
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "message_buffer.h"

#include "platform_api.h"

/* Project Includes */
#include "logging.h"

/*-----------------------------------------------------------*/

volatile StreamBufferHandle_t xLogMBuf = NULL;
static char pcPrintBuff[ dlMAX_LOG_LINE_LENGTH ];


static void vSendLogMessage( const char * buffer,
                             unsigned int count )
{
    if( xTaskGetSchedulerState() == taskSCHEDULER_NOT_STARTED )
    {
        vPlatformLoggingWriteEarly( buffer, count );
    }
    else
    {
        vPlatformLoggingWrite( buffer, count );
    }
}

void vLoggingInit( void )
{
    xLogMBuf = xMessageBufferCreate( dlLOGGING_STREAM_LENGTH );
}

/*-----------------------------------------------------------*/

void vLoggingPrintf( const char * const pcLogLevel,
                     const char * const pcFileName,
                     const unsigned long ulLineNumber,
                     const char * const pcFormat,
                     ... )
{
    uint32_t ulLenTotal = 0;
    int32_t lLenPart = -1;
    va_list args;
    const char * pcTaskName = NULL;
    BaseType_t xSchedulerWasSuspended = pdFALSE;

    /* Additional info to place at the start of the log line */
    if( xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED )
    {
        pcTaskName = pcTaskGetName( NULL );
    }
    else
    {
        pcTaskName = "None";
    }

    if( xTaskGetSchedulerState() == taskSCHEDULER_RUNNING )
    {
        xSchedulerWasSuspended = pdTRUE;
        /* Suspend the scheduler to access pcPrintBuff */
        vTaskSuspendAll();
    }

    pcPrintBuff[ 0 ] = '\0';
    lLenPart = snprintf( pcPrintBuff,
                         dlMAX_PRINT_STRING_LENGTH,
                         "<%-3.3s> %8lu [%-10.10s] ",
                         pcLogLevel,
                         ( ( unsigned long ) xTaskGetTickCount() / portTICK_PERIOD_MS ) & 0xFFFFFF,
                         pcTaskName );

    configASSERT( lLenPart > 0 );

    if( lLenPart < dlMAX_PRINT_STRING_LENGTH )
    {
        ulLenTotal = lLenPart;
    }
    else
    {
        ulLenTotal = dlMAX_PRINT_STRING_LENGTH;
    }

    if( ulLenTotal < dlMAX_PRINT_STRING_LENGTH )
    {
        /* There are a variable number of parameters. */
        va_start( args, pcFormat );
        lLenPart = vsnprintf( &pcPrintBuff[ ulLenTotal ],
                              ( dlMAX_PRINT_STRING_LENGTH - ulLenTotal ),
                              pcFormat,
                              args );
        va_end( args );

        configASSERT( lLenPart > 0 );

        if( lLenPart + ulLenTotal < dlMAX_PRINT_STRING_LENGTH )
        {
            ulLenTotal += lLenPart;
        }
        else
        {
            ulLenTotal = dlMAX_PRINT_STRING_LENGTH;
        }
    }

    /* remove any \r\n\0 characters at the end of the message */
    while( ulLenTotal > 0 &&
           ( pcPrintBuff[ ulLenTotal - 1 ] == '\r' ||
             pcPrintBuff[ ulLenTotal - 1 ] == '\n' ||
             pcPrintBuff[ ulLenTotal - 1 ] == '\0' ) )
    {
        pcPrintBuff[ ulLenTotal - 1 ] = '\0';
        ulLenTotal--;
    }

    if( ( pcFileName != NULL ) &&
        ( ulLineNumber > 0 ) &&
        ( ulLenTotal < dlMAX_LOG_LINE_LENGTH ) )
    {
        /* Add the trailer including file name and line number */
        lLenPart = snprintf( &pcPrintBuff[ ulLenTotal ],
                             ( dlMAX_LOG_LINE_LENGTH - ulLenTotal ),
                             " (%s:%lu)",
                             pcFileName,
                             ulLineNumber );

        configASSERT( lLenPart > 0 );

        if( lLenPart + ulLenTotal < dlMAX_LOG_LINE_LENGTH )
        {
            ulLenTotal += lLenPart;
        }
        else
        {
            ulLenTotal = dlMAX_LOG_LINE_LENGTH;
        }
    }

    vSendLogMessage( ( void * ) pcPrintBuff, ulLenTotal );

    if( xSchedulerWasSuspended == pdTRUE )
    {
        xTaskResumeAll();
    }
}

/*-----------------------------------------------------------*/
void vLoggingDeInit( void )
{
}
