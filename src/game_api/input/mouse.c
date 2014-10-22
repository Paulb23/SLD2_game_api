#include "mouse.h"
#include "../../../lib/SDL2/SDL.h"

/* function prototyping */
static int in_area(int x1, int y1, int x2, int y2, int w2, int h2);


/**************************
 *
 *  has the left mouse been clicked
 *
 *
 *************************/
int mouse_left_clicked() {
	return (SDL_GetMouseState(NULL,NULL) & SDL_BUTTON(SDL_BUTTON_LEFT));
}


/**************************
 *
 *  has the right mouse been clicked
 *
 *************************/
int mouse_right_clicked () {
	return (SDL_GetMouseState(NULL,NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT));
}


/**************************
 *
 *  is the mouse hovering in an area
 *
 *  @param x - x position of the object
 *  @param y - y position of the object
 *  @param w - width position of the object
 *  @param h - height position of the object
 *  @param event - the event queue
 *
 *************************/
int mouse_hover_in_area(int x, int y, int w, int h, SDL_Event event) {

	int state = 0;
	int mx = event.motion.x;			/* get mouse x and y */
	int my = event.motion.y;

	if (in_area(mx, my, x, y, w, h)) {  /* check if it is in the area */
		state = 1;
	}

	return state;						/* return */
}


/**************************
 *
 *  is the mouse left clicked in an area
 *
 *  @param x - x position of the object
 *  @param y - y position of the object
 *  @param w - width position of the object
 *  @param h - height position of the object
 *  @param event - the event queue
 *
 *************************/
int mouse_left_click_in_area(int x, int y, int w, int h, SDL_Event event) {

	int state = 0;
	int ex = event.button.x;												/* get mouse x and y */
	int ey = event.button.y;

	if (SDL_GetMouseState(NULL,NULL) & SDL_BUTTON(SDL_BUTTON_LEFT) ) {		/* if the left button was clicked */
		if (in_area(ex, ey, x, y, w, h)) {									/* check if it is in the area */
			event.button.button = 0;
			state = 1;
		}
	}

	return state;															/* return */
}


/**************************
 *
 *  is the mouse right clicked in an area
 *
 *  @param x - x position of the object
 *  @param y - y position of the object
 *  @param w - width position of the object
 *  @param h - height position of the object
 *  @param event - the event queue
 *
 *************************/
int mouse_right_click_in_area(int x, int y, int w, int h, SDL_Event event) {

	int state = 0;
	int ex = event.button.x;												/* get mouse x and y */
	int ey = event.button.y;

	if (SDL_GetMouseState(NULL,NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT) ) {		/* if the left button was clicked */
		if (in_area(ex, ey, x, y, w, h)) {									/* check if it is in the area */
			event.button.button = 0;
			state = 1;
		}
	}

	return state;															/* return */
}


/**************************
 *
 *  is x1 and y1 inside an area
 *
 *  @param x1 - x point
 *  @param y1 - y point
 *  @param x2 - x position of the object
 *  @param y2 - y position of the object
 *  @param w2 - width position of the object
 *  @param h2 - height position of the object
 *
 *************************/
static int in_area(int x1, int y1, int x2, int y2, int w2, int h2) {
	return ( x1 > x2 ) && ( x1 < x2 + w2 ) && ( y1 > y2 ) && ( y1 < y2 + h2 );
}
