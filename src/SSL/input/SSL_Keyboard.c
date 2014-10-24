/*-------------------------------------------------------------------------*/
/**
   @file    SSL_Keyboard.h
   @author  P. Batty
   @brief   Implements a easier way to get information about the keyboard.

   This module implements a easier way to get the keyboard key states.
*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "SSL_Keyboard.h"
#include "../misc/SSL_Keys.h"

#include "../../../lib/SDL2/SDL.h"


/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
|  @brief    Gets whether the key is down
|  @param    key         SDL_Keycode of the key
|  @return true if the key is pressed else false
|
|  Gets whether the key is pressed
|
\-----------------------------------------------------------------------------*/
int SSL_Keybord_Key_Down(SDL_Keycode key) {
	SDL_PumpEvents();
	const Uint8 *keystates =  SDL_GetKeyboardState( NULL );
	return keystates[key];
}


/*!--------------------------------------------------------------------------
|  @brief    Gets whether the key is down
|  @param    key         string version of the key
|  @return true if the key is pressed else false
|
|  Gets whether the key is pressed
|
\-----------------------------------------------------------------------------*/
int SSL_Keybord_Keyname_Down(char *key) {
	SDL_PumpEvents();
	const Uint8 *keystates =  SDL_GetKeyboardState( NULL );
	return keystates[GetCode(key)];
}
