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

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Standard includes. */
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* FreeRTOS+CLI includes. */
#include "FreeRTOS_CLI.h"
#include "main_header.h"

int32_t CLI_cmd = 0;
/*
 * Implements the reset command.
 */
static portBASE_TYPE prvResetCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString );
static portBASE_TYPE prvExecUICommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString );

/* Structure that defines the  command line command */
static const CLI_Command_Definition_t prvResetCommandDefinition =
{
	( const int8_t * const ) "reset", /* The command string to type. */
	( const int8_t * const ) "reset:\r\n reset the application\r\n\r\n",
	prvResetCommand, /* The function to run. */
	0 /* No parameters are expected. */
};

/* Structure that defines the  command line command */
static const CLI_Command_Definition_t prvExecUICommandDefinition =
{
	( const int8_t * const ) "press", /* The command string to type. */
	( const int8_t * const ) "press <button>:\r\n Execute button press <item>\r\n\r\n",
	prvExecUICommand, /* The function to run. */
	1 /* No parameters are expected. */
};

/*-----------------------------------------------------------*/

void vRegisterCLICommands( void )
{
	/* Register all the command line commands defined immediately above. */
	FreeRTOS_CLIRegisterCommand( &prvResetCommandDefinition);
	FreeRTOS_CLIRegisterCommand( &prvExecUICommandDefinition);	
}
/*-----------------------------------------------------------*/

static portBASE_TYPE prvResetCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString )
{
  int8_t *pcParameterString;
  portBASE_TYPE xParameterStringLength;
  int32_t lParameterValue;
	
  ( void ) pcCommandString;
  ( void ) xWriteBufferLen;
	

	
  pcParameterString = ( int8_t * ) FreeRTOS_CLIGetParameter
								(
									pcCommandString,		/* The command string itself. */
									1,						/* Return the first parameter. */
									&xParameterStringLength	/* Store the parameter string length. */
								);

	/* Turn the parameter into a number. */
	lParameterValue = ( int32_t ) atol( ( const char * ) pcParameterString );
	strcpy( (char *)pcWriteBuffer, "System reset : Done \r\n");
	configASSERT( pcWriteBuffer );
	
	HAL_NVIC_SystemReset();
}

/*-----------------------------------------------------------*/

static portBASE_TYPE prvExecUICommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString )
{
  int8_t *pcParameterString;
  portBASE_TYPE xParameterStringLength, xReturn;
  int32_t lParameterValue;
	
  ( void ) pcCommandString;
  ( void ) xWriteBufferLen;
	


	
  pcParameterString = ( int8_t * ) FreeRTOS_CLIGetParameter
								(
									pcCommandString,		/* The command string itself. */
									1,						/* Return the first parameter. */
									&xParameterStringLength	/* Store the parameter string length. */
								);

	/* Turn the parameter into a number. */
	lParameterValue = ( int32_t ) atol( ( const char * ) pcParameterString );
	
	if(strcmp((char *)pcParameterString, "sigtype") == 0)
	{
			CLI_cmd = PRESS_SIGTYPE;
		  strcpy( (char *)pcWriteBuffer, "Signal type switched \r\n");
	}
	
	else if(strcmp((char *)pcParameterString, "sigfreq") == 0)
	{
			CLI_cmd = PRESS_SIGFREQ;
		  strcpy( (char *)pcWriteBuffer, "Signal freq switched \r\n");
	}	
	
	else if(strcmp((char *)pcParameterString, "save") == 0)
	{
			CLI_cmd = PRESS_SAVE;
		  strcpy( (char *)pcWriteBuffer, "settings saved \r\n");		
	}
	
	else if(strcmp((char *)pcParameterString, "channel") == 0)
	{
			CLI_cmd = PRESS_SWITCH_CHANNEL;
		  strcpy( (char *)pcWriteBuffer, "Channel switched \r\n");		
	}	
	
	
	else if(strcmp((char *)pcParameterString, "timeup") == 0)
	{
			  CLI_cmd = PRESS_TIME_UP;
		    strcpy( (char *)pcWriteBuffer, "time up \r\n");		
	}
			
	
	else if(strcmp((char *)pcParameterString, "timedown") == 0)
	{
			  CLI_cmd = PRESS_TIME_DOWN;
		    strcpy( (char *)pcWriteBuffer, "time down \r\n");			
	}	
	else if(strcmp((char *)pcParameterString, "voltup") == 0)
	{
			  CLI_cmd = PRESS_VOLT_UP;
		    strcpy( (char *)pcWriteBuffer, "volt up \r\n");		
	}
			
	
	else if(strcmp((char *)pcParameterString, "voltdown") == 0)
	{
			  CLI_cmd = PRESS_VOLT_DOWN;
		    strcpy( (char *)pcWriteBuffer, "volt down \r\n");			
	}	
	else if(strcmp((char *)pcParameterString, "menu") == 0)
  {
			  CLI_cmd = PRESS_MENU;
		    strcpy( (char *)pcWriteBuffer, "settings menu toggled \r\n");			
  }
	else
	{
		strcpy( (char *)pcWriteBuffer, "Invalid command! \r\n");		
	}

	
	
	
	
	configASSERT( pcWriteBuffer );
  return pdFALSE;
}

int32_t Get_CLI_UX_Commands(void)
{
  int32_t cmd;
	cmd = CLI_cmd;
	CLI_cmd = 0;
	return cmd;
}
/*-----------------------------------------------------------*/

