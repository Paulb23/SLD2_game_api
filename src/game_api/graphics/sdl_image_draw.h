#ifndef SDL_IMAGE_DRAW_H_
#define SDL_IMAGE_DRAW_H_

#include "SSL_window.h"
#include "sdl_image_load.h"

/* function prototyping */
void image_draw(Image *Image, int x, int y, int angle, int frame, SDL_RendererFlip flip, SSL_Window *window);

#endif /* SDL_IMAGE_DRAW_H_ */
