#include "tests.h"
#include "../src/SSL/files/SSL_Tiled_Reader.h"
#include <stdio.h>

void tiled_reader_test() {
	SDL_Init(SDL_INIT_EVERYTHING);

	SSL_Window *window = SSL_Window_Create("This is the tile reader test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600,0,0, 0);
	SSL_Tiled_Map *map = SSL_Tiled_Map_Load(window);

	int (*tiles)[16][16];
	tiles = map->layer->next->value;

	SSL_Tileset_Info *tileset = map->tileset->tilesets->next->value;

	SDL_Event event;
	int running = 1;

	while(running) {
		SDL_PumpEvents();
		SDL_RenderPresent(window->renderer);
		SDL_RenderClear( window->renderer );

		int i, j;
		  for (i = 0; i <16; i++) {
			  for (j = 0; j <16; j++) {
				  SSL_Image_Draw(tileset->image, j * 16, i*16,0,(*tiles)[j][i],SDL_FLIP_NONE, window);
			  }
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
	printf("\n SSL Tiled reader test passed...\n");
}
