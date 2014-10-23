#ifndef SDL_API_IMAGE_H_
#define SDL_API_IMAGE_H_

#include "../../../lib/SDL2/SDL.h"
#include "sdl_window.h"

/** Image struct */
typedef struct _Image {
		SDL_Texture *Image;		/** The texture */
		int texture_width;		/** width of the texture */
	    int texture_height;     /** height of the texture */
		int frame_height;		/** height of each frame */
		int frame_width;		/** width of each frame */
		int amount_of_frames;	/** amount of frame in the image */
		int x;					/** last x Position of the image */
		int y;					/** last y Position of the image */
} Image;

/* function prototyping */
Image *image_load(char *file, int frameWidth, int frameHeight, Window *window);

#endif /* SDL_API_IMAGE_H_ */
