#ifndef INTERFACE_H_
#define INTERFACE_H_

#include "button.h"
#include "../misc/list.h"
#include "../graphics/sdl_window.h"

/* interface struct  */
typedef struct _Interface {
	List *buttons;			/* list of buttons on the interface */
	List *textboxes;		/* list of textboxes on the interface */
} Interface;

/* function prototyping */
Interface *interface_create();
void interface_add_text_button(Interface *interface, Text_Button *text_button);
void interface_add_image_button(Interface *interface, Image_Button *image_Button);
void interface_draw(Interface *interface, Window *window);
void interface_update(Interface *interface, SDL_Event event);

#endif /* INTERFACE_H_ */
