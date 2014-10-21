#include "tests.h"
#include "../src/game_api/graphics/sdl_window.h"
#include "../src/game_api/graphics/sdl_image_load.h"
#include "../src/game_api/graphics/sdl_image_draw.h"
#include "../src/game_api/graphics/sdl_font.h"
#include <stdio.h>

/**
 *  Creates a window with a animated images until the user closes the window
 */
void sdl_image_test() {
	SDL_Init(SDL_INIT_EVERYTHING);

	Window *window = window_create("This is the Sdl image test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
	Image *image = image_load("../extras/resources/test_image.png", 100, 100, window);

	int frame = 2;
	int angle = 0;

	SDL_Event event;
	int running = 1;

	while(running) {
		SDL_PumpEvents();
		SDL_RenderPresent(window->renderer);
		SDL_RenderClear( window->renderer );

		image_draw(image, 100, 100, angle, frame, SDL_FLIP_NONE, window);
		frame++;
		angle += 20;
		if (frame == image->amount_of_frames + 1) frame = 0;
		if (angle == 360) angle = 0;

		while (SDL_PollEvent(&event))
		 {
		    if (event.type == SDL_QUIT) {
		    	running = 0;
		    	break;
		    }
		 }

		SDL_Delay(100);
	}

    SDL_Quit();

	printf("\n Sdl image test passed...\n");
}
