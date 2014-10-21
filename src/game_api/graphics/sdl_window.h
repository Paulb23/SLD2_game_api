#ifndef SDL_WINDOW_H_
#define SDL_WINDOW_H_

#include "../../../lib/SDL2/SDL.h"
#include <stdint.h>

typedef struct _window {
	SDL_Window *window;
	SDL_Renderer *renderer;
} Window;

Window *window_create(char *title, int x, int y, int width, int height, uint32_t flags);
void window_set_icon(Window *window, char *icon);

#endif /* SDL_WINDOW_H_ */
