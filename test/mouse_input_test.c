#include "tests.h"
#include "../src/SSL/graphics/SSL_window.h"
#include "../src/SSL/graphics/SSL_Image.h"
#include "../src/SSL/graphics/SSL_Font.h"
#include "../src/SSL/misc/SSL_Color.h"
#include "../src/SSL/input/SSL_Mouse.h"
#include <stdio.h>

/**
 *  Creates a window with an image untill user closes it
 */
void mouse_input_test() {
	SDL_Init(SDL_INIT_EVERYTHING);

	SSL_Window *window = SSL_Window_Create("This is the Sdl image test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0, 0, 0);
	SSL_Image *image = SSL_Image_Load("../extras/resources/test_image.png", 100, 100, window);
	SSL_Font *font = SSL_Font_Load("../extras/resources/debug.ttf", 55);

	int frame = 1;

	SDL_Event event;
	int running = 1;

	while(running) {
		SDL_PumpEvents();
		SDL_RenderPresent(window->renderer);
		SDL_RenderClear( window->renderer );

		SSL_Font_Draw(0, 0, 0, SDL_FLIP_NONE, "Hover, Left and Right click on the image", font, *SSL_Color_Create(255,255,255,0), window);
		SSL_Image_Draw(image, 100, 100, 0, frame, SDL_FLIP_NONE, window);

		if (SSL_Mouse_Hover_In_Area(100, 100, 100, 100, event)) {
			frame = 2;
		} else {
			frame = 1;
		}

		if (SSL_Mouse_Left_Down_In_Area(100, 100, 100, 100, event)) {
			frame = 3;
		}
		if (SSL_Mouse_Right_Down_In_Area(100, 100, 100, 100, event)) {
			frame = 4;
		}

		if (SSL_Mouse_Left_Clicked_In_Area(100,100,100,100,event)) {
			printf("Clicked");
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

