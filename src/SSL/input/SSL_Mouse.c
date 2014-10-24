/*-------------------------------------------------------------------------*/
/**
   @file    SSL_Mouse.c
   @author  P. Batty
   @brief   Implements a easier way to get information about the mouse.

   This module implements a easier way to get the mouse states and whether is
    is inside an area
*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "SSL_Mouse.h"
#include "../../../lib/SDL2/SDL.h"


/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
|  @brief    Gets whether the a point is inside an area
|  @param    x         x Location of the area
|  @param    y         y Location of the area
|  @param    w         width of the area
|  @param    h         height of the area
|  @param    event     the SDL_Event queue to use
|  @return true if the point is inside the area else false
|
|  Gets whether a point is in the area
|
\-----------------------------------------------------------------------------*/
static int in_area(int x1, int y1, int x2, int y2, int w2, int h2) {
	return ( x1 > x2 ) && ( x1 < x2 + w2 ) && ( y1 > y2 ) && ( y1 < y2 + h2 );
}


/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
|  @brief    Gets whether the left button is down
|  @return true if the left mouse is down else false
|
|  Gets whether the left button is down
|
\-----------------------------------------------------------------------------*/
int SSL_Mouse_Left_Down() {
	return (SDL_GetMouseState(NULL,NULL) & SDL_BUTTON(SDL_BUTTON_LEFT));
}


/*!--------------------------------------------------------------------------
|  @brief    Gets whether the right button is down
|  @return true if the right mouse is down else false
|
|  Gets whether the right button is down
|
\-----------------------------------------------------------------------------*/
int SSL_Mouse_Right_Down () {
	return (SDL_GetMouseState(NULL,NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT));
}


/*!--------------------------------------------------------------------------
|  @brief    Gets whether the right middle is down
|  @return true if the middle mouse is down else false
|
|  Gets whether the middle button is down
|
\-----------------------------------------------------------------------------*/
int SSL_Mouse_Middle_Down () {
	return (SDL_GetMouseState(NULL,NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE));
}


/*!--------------------------------------------------------------------------
|  @brief    Gets whether the mouse is in an area
|  @param    x         x Location of the area
|  @param    y         y Location of the area
|  @param    w         width of the area
|  @param    h         height of the area
|  @param    event     the SDL_Event queue to use
|  @return true if the mouse is hovering inside the area else false
|
|  Gets whether the mouse is in the area
|
\-----------------------------------------------------------------------------*/
int SSL_Mouse_Hover_In_Area(int x, int y, int w, int h, SDL_Event event) {

	int state = 0;

	/* get mouse x and y */
	int mx = event.motion.x;
	int my = event.motion.y;

	/* check if it is in the area */
	if (in_area(mx, my, x, y, w, h)) {
		state = 1;
	}

	/* return */
	return state;
}


/*!--------------------------------------------------------------------------
|  @brief    Gets whether the left mouse button is down is in an area
|  @param    x         x Location of the area
|  @param    y         y Location of the area
|  @param    w         width of the area
|  @param    h         height of the area
|  @param    event     the SDL_Event queue to use
|  @return true if the left mouse button is down inside the area else false
|
|  Gets whether the left mouse button is down in the area
|
\-----------------------------------------------------------------------------*/
int SSL_Mouse_Left_Down_In_Area(int x, int y, int w, int h, SDL_Event event) {

	int state = 0;

	/* get mouse x and y */
	int ex = event.button.x;
	int ey = event.button.y;

	/* if the left button was clicked */
	/* check if it is in the area */
	if (SDL_GetMouseState(NULL,NULL) & SDL_BUTTON(SDL_BUTTON_LEFT) ) {
		if (in_area(ex, ey, x, y, w, h)) {
			event.button.button = 0;
			state = 1;
		}
	}

	/* return */
	return state;
}


/*!--------------------------------------------------------------------------
|  @brief    Gets whether the right mouse button is down is in an area
|  @param    x         x Location of the area
|  @param    y         y Location of the area
|  @param    w         width of the area
|  @param    h         height of the area
|  @param    event     the SDL_Event queue to use
|  @return true if the right mouse button is down inside the area else false
|
|  Gets whether the right mouse button is down in the area
|
\-----------------------------------------------------------------------------*/
int SSL_Mouse_Right_Down_In_Area(int x, int y, int w, int h, SDL_Event event) {

	int state = 0;

	/* get mouse x and y */
	int ex = event.button.x;
	int ey = event.button.y;

	/* if the left button was clicked */
	/* check if it is in the area */
	if (SDL_GetMouseState(NULL,NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT) ) {
		if (in_area(ex, ey, x, y, w, h)) {
			event.button.button = 0;
			state = 1;
		}
	}

	/* return */
	return state;
}
