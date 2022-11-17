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
#include "mbedtls_transport.h"

extern void vMQTTAgentTask( void * );
extern void vSubscribePublishTestTask( void * );

void SetupMqttTestParam( MqttTestParam_t * pTestParam )
{
    TlsTransportStatus_t xTlsStatus = TLS_TRANSPORT_SUCCESS;

    configASSERT( pTestParam != NULL );

    /* Initialization of timestamp for MQTT. */
    ulGlobalEntryTimeMs = MqttTestGetTimeMs();

    /* Setup the transport interface. */
    xTransport.send = mbedtls_transport_send;
    xTransport.recv = mbedtls_transport_recv;

    pxNetworkContext = mbedtls_transport_allocate();
    configASSERT( pxNetworkContext != NULL );

    xNetworkCredentials.xPrivateKey = xPkiObjectFromLabel( TLS_KEY_PRV_LABEL );
    xNetworkCredentials.xClientCertificate = xPkiObjectFromLabel( TLS_CERT_LABEL );
    xNetworkCredentials.pxRootCaChain[ 0 ] = xPkiObjectFromLabel( TLS_ROOT_CA_CERT_LABEL );

    xTlsStatus = mbedtls_transport_configure( pxNetworkContext,
                                              NULL,
                                              &xNetworkCredentials.xPrivateKey,
                                              &xNetworkCredentials.xClientCertificate,
                                              xNetworkCredentials.pxRootCaChain,
                                              1 );

    configASSERT( xTlsStatus == TLS_TRANSPORT_SUCCESS );

    pxSecondNetworkContext = mbedtls_transport_allocate();
    configASSERT( pxSecondNetworkContext != NULL );

    xSecondNetworkCredentials.xPrivateKey = xPkiObjectFromLabel( TLS_KEY_PRV_LABEL );
    xSecondNetworkCredentials.xClientCertificate = xPkiObjectFromLabel( TLS_CERT_LABEL );
    xSecondNetworkCredentials.pxRootCaChain[ 0 ] = xPkiObjectFromLabel( TLS_ROOT_CA_CERT_LABEL );

    xTlsStatus = mbedtls_transport_configure( pxSecondNetworkContext,
                                              NULL,
                                              &xSecondNetworkCredentials.xPrivateKey,
                                              &xSecondNetworkCredentials.xClientCertificate,
                                              xSecondNetworkCredentials.pxRootCaChain,
                                              1 );

    configASSERT( xTlsStatus == TLS_TRANSPORT_SUCCESS );

    pTestParam->pTransport = &xTransport;
    pTestParam->pNetworkContext = pxNetworkContext;
    pTestParam->pSecondNetworkContext = pxSecondNetworkContext;
    pTestParam->pNetworkConnect = prvTransportNetworkConnect;
    pTestParam->pNetworkDisconnect = prvTransportNetworkDisconnect;
    pTestParam->pNetworkCredentials = &xNetworkCredentials;
    pTestParam->pGetTimeMs = MqttTestGetTimeMs;
}

int RunDeviceAdvisorDemo( void )
{
    BaseType_t xResult;

    xResult = xTaskCreate( vMQTTAgentTask, "MQTTAgent", 2048, NULL, 10, NULL );
    configASSERT( xResult == pdTRUE );

    xResult = xTaskCreate( vSubscribePublishTestTask, "PubSub", 6144, NULL, 10, NULL );
    configASSERT( xResult == pdTRUE );

    return 0;
}
