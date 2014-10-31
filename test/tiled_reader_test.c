#include "tests.h"
#include "../src/SSL/files/SSL_Tiled.h"
#include <stdio.h>

void tiled_reader_test() {
	SDL_Init(SDL_INIT_EVERYTHING);

	SSL_Window *window = SSL_Window_Create("This is the tile reader test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600,0,0, 0);
	SSL_Tiled_Map *map = SSL_Tiled_Map_Load("../extras/resources/map.tmx", window);



	SDL_Event event;
	int running = 1;

	while(running) {
		SDL_PumpEvents();
		SDL_RenderPresent(window->renderer);
		SDL_RenderClear( window->renderer );

		SSL_Tiled_Draw_Map(map, 100, 100, window);

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT) {
			   running = 0;
			   break;
			 }
		}

	SDL_Delay(10);
	}
	SSL_Tiled_Map_Destroy(map);
	SDL_Quit();
	printf("\n SSL Tiled reader test passed...\n");
}
