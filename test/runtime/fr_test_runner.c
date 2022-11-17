#include "logging_levels.h"

#define LOG_LEVEL    LOG_DEBUG

#include "logging.h"

/* FreeRTOS includes. */
#include "FreeRTOS.h"

#define TEST_PRINT_BUFF_SZ   1024
#define TEST_PRINT_IDX_MAX ( TEST_PRINT_BUFF_SZ - 2U )

/*-----------------------------------------------------------*/

/* The buffer to store test result. The content will be printed if an eol character
 * is received */
static char pcTestResultBuffer[ TEST_PRINT_BUFF_SZ ];
static size_t uxBufferIndex = 0;

/*-----------------------------------------------------------*/

void TEST_io_flush( void )
{
    if( uxBufferIndex > TEST_PRINT_IDX_MAX )
    {
        uxBufferIndex = TEST_PRINT_IDX_MAX;
    }

    pcTestResultBuffer[ uxBufferIndex ] = '\00';

    if( uxBufferIndex > 0U )
    {
        LogSYS( "%.*s", uxBufferIndex, pcTestResultBuffer );

        /* Wait for 1 seconds to let print task empty its buffer. */
        vTaskDelay( pdMS_TO_TICKS( 1000UL ) );

        uxBufferIndex = 0U;
    }
}

/*-----------------------------------------------------------*/

void TEST_io_putchar( char c )
{
    if( c == '\n' )
    {
        TEST_io_flush();
    }
    else
    {
        if( ( uxBufferIndex >= TEST_PRINT_IDX_MAX ) )
        {
            TEST_io_flush();
        }

        pcTestResultBuffer[ uxBufferIndex ] = c;
        uxBufferIndex++;
    }
}

/*-----------------------------------------------------------*/

void TEST_NotifyTestStart()
{
    LogSYS( "---------STARTING TESTS---------" );
}
/*-----------------------------------------------------------*/

void TEST_NotifyTestFinished()
{
    LogSYS( "-------ALL TESTS FINISHED-------" );
}

/*-----------------------------------------------------------*/
