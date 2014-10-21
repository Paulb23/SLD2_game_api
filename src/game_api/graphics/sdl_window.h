#ifndef SDL_WINDOW_H_
#define SDL_WINDOW_H_

#include "../../../lib/SDL2/SDL.h"
#include <stdint.h>

/* window struct */
typedef struct _window {
	SDL_Window *window;			/* Sdl window */
	SDL_Renderer *renderer;		/* Sdl renderer */
} Window;

/* function prototypes */
Window *window_create(char *title, int x, int y, int width, int height, uint32_t flags);
void window_set_icon(Window *window, char *icon);

#endif /* SDL_WINDOW_H_ */
