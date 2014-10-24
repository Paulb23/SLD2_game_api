#include "tests.h"
#include "../src/game_api/graphics/SSL_Window.h"
#include "../src/game_api/graphics/SSL_Font.h"
#include "../src/game_api/misc/sdl_color.h"
#include "../src/game_api/misc/sdl_rect.h"
#include "../src/game_api/gui/interface.h"
#include "../src/game_api/gui/button.h"
#include <stdio.h>

void user_interface_test() {
	SDL_Init(SDL_INIT_EVERYTHING);

	SSL_Window *window = SSL_Window_Create("This is the Sdl user interface test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0, 0, 0);
	Interface *interface = interface_create();

	Text_Button *text_button = text_button_create(rect_create(100, 100, 150, 50), SSL_Font_Load("../extras/resources/debug.ttf", 50), color_create(255,255,255,255), color_create(255,0,0,255), "button?");
	Image_Button *image_button = image_button_create(rect_create(100, 200, 100, 100), SSL_Image_Load("../extras/resources/test_image.png", 100, 100, window), 1, 2, 3);
	Check_box *check_box = check_box_create(rect_create(100, 400, 100, 100), SSL_Image_Load("../extras/resources/check_box.png", 50, 50, window), 1, 1, 2, 3);

	interface_add_text_button(interface, text_button);
	interface_add_image_button(interface, image_button);
	interface_add_check_box(interface, check_box);


		SDL_Event event;
		int running = 1;

		while(running) {
			SDL_PumpEvents();
			SDL_RenderPresent(window->renderer);
			SDL_RenderClear( window->renderer );

			interface_draw(interface, window);
			interface_update(interface, event);

			if (text_button->button_status->pressed) {
				text_button->button_text_info->background_color = color_create(0, 0, 255 ,255);
			} else if (text_button->button_status->hovered) {
				text_button->button_text_info->background_color = color_create(0, 255, 0 ,255);
			} else {
				text_button->button_text_info->background_color = color_create(255, 0, 0 ,255);
			}

			if (text_button->button_status->clicked) {
				text_button->button_text_info->text = "Clicked!";
			}
			while (SDL_PollEvent(&event))
			 {
			    if (event.type == SDL_QUIT) {
			    	running = 0;
			    	break;
			    }
			 }
		SDL_Delay(10);
		}

	    SDL_Quit();

 printf("\n Sdl user interface passed...\n");
}
