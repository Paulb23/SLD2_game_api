#include "button.h"
#include "../misc/logger.h"
#include "../../../lib/SDL2/SDL.h"
#include "../misc/sdl_color.h"
#include <stdlib.h>


/**************************//**
 *
 *  Creates button without an image
 *
 *  @param position - position and size of the button
 *  @param font - font to draw with
 *  @param font color - color of the font
 *  @param background color - color behind the font
 *  @param text - text to draw on the button
 *
 *************************/
Text_Button *text_button_create(SDL_Rect *position, SSL_Font *font, SDL_Color *font_color, SDL_Color *background_color, char *text) {
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


/**************************//**
 *
 *  Creates button with a image
 *
 *  @param position - position and size of the button
 *  @param image - image to use
 *  @param default frame - default frame to draw
 *  @param hovered_frame - frame to draw when mouse is hovered
 *  @param pressed_frame - frame to draw when the left button is held on the button
 *
 *************************/
Image_Button *image_button_create(SDL_Rect *position, SSL_Image *image, int default_frame, int hovered_frame, int pressed_frame) {
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
	button->button_image_info->pressed_frame = pressed_frame;

	return (button) ? button : (Image_Button *) -1;
}


/**************************//**
 *
 *  Creates button with a image
 *
 *  @param position - position and size of the button
 *  @param image - image to use
 *  @param default frame - default frame to draw
 *  @param hovered_frame - frame to draw when mouse is hovered
 *  @param pressed_frame - frame to draw when the left button is held on the button
 *  @param active_frame - frame to draw when check box is ticked
 *
 *************************/
Check_box *check_box_create(SDL_Rect *position, SSL_Image *image, int default_frame, int hovered_frame, int pressed_frame, int active_frame) {
	Check_box *button = malloc(sizeof(Check_box));
	button->button = malloc(sizeof(Button));
	button->button_status = malloc(sizeof(Button_status));
	button->check_box_status = malloc(sizeof(Check_Box_Status));
	button->button_image_info = malloc(sizeof(Button_Image_Info));
	button->check_box_image_info = malloc(sizeof(Check_Box_Image_Info));

	button->button->type = CHECK_BOX;
	button->button->position = *position;
	button->button_status->clicked = 0;
	button->button_status->hovered = 0;
	button->button_status->pressed = 0;
	button->check_box_status->active = 0;
	button->button_image_info->image = image;
	button->button_image_info->default_frame = default_frame;
	button->button_image_info->hovered_frame = hovered_frame;
	button->button_image_info->pressed_frame = pressed_frame;
	button->check_box_image_info->active_frame = active_frame;

	return (button) ? button : (Check_box *) -1;
}
