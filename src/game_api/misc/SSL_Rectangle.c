/*-------------------------------------------------------------------------*/
/**
   @file    SSL_Rectangle.c
   @author  P. Batty
   @brief   Simple way to create SDL_Rect objects

   This module implements a simple way to create SDL_Rect objects.

*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "../../../lib/SDL2/SDL.h"

#include "SSL_Rectangle.h"
#include "SSL_Logger.h"

#include <stdlib.h>


/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
|  @brief	 Creates a SDL_Rect Object
|  @param    x			  X position of the object.
|  @param    y			  y position of the object.
|  @param    w			  width of the object.
|  @param    h			  height of the object.
|  @return 	 A SDL_Rect object or 0 if unsuccessful
|
|   Creates and returns a SDL_Rect Object.
|
|
\-----------------------------------------------------------------------------*/
SDL_Rect *SSL_Rectangle_Create(double x, double y, double w, double h) {

	/* allocate memory */
	SDL_Rect *rect = malloc(sizeof(SDL_Rect));

	/* if we could not allocate memory
	 * Log the error an return 0.
	 */
	if (!rect) {
		SSL_Log_Write("Failed to allocate memory, SSL_Rectangle");
		return 0;
	}

	/* else fill in the details */
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;

	/* return the object */
	return rect;
}
