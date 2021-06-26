/*
    FreeRTOS V7.3.0 - Copyright (C) 2012 Real Time Engineers Ltd.


    ***************************************************************************
     *                                                                       *
     *    FreeRTOS tutorial books are available in pdf and paperback.        *
     *    Complete, revised, and edited pdf reference manuals are also       *
     *    available.                                                         *
     *                                                                       *
     *    Purchasing FreeRTOS documentation will not only help you, by       *
     *    ensuring you get running as quickly as possible and with an        *
     *    in-depth knowledge of how to use FreeRTOS, it will also help       *
     *    the FreeRTOS project to continue with its mission of providing     *
     *    professional grade, cross platform, de facto standard solutions    *
     *    for microcontrollers - completely free of charge!                  *
     *                                                                       *
     *    >>> See http://www.FreeRTOS.org/Documentation for details. <<<     *
     *                                                                       *
     *    Thank you for using FreeRTOS, and thank you for your support!      *
     *                                                                       *
    ***************************************************************************


    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    >>>NOTE<<< The modification to the GPL is included to allow you to
    distribute a combined work that includes FreeRTOS without being obliged to
    provide the source code for proprietary components outside of the FreeRTOS
    kernel.  FreeRTOS is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
    or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public
    License and the FreeRTOS license exception along with FreeRTOS; if not it
    can be viewed here: http://www.freertos.org/a00114.html and also obtained
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!

    http://www.FreeRTOS.org - Documentation, latest information, license and
    contact details.

    http://www.SafeRTOS.com - A version that is certified for use in safety
    critical systems.

    http://www.OpenRTOS.com - Commercial support, development, porting,
    licensing and training services.
*/

/* Standard includes. */
#include "string.h"

#include "stm32f7xx_hal.h"

extern UART_HandleTypeDef huart1;

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

/* FreeRTOS+IO includes. */
//#include "FreeRTOS_IO.h"

/* Example includes. */
#include "FreeRTOS_CLI.h"
#include "CLI_uart_polling.h"

/* Dimensions the buffer into which input characters are placed. */
#define cmdMAX_INPUT_SIZE			50

/* Place holder for calls to ioctl that don't use the value parameter. */
#define cmdPARAMTER_NOT_USED		( ( void * ) 0 )

/* Block times of 50 and 500milliseconds, specified in ticks. */
#define cmd50ms						( ( void * ) ( 50UL / portTICK_RATE_MS ) )
#define cmd500ms					( ( void * ) ( 500UL / portTICK_RATE_MS ) )
/*-----------------------------------------------------------*/

 

const char logo_01[] = "                    ,     \\    /      ,           \n\r";
const char logo_02[] = "                   / \\    )\\__/(     / \\        \n\r";
const char logo_03[] = "                  /   \\  (_\\  /_)   /   \\       \n\r";
const char logo_04[] = "             ____/_____\\__\\@  @/___/_____\\____  \n\r";
const char logo_05[] = "            |             |\\../|              |   \n\r";
const char logo_06[] = "            |              \\VV/               |   \n\r";
const char logo_07[] = "            |         Pocket OZ V2.0    MMA21 |    \n\r";
const char logo_08[] = "            |_________________________________|    \n\r";
const char logo_09[] = "             |    /\\ /      \\       \\ /\\    |  \n\r";
const char logo_10[] = "             |  /   V        ))       V   \\  |    \n\r";
const char logo_11[] = "             |/     `       //        '     \\|    \n\r";
const char logo_12[] = "             `              V                '	   \n\r";
const char logo_13[] = "            	                                     \n\r";

/*
 * The task that implements the command console processing.
 */
static void prvUARTCommandConsoleTask(void const * pvParameters );

/*-----------------------------------------------------------*/

/* Holds the handle of the task that implements the UART command console. */
static xTaskHandle xCommandConsoleTask = NULL;

static const int8_t * const pcWelcomeMessage = ( int8_t * ) "\rPocketOZ CLI server started.\r\nType <Help> to view a list of registered commands.\r\n\r\n>";
static const int8_t * const pcNewLine = ( int8_t * ) "\r\n";
static const int8_t * const pcEndOfCommandOutputString = ( int8_t * ) "\r\n[Press ENTER to execute the previous command again]\r\n>";

/* The peripheral used by the command interpreter (and the vWriteString()
function). */
//static Peripheral_Descriptor_t xConsoleUART = NULL;

/*-----------------------------------------------------------*/
//osThreadId UARTCmdTaskHandle;

void vUARTCommandConsoleStart( void )
{
  //osThreadDef(UARTCmdTask, prvUARTCommandConsoleTask, configUART_COMMAND_CONSOLE_TASK_PRIORITY, 0, 128);
  //UARTCmdTaskHandle = osThreadCreate(osThread(UARTCmdTask), NULL);
  
	xTaskCreate( 	prvUARTCommandConsoleTask,				/* The task that implements the command console. */
					( const int8_t * const ) "UARTCmd",		/* Text name assigned to the task.  This is just to assist debugging.  The kernel does not use this name itself. */
					configUART_COMMAND_CONSOLE_STACK_SIZE,	/* The size of the stack allocated to the task. */
					NULL,									/* The parameter is not used, so NULL is passed. */
					configUART_COMMAND_CONSOLE_TASK_PRIORITY,/* The priority allocated to the task. */
					&xCommandConsoleTask );					/* Used to store the handle to the created task. */
}
/*-----------------------------------------------------------*/

static void prvUARTCommandConsoleTask(void const * pvParameters )
{
int8_t cRxedChar, cInputIndex = 0, *pcOutputString;
static int8_t cInputString[ cmdMAX_INPUT_SIZE ], cLastInputString[ cmdMAX_INPUT_SIZE ];
portBASE_TYPE xReturned;

	( void ) pvParameters;

	/* Obtain the address of the output buffer.  Note there is no mutual
	exclusion on this buffer as it is assumed only one command console
	interface will be used at any one time. */
	pcOutputString = FreeRTOS_CLIGetOutputBuffer();

        if(UART_CheckIdleState(&huart1) == HAL_OK)
        {
          HAL_UART_Transmit(&huart1, (uint8_t *) logo_01, strlen( ( char * ) logo_01 ) ,strlen( ( char * ) logo_01 ) );
          HAL_UART_Transmit(&huart1, (uint8_t *) logo_02, strlen( ( char * ) logo_02 ) ,strlen( ( char * ) logo_02 ) );
		      HAL_UART_Transmit(&huart1, (uint8_t *) logo_03, strlen( ( char * ) logo_03 ) ,strlen( ( char * ) logo_03 ) );
          HAL_UART_Transmit(&huart1, (uint8_t *) logo_04, strlen( ( char * ) logo_04 ) ,strlen( ( char * ) logo_04 ) );
          HAL_UART_Transmit(&huart1, (uint8_t *) logo_05, strlen( ( char * ) logo_05 ) ,strlen( ( char * ) logo_05 ) );
          HAL_UART_Transmit(&huart1, (uint8_t *) logo_06, strlen( ( char * ) logo_06 ) ,strlen( ( char * ) logo_06 ) );
          HAL_UART_Transmit(&huart1, (uint8_t *) logo_07, strlen( ( char * ) logo_07 ) ,strlen( ( char * ) logo_07 ) );
          HAL_UART_Transmit(&huart1, (uint8_t *) logo_08, strlen( ( char * ) logo_08 ) ,strlen( ( char * ) logo_08 ) );
          HAL_UART_Transmit(&huart1, (uint8_t *) logo_09, strlen( ( char * ) logo_09 ) ,strlen( ( char * ) logo_09 ) );
          HAL_UART_Transmit(&huart1, (uint8_t *) logo_10, strlen( ( char * ) logo_10 ) ,strlen( ( char * ) logo_10 ) );
          HAL_UART_Transmit(&huart1, (uint8_t *) logo_11, strlen( ( char * ) logo_11 ) ,strlen( ( char * ) logo_11 ) );
          HAL_UART_Transmit(&huart1, (uint8_t *) logo_12, strlen( ( char * ) logo_12 ) ,strlen( ( char * ) logo_12 ) );
          HAL_UART_Transmit(&huart1, (uint8_t *) logo_13, strlen( ( char * ) logo_13 ) ,strlen( ( char * ) logo_13 ) );					
					
					HAL_UART_Transmit(&huart1, (uint8_t *) pcWelcomeMessage, strlen( ( char * ) pcWelcomeMessage ) ,strlen( ( char * ) pcWelcomeMessage ) );
					
					
					
					
					

        }
        
	for( ;; )
	{
		/* Only interested in reading one character at a time. */
                HAL_UART_Receive(&huart1, (uint8_t *) &cRxedChar, sizeof( cRxedChar ), 0xFFFFFFFF );

		/* Echo the character back. */
                if(UART_CheckIdleState(&huart1) == HAL_OK)
                {
                  HAL_UART_Transmit(&huart1, (uint8_t *) &cRxedChar, sizeof( cRxedChar ), sizeof( cRxedChar ) );
                }
                
		if( cRxedChar == '\r' )
		{
			/* The input command string is complete.  Ensure the previous
			UART transmission has finished before sending any more data.
			This task will be held in the Blocked state while the Tx completes,
			if it has not already done so, so no CPU time will be wasted by
			polling. */
                      if(UART_CheckIdleState(&huart1) == HAL_OK)
                      {
                        HAL_UART_Transmit(&huart1, (uint8_t *) pcNewLine, strlen( ( char * ) pcNewLine ), strlen( ( char * ) pcNewLine ) );

                      }
			/* See if the command is empty, indicating that the last command is
			to be executed again. */
			if( cInputIndex == 0 )
			{
				strcpy( ( char * ) cInputString, ( char * ) cLastInputString );
			}

			/* Pass the received command to the command interpreter.  The
			command interpreter is called repeatedly until it returns
			pdFALSE as it might generate more than one string. */
			do
			{
				/* Once again, just check to ensure the UART has completed
				sending whatever it was sending last.  This task will be held
				in the Blocked state while the Tx completes, if it has not
				already done so, so no CPU time	is wasted polling. */
        if(UART_CheckIdleState(&huart1) == HAL_OK)
                                  xReturned = pdPASS;
                                
				if( xReturned == pdPASS )
				{
					/* Get the string to write to the UART from the command
					interpreter. */
					xReturned = FreeRTOS_CLIProcessCommand( cInputString, pcOutputString, configCOMMAND_INT_MAX_OUTPUT_SIZE );

					/* Write the generated string to the UART. */
           HAL_UART_Transmit(&huart1, (uint8_t *) pcOutputString, strlen( ( char * ) pcOutputString ), strlen( ( char * ) pcOutputString ) );
				}

			} while( xReturned != pdFALSE );

			/* All the strings generated by the input command have been sent.
			Clear the input	string ready to receive the next command.  Remember
			the command that was just processed first in case it is to be
			processed again. */
			strcpy( ( char * ) cLastInputString, ( char * ) cInputString );
			cInputIndex = 0;
			memset( cInputString, 0x00, cmdMAX_INPUT_SIZE );

			/* Ensure the last string to be transmitted has completed. */
                      if(UART_CheckIdleState(&huart1) == HAL_OK)
                      {
                        HAL_UART_Transmit(&huart1, (uint8_t *) pcEndOfCommandOutputString, strlen( ( char * ) pcEndOfCommandOutputString ), strlen( ( char * ) pcEndOfCommandOutputString ) );

                      }
		}
		else
		{
			if( cRxedChar == '\r' )
			{
				/* Ignore the character. */
			}
			else if( cRxedChar == '\b' )
			{
				/* Backspace was pressed.  Erase the last character in the
				string - if any. */
				if( cInputIndex > 0 )
				{
					cInputIndex--;
					cInputString[ cInputIndex ] = '\0';
				}
			}
			else
			{
				/* A character was entered.  Add it to the string
				entered so far.  When a \n is entered the complete
				string will be passed to the command interpreter. */
				if( ( cRxedChar >= ' ' ) && ( cRxedChar <= '~' ) )
				{
					if( cInputIndex < cmdMAX_INPUT_SIZE )
					{
						cInputString[ cInputIndex ] = cRxedChar;
						cInputIndex++;
					}
				}
			}
		}
	}
}
/*-----------------------------------------------------------*/

void vOutputString( const uint8_t * const pucMessage )
{
  
    if(UART_CheckIdleState(&huart1) == HAL_OK)
    {
      HAL_UART_Transmit(&huart1, (uint8_t *) pucMessage, strlen( ( char * ) pucMessage ), strlen( ( char * ) pucMessage ) );

    }
}
/*-----------------------------------------------------------*/


