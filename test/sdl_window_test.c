#include "tests.h"
#include "../src/SSL/graphics/SSL_Window.h"
#include <stdio.h>
#include <assert.h>

/* create and destroy windows */
static void test1() {
	SSL_Window *window[50];

	int i = 0;
	for (i = 0; i < 50; i ++) {
		window[i] = SSL_Window_Create("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, i, i, 0, 0, 0);
		assert(window[i] != NULL);
		SSL_Window_Set_Icon(window[i], "test.png");
	}

	for (i = 0; i < 50; i ++) {
		SSL_Window_Destroy(window[i]);
	}
}

/*
 * Creates and destroys a window
 */
void sdl_window_test() {
	printf("\n Starting SSL Window Test ...\n");

	SDL_Init(SDL_INIT_EVERYTHING);

	test1();

    SDL_Quit();

	printf(" SSL Window test passed...\n");
}
