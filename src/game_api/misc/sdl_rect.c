#include "../../../lib/SDL2/SDL.h"
#include "sdl_rect.h"
#include <stdlib.h>

/**************************
 *
 *  Creates a SDL solor
 *
 *  @param x - x position
 *  @param y - y position
 *  @param w - width
 *  @param h - height
 *
 *************************/
SDL_Rect *rect_create(double x, double y, double w, double h) {
	SDL_Rect *rect = malloc(sizeof(SDL_Rect));
		rect->x = x;
		rect->y = y;
		rect->w = w;
		rect->h = h;
	return rect;
}
