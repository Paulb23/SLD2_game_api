#include "tests.h"
#include "../src/SSL/graphics/SSL_Window.h"
#include "../src/SSL/graphics/SSL_Image.h"
#include "../src/SSL/graphics/SSL_Font.h"
#include "../src/SSL/misc/SSL_Color.h"
#include "../src/SSL/input/keyboard.h"
#include <stdio.h>

/**
 *  Creates a window with a animated images until the user closes the window
 */
void keybord_input_test() {
	SDL_Init(SDL_INIT_EVERYTHING);

	SSL_Window *window = SSL_Window_Create("This is the Sdl keyboard input test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0, 0, 0);
	SSL_Image *image = SSL_Image_Load("../extras/resources/test_image.png", 10, 10, window);

	SSL_Font *font = SSL_Font_Load("../extras/resources/debug.ttf", 65);

	SDL_Event event;
	int running = 1;

	int x = 100;
	int y = 100;
	int speed = 10;

	while(running) {
		SDL_PumpEvents();
		SDL_RenderPresent(window->renderer);
		SDL_RenderClear( window->renderer );

		SSL_Font_Draw(0, 0, 0, SDL_FLIP_NONE, "Use the arrow or wasd keys to move", font, *SSL_Color_Create(255,255,255,0), window);
		SSL_Image_Draw(image, x, y, 0, 1, SDL_FLIP_NONE, window);

		if (keybord_keyname_down("_left") || keybord_key_down(SDL_SCANCODE_A)) {
			x-=speed;
		}
		if (keybord_keyname_down("_right") || keybord_key_down(SDL_SCANCODE_D)) {
			x+=speed;
		}
		if (keybord_keyname_down("_up") || keybord_key_down(SDL_SCANCODE_W)) {
			y-=speed;
		}
		if (keybord_keyname_down("_down") || keybord_key_down(SDL_SCANCODE_S)) {
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
