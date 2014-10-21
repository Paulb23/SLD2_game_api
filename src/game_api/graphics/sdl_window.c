#include "sdl_window.h"
#include "../../../lib/SDL2/SDL_image.h"
#include <stdlib.h>
#include <stdint.h>

Window *window_create(char *title, int x, int y, int width, int height, uint32_t flags) {
	Window *window =  malloc(sizeof(Window));
	if (!window) return (Window *)-1;

	window->window = SDL_CreateWindow(title, x, y, width, height, flags);
	window->renderer = SDL_CreateRenderer(window->window, -1, SDL_RENDERER_ACCELERATED);

	SDL_SetRenderDrawBlendMode(window->renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderSetViewport(window->renderer, NULL );
	SDL_RenderSetLogicalSize(window->renderer, width, height);

	return window;
}

void window_set_icon(Window *window, char *icon) {
	SDL_SetWindowIcon(window->window, (SDL_Surface *)IMG_Load(icon));
}
