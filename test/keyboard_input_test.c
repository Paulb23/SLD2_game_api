#include "tests.h"
#include "../src/game_api/graphics/sdl_window.h"
#include "../src/game_api/graphics/sdl_image_load.h"
#include "../src/game_api/graphics/sdl_image_draw.h"
#include "../src/game_api/graphics/sdl_font.h"
#include "../src/game_api/misc/sdl_color.h"
#include "../src/game_api/input/keyboard.h"
#include <stdio.h>

/**
 *  Creates a window with a animated images until the user closes the window
 */
void keybord_input_test() {
	SDL_Init(SDL_INIT_EVERYTHING);

	Window *window = window_create("This is the Sdl image test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
	Image *image = image_load("../extras/resources/test_image.png", 10, 10, window);

	Font *font = font_load("../extras/resources/debug.ttf", 65);

	SDL_Event event;
	int running = 1;

	int x = 100;
	int y = 100;
	int speed = 10;

	while(running) {
		SDL_PumpEvents();
		SDL_RenderPresent(window->renderer);
		SDL_RenderClear( window->renderer );

		font_draw(0, 0, 0, SDL_FLIP_NONE, "Use the arrow or wasd keys to move", font, *color_create(255,255,255,0), window);
		image_draw(image, x, y, 0, 1, SDL_FLIP_NONE, window);

		if (keybord_key_down(SDL_SCANCODE_LEFT) || keybord_key_down(SDL_SCANCODE_A)) {
			x-=speed;
		}
		if (keybord_key_down(SDL_SCANCODE_RIGHT) || keybord_key_down(SDL_SCANCODE_D)) {
			x+=speed;
		}
		if (keybord_key_down(SDL_SCANCODE_UP) || keybord_key_down(SDL_SCANCODE_W)) {
			y-=speed;
		}
		if (keybord_key_down(SDL_SCANCODE_DOWN) || keybord_key_down(SDL_SCANCODE_S)) {
			y+=speed;
		}

		if (x < 0) {
			x = 800;
		}
		if (x > 800) {
			x = 0;
		}
		if (y < 0) {
			y = 600;
		}
		if (y > 600) {
			y = 0;
		}

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

	printf("\n SDL keyboard input test passed...\n");
}
