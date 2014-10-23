#include "sdl_image_load.h"
#include "../../../lib/SDL2/SDL.h"
#include "../../../lib/SDL2/SDL_image.h"
#include "../misc/logger.h"
#include "sdl_window.h"
#include <stdlib.h>
#include <stdio.h>

/* function prototyping */
static SDL_Texture *image_load_file(char file[], Image *image, Window *window);

/**************************//**
 *
 * Loads an image and returns it.
 * returns -1 on fail
 *
 * @param file - path to the image
 * @param frameWidth - height of each frame
 * @param frameHeight - width of each frame
 * @param window - window to use
 *
 *************************/
Image *image_load(char *file, int frameWidth, int frameHeight, Window *window) {
	Image *image = malloc(sizeof(Image));														/* Allocate memory */
	if (!image) {log_write("Failed to allocate memory, loading image! "); return (Image *)-1;}	/* return of failed allocation */

	image->Image = image_load_file(file, image,window);														/* actually load the texture */
	image->frame_width = frameWidth;																		/* init the frame variables */
	image->frame_height = frameHeight;

	if (SDL_QueryTexture(image->Image, NULL, NULL, &image->texture_width, &image->texture_height) != 0) {	/* check texture is valid else return */
		log_write("Failed to create image texture! ");
		return (Image *)-1;
	} else if (frameWidth != 0 && frameHeight != 0) {														/* Calculate the amount of frame in the image */

		int amountOfColumns = image->texture_width / image->frame_width;
		int amountOfRows    = image->texture_height/ image->frame_height;
		int amountOfFrames  = amountOfColumns * amountOfRows;

		image->amount_of_frames = amountOfFrames;
	} else {
		image->amount_of_frames = 0;
	}

	return image;																							/* return the image */
}


/**************************//**
 *
 * Loads the image file
 * SHOULD NOT HAVE TO CALL USED BY IMAGE_LOAD
 *
 * @param file - path to the image
 * @param image - image to store it in
 * @param window - window to use
 *
 *************************/
static SDL_Texture *image_load_file(char file[], Image *image, Window *window) {
	SDL_Surface *surface = NULL;																		/* Create surface and texture */
	SDL_Texture *texture = NULL;

	surface = IMG_Load(file);																			/* Load the file */

	if (surface != NULL) {																				/* if we could load the file  */
		//SDL_SetColorKey( surface, SDL_TRUE, SDL_MapRGB( surface->format, 255, 255, 255) );				/* remove all white and convert to a texture TODO: FIX REMOVES YELLOW? */
		texture = SDL_CreateTextureFromSurface( window->renderer, surface );

		image->texture_height = surface->h;																/* update the image width, height */
		image->texture_width = surface->w;

		SDL_FreeSurface( surface );																		/* free the surface */
	}
	return texture;																						/* return the texture */
}
