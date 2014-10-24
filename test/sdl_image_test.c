#include "tests.h"
#include "../src/SSL/graphics/SSL_window.h"
#include "../src/SSL/graphics/SSL_Image.h"
#include "../src/SSL/graphics/SSL_Font.h"
#include <stdio.h>

/**
 *  Creates a window with a animated images until the user closes the window
 */
void sdl_image_test() {
	SDL_Init(SDL_INIT_EVERYTHING);

	SSL_Window *window = SSL_Window_Create("This is the Sdl image test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0,0,0);
	SSL_Image *image = SSL_Image_Load("../extras/resources/test_image.png", 100, 100, window);

	int frame = 2;
	int angle = 0;

	SDL_Event event;
	int running = 1;

	while(running) {
		SDL_PumpEvents();
		SDL_RenderPresent(window->renderer);
		SDL_RenderClear( window->renderer );

		SSL_Image_Draw(image, 100, 100, angle, frame, SDL_FLIP_NONE, window);
		frame++;
		angle += 20;
		if (frame == image->amount_of_frames + 1) frame = 1;
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
