/*-------------------------------------------------------------------------*/
/**
   @file    SSL_Logger.c
   @author  P. Batty
   @brief   Implements a Logging function.

   This module implements a simple logging function that will
   write a message to a file.
*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/
#include "SSL_Logger.h"

#include <time.h>
#include <stdio.h>
#include <stdarg.h>


/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/

int LOGGIN = 1;									/**< are we logging  */
static char *file_path = "../extras/log.txt";	/**< path to the file */


/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
|  @brief	 Writes a message to a file
|  @param    text		  Text to write.
|  @param    ...          printf arguments
|  @return 	 void
|
|  Writes a message to a file, in the style of printf.
|
|
\-----------------------------------------------------------------------------*/
void SSL_Log_Write(char *text, ...) {

	/* if we are logging */
	if (LOGGIN) {

		/* open the file */
		FILE *f = fopen(file_path, "ab");

		/* if we could not open the file return */
		if (f == NULL) {
			return;
		}

		/* get the current time */
		time_t current_time;
		char* c_time_string;

		/* get the argument list */
		va_list arg;

		/* calculate the current time */
		current_time = time(NULL);
		c_time_string = ctime(&current_time);

		/* print out the time */
		fprintf(f, "%s: ", c_time_string);

		/* print out the message */
		va_start(arg, text);
		vfprintf(f, text, arg);
		va_end(arg);

		/* print a new line */
		fprintf(f, "\r\n");

		/* close the file and return */
		fclose(f);
	}
}
