#ifndef SDL_IMAGE_DRAW_H_
#define SDL_IMAGE_DRAW_H_

#include "sdl_window.h"
#include "sdl_image_load.h"

/* function prototyping */
void image_draw(Image *Image, int x, int y, int angle, int frame, SDL_RendererFlip flip, Window *window);

#endif /* SDL_IMAGE_DRAW_H_ */
