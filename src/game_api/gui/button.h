#ifndef BUTTON_H_
#define BUTTON_H_

#include "../../../lib/SDL2/SDL.h"
#include "../graphics/SSL_Image.h"
#include "../graphics/sdl_font.h"

/** Diffrent button types */
typedef enum Button_type {
	TEXT_BUTTON,
	IMAGE_BUTTON,
	CHECK_BOX
} Button_Type;

/** In all buttons */
typedef struct _Button {
	Button_Type type;					/** type of button */
	SDL_Rect position;					/** position and size of button */
} Button;


/** button status */
typedef struct _button_status {
	int hovered;						/** is the mouse hovered on the button */
	int clicked;						/** is the button clicked */
	int pressed;						/** is the mouse button down on the button */
} Button_status;

/** button image info */
typedef struct _Button_Image_Info {
	SSL_Image *image;						/** the image to draw with */
	int default_frame;					/** default frame to draw */
	int hovered_frame;					/** frame to draw when mouse is hovered */
	int pressed_frame;					/** frame to draw when the left button is held on the button */
} Button_Image_Info;

/** button text info */
typedef struct _Button_Text_Info {
	Font *font;							/** font to draw with */
	SDL_Color color;					/** color of the font */
	SDL_Color *background_color;		/** color behind the font */
	char *text;							/** text to draw on the button */
} Button_Text_Info;

/** The text baced button */
typedef struct _Text_Button {
	Button *button;						/** Basic button info */
	Button_Text_Info *button_text_info; /** text button info */
	Button_status * button_status;		/** status info */
} Text_Button;

/** The image baced button */
typedef struct _Image_Button {
	Button *button;							/** Basic button info */
	Button_Image_Info * button_image_info;	/** image button info */
	Button_status * button_status;			/** status info */
} Image_Button;

/** addition status for check box */
typedef struct _check_box_status {
	int active;								/** is the box ticked */
} Check_Box_Status;

/** addition info for check box */
typedef struct _check_box_image_info {
	int active_frame;						/** frame to draw when ticked */
} Check_Box_Image_Info;

/** The check box */
typedef struct _check_box {
	Button *button;								/** Basic button info */
	Button_Image_Info * button_image_info;		/** image button info */
	Button_status *button_status;				/** status info */
	Check_Box_Status *check_box_status;			/** additional status info */
	Check_Box_Image_Info *check_box_image_info; /** additional image info */
} Check_box;


/* function prototyping */
Text_Button *text_button_create(SDL_Rect *position, Font *font, SDL_Color *font_color, SDL_Color *background_color, char *text);
Image_Button *image_button_create(SDL_Rect *position, SSL_Image *image, int default_frame, int hovered_frame, int pressed_frame);
Check_box *check_box_create(SDL_Rect *position, SSL_Image *image, int default_frame, int hovered_frame, int pressed_frame, int active_frame);

#endif /* BUTTON_H_ */
