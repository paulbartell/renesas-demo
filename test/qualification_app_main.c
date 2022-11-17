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

#include "logging_levels.h"

#define LOG_LEVEL    LOG_DEBUG

#include "logging.h"

#include "test_param_config.h"
#include "test_execution_config.h"
#include "qualification_test.h"
#include "transport_interface_test.h"
#include "ota_pal_test.h"
#include "mqtt_test.h"

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "mbedtls_transport.h"
#include "sys_evt.h"         /* For get network ready event. */
#include "mqtt_agent_task.h" /* For device advisor test. */
#include "ota_config.h"

/**
 * @brief Socket send and receive timeouts to use.  Specified in milliseconds.
 */
#define mqttexampleTRANSPORT_SEND_RECV_TIMEOUT_MS    ( 750 )

typedef struct NetworkCrendentials
{
    PkiObject_t xPrivateKey;
    PkiObject_t xClientCertificate;
    PkiObject_t pxRootCaChain[ 1 ];
} NetworkCredentials_t;

static NetworkCredentials_t xNetworkCredentials = { 0 };
static NetworkCredentials_t xSecondNetworkCredentials = { 0 };
static TransportInterface_t xTransport = { 0 };
static NetworkContext_t * pxNetworkContext = NULL;
static NetworkContext_t * pxSecondNetworkContext = NULL;

static NetworkConnectStatus_t prvTransportNetworkConnect( void * pvNetworkContext,
                                                          TestHostInfo_t * pxHostInfo,
                                                          void * pvNetworkCredentials )
{
    TlsTransportStatus_t xTlsStatus = TLS_TRANSPORT_SUCCESS;

    xTlsStatus = mbedtls_transport_connect( pvNetworkContext,
                                            pxHostInfo->pHostName,
                                            ( uint16_t ) pxHostInfo->port,
                                            mqttexampleTRANSPORT_SEND_RECV_TIMEOUT_MS,
                                            mqttexampleTRANSPORT_SEND_RECV_TIMEOUT_MS );

    configASSERT( TLS_TRANSPORT_SUCCESS == xTlsStatus );

    return NETWORK_CONNECT_SUCCESS;
}

static void prvTransportNetworkDisconnect( void * pNetworkContext )
{
    mbedtls_transport_disconnect( pNetworkContext );
}

/*-----------------------------------------------------------*/

void run_qualification_main( void * pvArgs )
{
    ( void ) pvArgs;

    LogInfo( "Start qualification test." );
    LogInfo( "Waiting network connected event." );

    /* Block until the network interface is connected */
    ( void ) xEventGroupWaitBits( xSystemEvents,
                                  EVT_MASK_NET_CONNECTED,
                                  0x00,
                                  pdTRUE,
                                  portMAX_DELAY );

    LogInfo( "Run qualification test." );

    RunQualificationTest();

    LogInfo( "End qualification test." );

    for( ; ; )
    {
        vTaskDelay( pdMS_TO_TICKS( 30000UL ) );
    }

    vTaskDelete( NULL );
}

/*-----------------------------------------------------------*/

