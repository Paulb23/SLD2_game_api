#include "tests.h"
#include "../src/game_api/graphics/SSL_window.h"
#include "../src/game_api/graphics/sdl_font.h"
#include "../src/game_api/misc/sdl_color.h"
#include <stdio.h>

/**
 * Creates a spinning white font waits for user to exit
 */
void sdl_font_test() {
	SDL_Init(SDL_INIT_EVERYTHING);

	SSL_Window *window = SSL_Window_Create("This is the Sdl font test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0,0, 0);
	Font *font = font_load("../extras/resources/debug.ttf", 100);

	int angle = 0;

	SDL_Event event;
		int running = 1;

		while(running) {
			SDL_PumpEvents();
			SDL_RenderPresent(window->renderer);
			SDL_RenderClear( window->renderer );

			font_draw(200, 200, angle, SDL_FLIP_NONE, "Exit to Continue", font, *color_create(255,255,255,0), window);
			angle += 20;
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

 printf("\n Sdl font test passed...\n");
}
