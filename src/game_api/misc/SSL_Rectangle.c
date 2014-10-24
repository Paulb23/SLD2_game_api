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
|  @return 	 A SDL_Rect object
|
|   Creates and returns a SDL_Rect Object.
|
|
\-----------------------------------------------------------------------------*/
SDL_Rect *SSL_Rectangle_Create(double x, double y, double w, double h) {
	SDL_Rect *rect = malloc(sizeof(SDL_Rect));
		rect->x = x;
		rect->y = y;
		rect->w = w;
		rect->h = h;
	return rect;
}
