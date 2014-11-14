#include "tests.h"
#include "../src/SSL/graphics/SSL_Window.h"
#include "../src/SSL/graphics/SSL_Font.h"
#include "../src/SSL/misc/SSL_Color.h"
#include "../src/SSL/misc/SSL_Rectangle.h"
#include "../src/SSL/gui/SSL_Interface.h"
#include "../src/SSL/gui/SSL_Button.h"
#include <stdio.h>

static void test1() {
	SSL_Window *window = SSL_Window_Create("This is the Sdl user interface test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 200, 200, 0, 0, 0);
	SSL_Interface *interface = SSL_Interface_Create();

	SSL_Text_Button *text_button = SSL_Text_Button_Create(SSL_Rectangle_Create(20, 50, 150, 50), SSL_Font_Load("../extras/resources/debug.ttf", 50), SSL_Color_Create(255,255,255,255), SSL_Color_Create(255,0,0,255), "button?");
	SSL_Interface_Add_Text_Button(interface, text_button);

	SDL_Event event;
	int running = 1;

	printf("\n ************************** \n ");
	printf("\n * Can You See An button? * \n ");
	printf("\n * Hover, Mouse down and  * \n ");
	printf("\n * Click it               * \n ");
	printf("\n ************************** \n ");


	while(running) {
		SDL_PumpEvents();
		SDL_RenderPresent(window->renderer);
		SDL_RenderClear( window->renderer );

		interface_draw(interface, window);
		interface_update(interface, event);

		if (text_button->button_status->pressed) {
			text_button->button_text_info->background_color = SSL_Color_Create(0, 0, 255 ,255);
		} else if (text_button->button_status->hovered) {
			text_button->button_text_info->background_color = SSL_Color_Create(0, 255, 0 ,255);
		} else {
			text_button->button_text_info->background_color = SSL_Color_Create(255, 0, 0 ,255);
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

	SSL_Interface_Destroy(interface);
	SSL_Window_Destroy(window);
}

static void test2() {
	SSL_Window *window = SSL_Window_Create("This is the Sdl user interface test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 200, 200, 0, 0, 0);
	SSL_Interface *interface = SSL_Interface_Create();

	SSL_Image_Button *image_button = SSL_Image_Button_Create(SSL_Rectangle_Create(50, 50, 100, 100), SSL_Image_Load("../extras/resources/test_image.png", 100, 100, window), 1, 2, 3);
	SSL_Interface_Add_Image_Button(interface, image_button);

	SDL_Event event;
	int running = 1;

	printf("\n ************************** \n ");
	printf("\n * Can You See An button? * \n ");
	printf("\n * Hover, Mouse down and  * \n ");
	printf("\n * Click it               * \n ");
	printf("\n ************************** \n ");

	while(running) {
		SDL_PumpEvents();
		SDL_RenderPresent(window->renderer);
		SDL_RenderClear( window->renderer );

		interface_draw(interface, window);
		interface_update(interface, event);

		while (SDL_PollEvent(&event))
		 {
			if (event.type == SDL_QUIT) {
				   running = 0;
				   break;
			}
		}
	SDL_Delay(10);
	}

	SSL_Interface_Destroy(interface);
	SSL_Window_Destroy(window);
}


static void test3() {
	SSL_Window *window = SSL_Window_Create("This is the Sdl user interface test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 200, 200, 0, 0, 0);
	SSL_Interface *interface = SSL_Interface_Create();

	SSL_Check_box *check_box = SSL_Check_Box_Create(SSL_Rectangle_Create(50, 50, 50, 50), SSL_Image_Load("../extras/resources/check_box.png", 50, 50, window), 1, 1, 2, 3);
	SSL_Interface_Add_Check_Box(interface, check_box);

	SDL_Event event;
	int running = 1;

	printf("\n ************************** \n ");
	printf("\n * Can You See An box?    * \n ");;
	printf("\n * Click it               * \n ");
	printf("\n ************************** \n ");

	while(running) {
		SDL_PumpEvents();
		SDL_RenderPresent(window->renderer);
		SDL_RenderClear( window->renderer );

		interface_draw(interface, window);
		interface_update(interface, event);

		while (SDL_PollEvent(&event))
		 {
			if (event.type == SDL_QUIT) {
				   running = 0;
				   break;
			}
		}
	SDL_Delay(10);
	}

	SSL_Interface_Destroy(interface);
	SSL_Window_Destroy(window);
}
void user_interface_test() {
	printf("\n Starting SSL user interface Tests...\n");
	SDL_Init(SDL_INIT_EVERYTHING);

		//test1();
		test2();
		test3();

	    SDL_Quit();

 printf(" SSL user interface passed...\n");
}
