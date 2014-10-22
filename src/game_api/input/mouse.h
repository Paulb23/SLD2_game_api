#ifndef MOUSE_H_
#define MOUSE_H_

#include "../../../lib/SDL2/SDL.h"

/* function prototyping */
int mouse_left_clicked();
int mouse_right_clicked();
int mouse_hover_in_area(int x, int y, int w, int h, SDL_Event event);
int mouse_left_click_in_area(int x, int y, int w, int h, SDL_Event event);
int mouse_right_click_in_area(int x, int y, int w, int h, SDL_Event event);

#endif /* MOUSE_H_ */
