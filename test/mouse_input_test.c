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
	printf("\n Starting SSL Mouse Input Test ...\n");
	SDL_Init(SDL_INIT_EVERYTHING);

	SSL_Window *window = SSL_Window_Create("This is the Sdl image test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 200, 200, 0, 0, 0);
	SSL_Image *image = SSL_Image_Load("../extras/resources/test_image.png", 100, 100, window);

	int frame = 1;

	SDL_Event event;
	int running = 1;

	printf("\n ************************** \n ");
	printf("\n *  Can You See An Image? * \n ");
	printf("\n *  Hover, Left and Right * \n ");
	printf("\n *  click on the image    * \n ");
	printf("\n *  does it change?       * \n ");
	printf("\n ************************** \n ");

	while(running) {
		SDL_PumpEvents();
		SDL_RenderPresent(window->renderer);
		SDL_RenderClear( window->renderer );

		SSL_Image_Draw(image, 50, 50, 0, frame, SDL_FLIP_NONE, window);

		if (SSL_Mouse_Hover_In_Area(50, 50, 100, 100, event)) {
			frame = 2;
		} else {
			frame = 1;
		}

		if (SSL_Mouse_Left_Down_In_Area(50, 50, 100, 100, event)) {
			frame = 3;
		}
		if (SSL_Mouse_Right_Down_In_Area(50, 50, 100, 100, event)) {
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

	SSL_Window_Destroy(window);
	SSL_Image_Destroy(image);

    SDL_Quit();

	printf(" SSL Mouse Input Test passed...\n");
}

