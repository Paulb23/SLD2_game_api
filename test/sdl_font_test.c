#include "tests.h"
#include "../src/SSL/graphics/SSL_window.h"
#include "../src/SSL/graphics/SSL_Font.h"
#include "../src/SSL/misc/SSL_Color.h"
#include <stdio.h>
#include <assert.h>

/* loading and destroying images */
static void test1() {

	SSL_Font *fonts[100];

	int i = 0;
	for(i = 0; i < 100; i++) {
		fonts[i] = SSL_Font_Load("../extras/resources/debug.ttf", i);
		assert(fonts[i] != NULL);
	}

	for(i = 0; i < 100; i++) {
		SSL_Font_Destroy(fonts[i]);
	}

}

/* check user can see an image */
static void test2() {
	SSL_Window *window = SSL_Window_Create("This is the Sdl image test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 200, 200, 0,0,0);
	assert(window != NULL);

	SSL_Font *font = SSL_Font_Load("../extras/resources/debug.ttf", 100);

	int angle = 0;

	SDL_Event event;
	int running = 1;

	printf("\n ************************** \n ");
	printf("\n * Can You See some text? * \n ");
	printf("\n ************************** \n ");

	while(running) {
		SDL_PumpEvents();
		SDL_RenderPresent(window->renderer);
		SDL_RenderClear( window->renderer );

		SSL_Font_Draw(40, 40, angle, SDL_FLIP_NONE, "Text", font, *SSL_Color_Create(255,255,255,0), window);
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

	SSL_Font_Destroy(font);
	SSL_Window_Destroy(window);
}

/**
 * Creates a spinning white font waits for user to exit
 */
void sdl_font_test() {
	printf("\n Starting SSL Font Test ...\n");

	SDL_Init(SDL_INIT_EVERYTHING);

	test1();
	test2();

	SDL_Quit();

 printf(" SSL Font Test Passed...\n");
}
