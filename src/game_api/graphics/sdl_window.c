#include "sdl_window.h"
#include "../../../lib/SDL2/SDL_image.h"
#include <stdlib.h>
#include <stdint.h>

/**************************
 *
 * Creates a new window and returns it.
 * else -1 on failed creation
 *
 *@param title - title of the window
 *@param x - x position to create the window
 *@param y - y position to create the window
 *@param width - width of the window
 *@param height - height of the window
 *@param flags - The flags for the window, can use multiple like so: FLAG_1 || FLAG_2 || FLAG_3
 *               ::SDL_WINDOW_FULLSCREEN, ::SDL_WINDOW_OPENGL,
 *               ::SDL_WINDOW_HIDDEN,     ::SDL_WINDOW_BORDERLESS,
 *               ::SDL_WINDOW_RESIZABLE,  ::SDL_WINDOW_MAXIMIZED,
 *               ::SDL_WINDOW_MINIMIZED,  ::SDL_WINDOW_INPUT_GRABBED.
 *
 *************************/
Window *window_create(char *title, int x, int y, int width, int height, uint32_t flags) {
	Window *window =  malloc(sizeof(Window));												/* allocate memory */
	if (!window) return (Window *)-1;														/* return of failed allocation */

	window->window = SDL_CreateWindow(title, x, y, width, height, flags);					/* create the window and render */
	window->renderer = SDL_CreateRenderer(window->window, -1, SDL_RENDERER_ACCELERATED);

	SDL_SetRenderDrawBlendMode(window->renderer, SDL_BLENDMODE_BLEND);						/* initilize them */
	SDL_RenderSetViewport(window->renderer, NULL );
	SDL_RenderSetLogicalSize(window->renderer, width, height);

	return window;
}


/**************************
 *
 * Changes the window icon to the one provided
 *
 *@param window - the window to add the icon to
 *@param icon - path to the icon image
 *
 *************************/
void window_set_icon(Window *window, char *icon) {
	SDL_SetWindowIcon(window->window, (SDL_Surface *)IMG_Load(icon));
}
