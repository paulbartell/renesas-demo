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
#include "FreeRTOS.h"


/*-----------------------------------------------------------*/

#if ( ipconfigUSE_LLMNR != 0 ) || ( ipconfigUSE_NBNS != 0 ) || ( ipconfigDHCP_REGISTER_HOSTNAME == 1 )

    const char * pcApplicationHostnameHook( void )
    {
        /* Assign the name "FreeRTOS" to this network node.  This function will
         * be called during the DHCP: the machine will be registered with an IP
         * address plus this name. */
        return "FreeRTOS";
    }

#endif

/*-----------------------------------------------------------*/

#if ( ipconfigUSE_LLMNR != 0 ) || ( ipconfigUSE_NBNS != 0 )

    BaseType_t xApplicationDNSQueryHook( const char * pcName )
    {
        BaseType_t xReturn;

        /* Determine if a name lookup is for this node.  Two names are given
         * to this node: that returned by pcApplicationHostnameHook() and that set
         * by mainDEVICE_NICK_NAME. */
        if( _stricmp( pcName, pcApplicationHostnameHook() ) == 0 )
        {
            xReturn = pdPASS;
        }
        else if( _stricmp( pcName, mainDEVICE_NICK_NAME ) == 0 )
        {
            xReturn = pdPASS;
        }
        else
        {
            xReturn = pdFAIL;
        }

        return xReturn;
    }

#endif /* if ( ipconfigUSE_LLMNR != 0 ) || ( ipconfigUSE_NBNS != 0 ) */

/*
 * Set *pulNumber to a random number, and return pdTRUE. When the random number
 * generator is broken, it shall return pdFALSE.
 */
BaseType_t xApplicationGetRandomNumber( uint32_t * pulNumber )
{
    *pulNumber = ( uint32_t ) uxRand();
    return pdTRUE;
}

/*-----------------------------------------------------------*/

/*
 * Callback that provides the inputs necessary to generate a randomized TCP
 * Initial Sequence Number per RFC 6528.  THIS IS ONLY A DUMMY IMPLEMENTATION
 * THAT RETURNS A PSEUDO RANDOM NUMBER SO IS NOT INTENDED FOR USE IN PRODUCTION
 * SYSTEMS.
 */
uint32_t ulApplicationGetNextSequenceNumber( uint32_t ulSourceAddress,
                                             uint16_t usSourcePort,
                                             uint32_t ulDestinationAddress,
                                             uint16_t usDestinationPort )
{
    ( void ) ulSourceAddress;
    ( void ) usSourcePort;
    ( void ) ulDestinationAddress;
    ( void ) usDestinationPort;

    return ( uint32_t ) uxRand();
}

/*-----------------------------------------------------------*/

void vPlatformInitIpStack( void )
{
    UBaseType_t uxRandomNumber;
    BaseType_t xResult;
    uint8_t ucIPAddress[ 4 ];
    uint8_t ucNetMask[ 4 ] = { 255, 255, 0, 0 };
    uint8_t ucNullAddress[ 4 ] = { 0, 0, 0, 0 };
    uint8_t ucMACAddress[ 6 ];

    /* Generate a ramdom number */
    uxRandomNumber = uxRand();

    /* Generate a random MAC address in the reserved range */
    ucMACAddress[ 0 ] = 0x00;
    ucMACAddress[ 1 ] = 0x11;
    ucMACAddress[ 2 ] = ( uxRandomNumber & 0xFF );
    ucMACAddress[ 3 ] = ( ( uxRandomNumber >> 8 ) & 0xFF );
    ucMACAddress[ 4 ] = ( ( uxRandomNumber >> 16 ) & 0xFF );
    ucMACAddress[ 5 ] = ( ( uxRandomNumber >> 24 ) & 0xFF );

    /* Assign a link-local address in the 169.254.0.0/16 range */
    ucIPAddress[ 0 ] = 169U;
    ucIPAddress[ 1 ] = 254U;
    ucIPAddress[ 2 ] = ( ( uxRandomNumber >> 16 ) & 0xFF );
    ucIPAddress[ 3 ] = ( ( uxRandomNumber >> 24 ) & 0xFF );

    xResult = FreeRTOS_IPInit( ucIPAddress, ucNetMask, ucNullAddress, ucNullAddress, ucMACAddress );
    configASSERT( xResult == pdTRUE );
}
/*-----------------------------------------------------------*/
