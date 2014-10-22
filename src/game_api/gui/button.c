#include "button.h"
#include "../misc/logger.h"
#include "../../../lib/SDL2/SDL.h"
#include "../misc/sdl_color.h"
#include <stdlib.h>

Text_Button *text_button_create(SDL_Rect *position, Font *font, SDL_Color *font_color, SDL_Color *background_color, char *text) {
	Text_Button *button = malloc(sizeof(Text_Button));
	button->button = malloc(sizeof(Button));
	button->button_status = malloc(sizeof(Button_status));
	button->button_text_info = malloc(sizeof(Button_Text_Info));

	button->button->type = TEXT_BUTTON;
	button->button->position = *position;
	button->button_status->clicked = 0;
	button->button_status->hovered = 0;
	button->button_status->pressed = 0;
	button->button_text_info->text = text;
	button->button_text_info->font = font;
	button->button_text_info->color = *font_color;
	button->button_text_info->background_color = background_color;

	return (button) ? button : (Text_Button *) -1;
}

Image_Button *image_button_create(SDL_Rect *position, Image *image, int default_frame, int hovered_frame) {
	Image_Button *button = malloc(sizeof(Image_Button));
	button->button = malloc(sizeof(Button));
	button->button_status = malloc(sizeof(Button_status));
	button->button_image_info = malloc(sizeof(Button_Image_Info));

	button->button->type = IMAGE_BUTTON;
	button->button->position = *position;
	button->button_status->clicked = 0;
	button->button_status->hovered = 0;
	button->button_status->pressed = 0;
	button->button_image_info->image = image;
	button->button_image_info->default_frame = default_frame;
	button->button_image_info->hovered_frame = hovered_frame;

	return (button) ? button : (Image_Button *) -1;
}
