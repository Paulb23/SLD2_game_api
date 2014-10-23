#include "../../../lib/SDL2/SDL.h"
#include "sdl_color.h"
#include <stdlib.h>

/**************************//**
 *
 *  Creates a SDL solor
 *
 *  @param r - amount of red
 *  @param g - amount of green
 *  @param b - amount of blue
 *  @param a - amount of alpha
 *
 *************************/
SDL_Color *color_create(int r, int g, int b, int a) {
	SDL_Color *color = malloc(sizeof(SDL_Color));
		color->r = r;
		color->g = g;
		color->b = b;
		color->a = a;
	return color;
}
