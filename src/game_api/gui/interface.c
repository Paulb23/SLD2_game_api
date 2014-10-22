#include "interface.h"
#include "../misc/logger.h"
#include "../misc/list.h"
#include "../misc/sdl_color.h"
#include "../graphics/sdl_window.h"
#include "../graphics/sdl_image_draw.h"
#include <stdlib.h>

/**************************
 *
 * Creates a Interface an returns it
 * If it fails to create return -1
 *
 *************************/
Interface *interface_create() {
	Interface *interface = malloc(sizeof(Interface));
	if (!interface) {log_write("Failed to allocate memory for new Interface! "); return (Interface *)-1;}

	interface->buttons = list_create();
	interface->textboxes = list_create();

	return interface;
}

void interface_add_text_button(Interface *interface, Text_Button *text_button) {
	list_set(interface->buttons, text_button);
}

void interface_add_image_button(Interface *interface, Image_Button *image_button) {
	list_set(interface->buttons, image_button);
}

void interface_draw(Interface *interface, Window *window) {
	int i = 1;
	Text_Button * text_button;
	Image_Button * image_button;

	while (list_get(interface->buttons, i) != (void *)-1) {

		text_button = list_get(interface->buttons, i);

		if (text_button->button->type == TEXT_BUTTON) {
				SDL_Color *c;
				c = (SDL_Color *)color_create(255, 255, 255, 255);
				SDL_GetRenderDrawColor(window->renderer, &c->r, &c->g, &c->b, &c->a);
				SDL_SetRenderDrawColor(window->renderer, text_button->button_text_info->background_color->r, text_button->button_text_info->background_color->g, text_button->button_text_info->background_color->b, text_button->button_text_info->background_color->a);
				SDL_RenderFillRect(window->renderer, &text_button->button->position);
				SDL_SetRenderDrawColor(window->renderer, c->r, c->g, c->b, c->a);
				font_draw(text_button->button->position.x + 5, text_button->button->position.y - 5, 0, SDL_FLIP_NONE, text_button->button_text_info->text, text_button->button_text_info->font, text_button->button_text_info->color, window);
		} else {
			image_button = list_get(interface->buttons, i);

			if (image_button->button_status->hovered) {
				image_draw(image_button->button_image_info->image, image_button->button->position.x, image_button->button->position.y, 0,image_button->button_image_info->hovered_frame, SDL_FLIP_NONE, window);
			} else {
				image_draw(image_button->button_image_info->image, image_button->button->position.x, image_button->button->position.y, 0,image_button->button_image_info->default_frame, SDL_FLIP_NONE, window);
			}
		}
	 i++;
	}
}

void interface_update(Interface *interface, SDL_Event event) {
	Text_Button *button;

	int i = 1;
	int x = event.button.x;
	int y = event.button.y;

	while (list_get(interface->buttons, i) != (void *)-1) {

		button = list_get(interface->buttons, i);

		if (( x > button->button->position.x ) && ( x < button->button->position.x + button->button->position.w ) && ( y > button->button->position.y ) && ( y < button->button->position.y + button->button->position.h )) {
				button->button_status->hovered = 1;
		} else {
				button->button_status->hovered = 0;
		}

		if (event.type == SDL_MOUSEBUTTONUP) {
			if(event.button.button == SDL_BUTTON_LEFT) {						// Left Button
				if (( x > button->button->position.x ) && ( x < button->button->position.x + button->button->position.w ) && ( y > button->button->position.y ) && ( y < button->button->position.y + button->button->position.h )) {
						event.button.button = 0;
						button->button_status->clicked = 1;
				} else {
						button->button_status->clicked = 0;
				}
			} else {
				button->button_status->clicked = 0;
			}
		} else {
			button->button_status->clicked = 0;
		}

		if (event.type == SDL_MOUSEBUTTONDOWN) {
			if(event.button.button == SDL_BUTTON_LEFT) {						// Left Button
				if (( x > button->button->position.x ) && ( x < button->button->position.x + button->button->position.w ) && ( y > button->button->position.y ) && ( y < button->button->position.y + button->button->position.h )) {
						event.button.button = 0;
						button->button_status->pressed = 1;
				} else {
						button->button_status->pressed = 0;
				}
			} else {
				button->button_status->pressed = 0;
			}
		} else {
			button->button_status->pressed = 0;
		}
	 i++;
	}
}
