#include "tests.h"
#include "../src/game_api/graphics/sdl_window.h"
#include "../src/game_api/graphics/sdl_image_load.h"
#include "../src/game_api/graphics/sdl_image_draw.h"
#include "../src/game_api/graphics/sdl_font.h"
#include "../src/game_api/misc/sdl_color.h"
#include "../src/game_api/input/mouse.h"
#include <stdio.h>

/**
 *  Creates a window with an image untill user closes it
 */
void mouse_input_test() {
	SDL_Init(SDL_INIT_EVERYTHING);

	Window *window = window_create("This is the Sdl image test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
	Image *image = image_load("../extras/resources/test_image.png", 100, 100, window);
	Font *font = font_load("../extras/resources/debug.ttf", 55);

	int frame = 1;

	SDL_Event event;
	int running = 1;

	while(running) {
		SDL_PumpEvents();
		SDL_RenderPresent(window->renderer);
		SDL_RenderClear( window->renderer );

		font_draw(0, 0, 0, SDL_FLIP_NONE, "Hover, Left and Right click on the image", font, *color_create(255,255,255,0), window);
		image_draw(image, 100, 100, 0, frame, SDL_FLIP_NONE, window);

		if (mouse_hover_in_area(100, 100, 100, 100, event)) {
			frame = 2;
		} else {
			frame = 1;
		}

		if (mouse_left_click_in_area(100, 100, 100, 100, event)) {
			frame = 3;
		}
		if (mouse_right_click_in_area(100, 100, 100, 100, event)) {
			frame = 4;
		}

		while (SDL_PollEvent(&event))
		 {
		    if (event.type == SDL_QUIT) {
		    	running = 0;
		    	break;
		    }
		 }
	}

    SDL_Quit();

	printf("\n Sdl mouse input test passed...\n");
}

