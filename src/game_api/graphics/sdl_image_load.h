#ifndef SDL_API_IMAGE_H_
#define SDL_API_IMAGE_H_

#include "../../../lib/SDL2/SDL.h"
#include "sdl_window.h"

typedef struct _Image {
		SDL_Texture *Image;
		int texture_width;
	    int texture_height;
		int frame_height;
		int frame_width;
		int amount_of_frames;
		int x;
		int y;
} Image;

Image *image_load(char *file, int width, int height, Window *window);

#endif /* SDL_API_IMAGE_H_ */
