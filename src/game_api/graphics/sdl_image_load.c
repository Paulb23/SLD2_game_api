#include "sdl_image_load.h"
#include "../../../lib/SDL2/SDL.h"
#include "sdl_window.h"
#include <stdlib.h>

SDL_Texture *image_load_file(char *file, Image *image, Window *window);

Image *image_load(char *file, int width, int height, Window *window) {
	Image *image = malloc(sizeof(Image));
	if (!image) return (Image *)-1;

	image->Image = image_load_file(file, image,window);
	image->frame_width = width;
	image->frame_height = height;

	if (SDL_QueryTexture(image->Image, NULL, NULL, &image->texture_width, &image->texture_height) != 0) {
		return (Image *)-1;
	} else {

		int amountOfColumns = image->texture_width / image->frame_width;
		int amountOfRows    = image->texture_height/ image->frame_height;
		int amountOfFrames  = amountOfColumns * amountOfRows;

		image->amount_of_frames = amountOfFrames;
	}

	return image;
}

SDL_Texture *image_load_file(char *file, Image *image, Window *window) {
	SDL_Surface *surface = NULL;
	SDL_Texture *texture = NULL;

	surface = IMG_Load(file);

	if (!surface) {
		SDL_SetColorKey( surface, SDL_TRUE, SDL_MapRGB( surface->format, 255, 255, 255) );
		texture = SDL_CreateTextureFromSurface( window->renderer, surface );

		image->texture_height = surface->h;
		image->texture_width = surface->w;

		SDL_FreeSurface( surface );
	}

	SDL_SetTextureColorMod(texture, 0, 0 , 0);

	return texture;
}
