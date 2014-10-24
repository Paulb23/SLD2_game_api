#include "tests.h"
#include "../src/SSL/graphics/SSL_Window.h"
#include <stdio.h>


/*
 * Creates and destroys a window
 */
void sdl_window_test() {
	SDL_Init(SDL_INIT_EVERYTHING);

	SSL_Window *window = SSL_Window_Create("This is the Sdl window test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600,0,0, 0);
	SSL_Window_Set_Icon(window, "sahdhsa.png");

    SDL_Quit();

	printf("\n Sdl Window test passed...\n");
}
