#include "tests.h"
#include "../src/game_api/graphics/sdl_window.h"
#include <stdio.h>


/*
 * Creates and destroys a window
 */
void sdl_window_test() {
	SDL_Init(SDL_INIT_EVERYTHING);

	Window *window = window_create("This is the Sdl window test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
	window_set_icon(window, "sahdhsa.png");

    SDL_Quit();

	printf("\n Sdl Window test passed...\n");
}
