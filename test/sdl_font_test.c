#include "tests.h"
#include "../src/SSL/graphics/SSL_window.h"
#include "../src/SSL/graphics/SSL_Font.h"
#include "../src/SSL/misc/SSL_Color.h"
#include <stdio.h>

/**
 * Creates a spinning white font waits for user to exit
 */
void sdl_font_test() {
	SDL_Init(SDL_INIT_EVERYTHING);

	SSL_Window *window = SSL_Window_Create("This is the Sdl font test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0,0, 0);
	SSL_Font *font = SSL_Font_Load("../extras/resources/debug.ttf", 100);

	int angle = 0;

	SDL_Event event;
		int running = 1;

		while(running) {
			SDL_PumpEvents();
			SDL_RenderPresent(window->renderer);
			SDL_RenderClear( window->renderer );

			SSL_Font_Draw(200, 200, angle, SDL_FLIP_NONE, "Exit to Continue", font, *SSL_Color_Create(255,255,255,0), window);
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
