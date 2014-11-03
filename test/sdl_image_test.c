#include "tests.h"
#include "../src/SSL/graphics/SSL_window.h"
#include "../src/SSL/graphics/SSL_Image.h"
#include "../src/SSL/graphics/SSL_Font.h"
#include <stdio.h>
#include <assert.h>

/* loading and destroying images */
static void test1() {
	SSL_Window *window = SSL_Window_Create("This is the Sdl image test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1, 1, 0,0,0);
	assert(window != NULL);

	SSL_Image *images[100];

	int i = 0;
	for(i = 0; i < 100; i++) {
		images[i] = SSL_Image_Load("../extras/resources/test_image.png", 100, 100, window);
		assert(images[i] != NULL);
	}

	for(i = 0; i < 100; i++) {
		SSL_Image_Destroy(images[i]);
	}

	SSL_Window_Destroy(window);
}

/* check user can see an image */
static void test2() {
	SSL_Window *window = SSL_Window_Create("This is the Sdl image test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 200, 200, 0,0,0);
	assert(window != NULL);

	SSL_Image *image = SSL_Image_Load("../extras/resources/test_image.png", 100, 100, window);

	int frame = 2;
	int angle = 0;

	SDL_Event event;
	int running = 1;

	printf("\n ************************** \n ");
	printf("\n *  Can You See An Image? * \n ");
	printf("\n ************************** \n ");

	while(running) {
		SDL_PumpEvents();
		SDL_RenderPresent(window->renderer);
		SDL_RenderClear( window->renderer );

		SSL_Image_Draw(image, 50, 50, angle, frame, SDL_FLIP_NONE, window);
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

	SSL_Image_Destroy(image);
	SSL_Window_Destroy(window);
}

/**
 *  Creates a window with a animated images until the user closes the window
 */
void sdl_image_test() {
	printf("\n Starting SSL Image Test ...\n");

	SDL_Init(SDL_INIT_EVERYTHING);

	test1();
	test2();

    SDL_Quit();

	printf(" SSL image test passed...\n");
}
