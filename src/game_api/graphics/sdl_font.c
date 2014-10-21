#include "../../../lib/SDL2/SDL.h"
#include "../../../lib/SDL2/SDL_ttf.h"
#include "../misc/logger.h"
#include "sdl_window.h"
#include "sdl_font.h"
#include <stdlib.h>

/**************************
 *
 *  Loads and returns a TTF font
 *
 *  @param file - path to the font
 *  @param size - size of the font
 *
 *************************/
Font *font_load(char *file, int size) {
	Font *font = malloc(sizeof(Font));
	font->font = TTF_OpenFont(file, size);
	return font;
}


/**************************
 *
 *  draws a TTF font
 *
 *  @param x - x position to draw the text
 *  @param y - y position to draw the text
 *  @param text - text to draw
 *  @param font - font to draw
 *  @param window to draw to
 *
 *************************/
void font_draw(int x, int y, int angle, SDL_RendererFlip flip, char *text, Font *font, SDL_Color fontColor, Window *window) {

	SDL_Surface *textSurface = TTF_RenderText_Solid(font->font, text, fontColor);				/* create the font texture */
	SDL_Texture *textTexture = SDL_CreateTextureFromSurface(window->renderer, textSurface);

	if (SDL_QueryTexture(textTexture, NULL, NULL, &textSurface->w, &textSurface->h) != 0) {		/* check that it's valid */
		if (LOGGIN) { log_write("Failed to create font texture reader! ");}
		return;
	} else {

		SDL_Rect offset;																		/* rectangle to hold the position */
			offset.x = x;
			offset.y = y;
			offset.w = textSurface->w;
			offset.h = textSurface->h;

		SDL_RenderCopyEx( window->renderer, textTexture, NULL, &offset, angle, NULL, flip);	/* draw the text */
	}
	SDL_FreeSurface(textSurface);																/* DO NOT REMOVE STOPS MEMORY LEAK */
	SDL_DestroyTexture(textTexture);
}
