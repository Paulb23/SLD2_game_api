#include "../../../lib/SDL2/SDL.h"
#include "../misc/logger.h"
#include "sdl_window.h"
#include "sdl_image_load.h"

/**************************//**
 *
 *	Draws an image to a window
 *
 *	@param image - image to draw
 *	@param x - x position to draw
 *	@param y - y position to draw
 *	@param angle - angle of the image
 *	@param frame - frame of the image to draw
 *	@param flip - Filp the image one of the following:
 *				  :: SDL_FLIP_NONE :: SDL_FLIP_HORIZONTAL :: SDL_FLIP_VERTICAL
 *	@param window - window to draw on
 *
 *************************/
void image_draw(Image *Image, int x, int y, int angle, int frame, SDL_RendererFlip flip, Window *window) {
		SDL_Rect imageFrame;															/* image frame, rectangle inside the image to draw */
		imageFrame.x = 0;
		imageFrame.y = 0;
		imageFrame.w = Image->texture_width;
		imageFrame.h = Image->texture_height;
																						/* if they want a frame, not the whole image */
		if ((Image->frame_height != 0 && Image->frame_width != 0) || frame != 0) {

			int amountOfColumns = Image->texture_width / Image->frame_width;			/* Calculate the coordinated of the frame */

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

		SDL_Rect offset;																/* rectangle for the location in the window */
		offset.x = x;
		offset.y = y;
		offset.w = Image->frame_width;
		offset.h = Image->frame_height;

		Image->x = x;																	/* update the image position */
		Image->y = y;

		SDL_Point centre;																/* find the centre of the frame */
		centre.x = imageFrame.w / 2;
		centre.y = imageFrame.h / 2;
																						/* draw the image */
		SDL_RenderCopyEx( window->renderer, Image->Image, &imageFrame, &offset, angle, &centre, flip);
}

