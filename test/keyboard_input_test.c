#include "tests.h"
#include "../src/SSL/graphics/SSL_Window.h"
#include "../src/SSL/graphics/SSL_Image.h"
#include "../src/SSL/graphics/SSL_Font.h"
#include "../src/SSL/misc/SSL_Color.h"
#include "../src/SSL/input/SSL_Keyboard.h"
#include "../lib/SDL2/SDL.h"
#include <stdio.h>

/**
 *  Creates a window with a animated images until the user closes the window
 */
void keybord_input_test() {
	printf("\n Starting SSL keyboard input test...\n");

	SDL_Init(SDL_INIT_EVERYTHING);

	SSL_Window *window = SSL_Window_Create("This is the Sdl keyboard input test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 200, 200, 0, 0, 0);
	SSL_Image *image = SSL_Image_Load("../extras/resources/test_image.png", 10, 10, window);

	SDL_Event event;
	int running = 1;

	int x = 100;
	int y = 100;
	int speed = 10;

	printf("\n ************************** \n ");
	printf("\n *  Can You Move the box? * \n ");
	printf("\n *  W A S D               * \n ");
	printf("\n *  UP DOWN LEFT RIGHT    * \n ");
	printf("\n ************************** \n ");

	while(running) {
		SDL_PumpEvents();
		SDL_RenderPresent(window->renderer);
		SDL_RenderClear( window->renderer );

		SSL_Image_Draw(image, x, y, 0, 1, SDL_FLIP_NONE, window);

		if (SSL_Keybord_Keyname_Down("_left") || SSL_Keybord_Key_Down(SDL_SCANCODE_A)) {
			x-=speed;
		}
		if (SSL_Keybord_Keyname_Down("_right") || SSL_Keybord_Key_Down(SDL_SCANCODE_D)) {
			x+=speed;
		}
		if (SSL_Keybord_Keyname_Down("_up") || SSL_Keybord_Key_Down(SDL_SCANCODE_W)) {
			y-=speed;
		}
		if (SSL_Keybord_Keyname_Down("_down") || SSL_Keybord_Key_Down(SDL_SCANCODE_S)) {
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

	SSL_Window_Destroy(window);
	SSL_Image_Destroy(image);

    SDL_Quit();

	printf(" SSL keyboard input test passed...\n");
}
