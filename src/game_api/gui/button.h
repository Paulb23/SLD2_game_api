#ifndef BUTTON_H_
#define BUTTON_H_

#include "../../../lib/SDL2/SDL.h"
#include "../graphics/sdl_image_load.h"
#include "../graphics/sdl_font.h"

typedef enum Button_type {
	TEXT_BUTTON,
	IMAGE_BUTTON,
	CHECK_BOX
} Button_Type;

typedef struct _Button {
	Button_Type type;
	SDL_Rect position;
} Button;

typedef struct _button_status {
	int hovered;
	int clicked;
	int pressed;
} Button_status;

typedef struct _Button_Image_Info {
	Image *image;
	int default_frame;
	int hovered_frame;
} Button_Image_Info;

typedef struct _Button_Text_Info {
	Font *font;
	SDL_Color color;
	SDL_Color *background_color;
	char *text;
} Button_Text_Info;

typedef struct _Text_Button {
	Button *button;
	Button_Text_Info *button_text_info;
	Button_status * button_status;
} Text_Button;

typedef struct _Image_Button {
	Button *button;
	Button_Image_Info * button_image_info;
	Button_status * button_status;
} Image_Button;

typedef struct _check_box {
	Button *button;
	Button_Image_Info * button_image_info;
	Button_status * button_status;
} Check_box;


/* function prototyping */
Text_Button *text_button_create(SDL_Rect *position, Font *font, SDL_Color *font_color, SDL_Color *background_color, char *text);
Image_Button *image_button_create(SDL_Rect *position, Image *image, int default_frame, int hovered_frame);

#endif /* BUTTON_H_ */
