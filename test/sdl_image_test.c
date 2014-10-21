#include "tests.h"
#include "../src/game_api/graphics/sdl_window.h"
#include "../src/game_api/graphics/sdl_image_load.h"
#include <stdio.h>

void sdl_image_test() {
	SDL_Init(SDL_INIT_EVERYTHING);

	Window *window = window_create("This is the Sdl image test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
	Image *image = image_load("../extras/resources/test_image.png", 100, 100, window);

    SDL_Quit();

	printf("\n Sdl image test passed...\n");
}
