/*-------------------------------------------------------------------------*/
/**
   @file    SSL_Keyboard.h
   @author  P. Batty
   @brief   Implements a easier way to get information about the keyboard.

   This module implements a easier way to get the keyboard key states.
*/
/*--------------------------------------------------------------------------*/

#ifndef KEYBOARD_H_
#define KEYBOARD_H_


/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "../../../lib/SDL2/SDL.h"


/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
|  @brief    Gets whether the key is down
|  @param    key         SDL_Keycode of the key
|  @return true if the key is pressed else false
|
|  Gets whether the key is pressed
|
\-----------------------------------------------------------------------------*/
int SSL_Keybord_Key_Down(SDL_Keycode key);


/*!--------------------------------------------------------------------------
|  @brief    Gets whether the key is down
|  @param    key         string version of the key
|  @return true if the key is pressed else false
|
|  Gets whether the key is pressed
|
\-----------------------------------------------------------------------------*/
int SSL_Keybord_Keyname_Down(char *key);

#endif /* KEYBOARD_H_ */
