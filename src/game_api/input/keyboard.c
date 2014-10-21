#include "keyboard.h"
#include "../../../lib/SDL2/SDL.h"

/**************************
 *
 *  gets whether a key is down or not
 *
 *  @param key - key to get
 *
 *************************/
int keybord_key_down(SDL_Keycode key) {
	SDL_PumpEvents();
	const Uint8 *keystates =  SDL_GetKeyboardState( NULL );
	return keystates[key];
}
