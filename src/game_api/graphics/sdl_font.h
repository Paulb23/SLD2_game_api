#ifndef SDL_FONT_H_
#define SDL_FONT_H_

#include "../../../lib/SDL2/SDL_ttf.h"

/** Font struct */
typedef struct _font {
	TTF_Font *font;
} Font;

/* function prototyping */
Font *font_load(char *file, int size);
void font_draw(int x, int y, int angle, SDL_RendererFlip flip, char *text, Font *font, SDL_Color fontColor, SSL_Window *window);

#endif /* SDL_FONT_H_ */
