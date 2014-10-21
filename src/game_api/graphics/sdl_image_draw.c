#include "../../../lib/SDL2/SDL.h"
#include "sdl_window.h"
#include "sdl_image_load.h"

void image_draw(Image *Image, int x, int y, int angle, int frame, SDL_RendererFlip flip, Window *window) {
		SDL_Rect imageFrame;
		imageFrame.x = 0;
		imageFrame.y = 0;
		imageFrame.w = Image->texture_width;
		imageFrame.h = Image->texture_height;

		if (!(Image->frame_height == 0 && Image->frame_width == 0) || frame != 0) {

			int amountOfColumns = Image->texture_width / Image->frame_width;

			imageFrame.w = Image->frame_width;
			imageFrame.h = Image->frame_height;

			if (frame != 1) {

				int i = 0;

				for (i = 1; i <= frame - 1; i ++) {
					imageFrame.x = imageFrame.x + Image->frame_width;

					if (!(i % amountOfColumns)) {
						imageFrame.x = 0;
						imageFrame.y = imageFrame.y + Image->frame_height;
					}
				}
			}
		}

		SDL_Rect offset;
		offset.x = x;
		offset.y = y;
		offset.w = Image->frame_width;
		offset.h = Image->frame_height;

		Image->x = x;
		Image->y = y;

		SDL_Point centre;
		centre.x = imageFrame.w / 2;
		centre.y = imageFrame.h / 2;

		SDL_RenderCopyEx( window->renderer, Image->Image, &imageFrame, &offset, angle, &centre, flip);
}

