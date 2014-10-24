/*-------------------------------------------------------------------------*/
/**
   @file    SSL_Color.h
   @author  P. Batty
   @brief   Simple way to create SDL_Color objects

   This module implements a simple way to create SDL_Color objects.

*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "../../../lib/SDL2/SDL.h"

#include "SSL_Color.h"
#include "SSL_Logger.h"

#include <stdlib.h>

/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief	 Creates a SDL_Color Object
  @param    r			  Amount of red 0 - 255.
  @param    g			  Amount of green 0 - 255.
  @param    b			  Amount of blue 0 - 255.
  @param    a			  Amount of alpha
  @return 	 A SDL_Color object or 0 if unsuccessful

   Creates and returns a SDL_Color Object.


\-----------------------------------------------------------------------------*/
SDL_Color *SSL_Color_Create(int r, int g, int b, int a) {

	/* Allocate memory */
	SDL_Color *color = malloc(sizeof(SDL_Color));

	/* if we could not allocate memory
	 * Log the error an return 0.
	 */
	if (!color) {
		SSL_Log_Write("Failed to allocate memory, SSL_Rectangle");
		return 0;
	}

	/* else fill in the details */
	color->r = r;
	color->g = g;
	color->b = b;
	color->a = a;

	/* return the object  */
	return color;
}
