/*-------------------------------------------------------------------------*/
/**
   @file    SSL_Interface.h
   @author  P. Batty
   @brief   Implements a Interface to put buttons and other gui elements

   This module implements a interface to put gui elements, utilising the SLL_List
   Collection to store them.

*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "SSL_Interface.h"
#include "../misc/SSL_Logger.h"
#include "../misc/SSL_List.h"
#include "../misc/SSL_Color.h"
#include "../graphics/SSL_window.h"
#include "../graphics/SSL_Image.h"

#include <stdlib.h>


/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
|  @brief    Creates a new SSL_Interface object.
|  @return Pointer to a SSL_Interface object on successful creation otherwise 0.
|
|  Creates a new SSL_Interface object with allocated memory destroy with
|  SSL_Interface_Destroy.
|
|  If it cannot create the object it will return 0.
|
\-----------------------------------------------------------------------------*/
SSL_Interface *SSL_Interface_Create() {

	/* Allocate memory */
	SSL_Interface *interface = malloc(sizeof(SSL_Interface));

	/* Return if failed allocation */
	if (!interface) {
		SSL_Log_Write("Failed to allocate memory for new Interface! ");
		return 0;
	}

	/* create the list */
	interface->buttons = SSL_List_Create();

	/* check the list was created else return*/
	if (!interface->buttons) {
		SSL_Log_Write("Failed to allocate memory for new Interface! ");
		return 0;
	}

	/* return the interface */
	return interface;
}


/*!--------------------------------------------------------------------------
|  @brief    Adds a text button to the interface
|  @param    interface         Interface to add the button to.
|  @param    text_button       The button to add.
|  @return void
|
|  Adds a text button to the interface.
|
\-----------------------------------------------------------------------------*/
void SSL_Interface_Add_Text_Button(SSL_Interface *interface, SSL_Text_Button *text_button) {
	SSL_List_Add(interface->buttons, text_button);
}


/*!--------------------------------------------------------------------------
|  @brief    Adds a image button to the interface
|  @param    interface         Interface to add the button to.
|  @param    image_button       The button to add.
|  @return void
|
|  Adds a image button to the interface.
|
\-----------------------------------------------------------------------------*/
void SSL_Interface_Add_Image_Button(SSL_Interface *interface, SSL_Image_Button *image_button) {
	SSL_List_Add(interface->buttons, image_button);
}


/*!--------------------------------------------------------------------------
|  @brief    Adds a check box to the interface
|  @param    interface         Interface to add the check box to.
|  @param    image_button      The check box to add.
|  @return void
|
|  Adds a check box  to the interface.
|
\-----------------------------------------------------------------------------*/
void SSL_Interface_Add_Check_Box(SSL_Interface *interface, SSL_Check_box *check_box) {
	SSL_List_Add(interface->buttons, check_box);
}


/*!--------------------------------------------------------------------------
|  @brief    Removes a text button to the interface
|  @param    interface         Interface to remove the button to.
|  @param    text_button       The button to remove.
|  @return void
|
|  Removes a text button to the interface.
|
\-----------------------------------------------------------------------------*/
void SSL_Interface_Remove_Text_Button(SSL_Interface *interface, SSL_Text_Button *text_button) {
	SSL_List_Remove(interface->buttons, text_button);
}


/*!--------------------------------------------------------------------------
|  @brief    Removes a image button to the interface
|  @param    interface         Interface to remove the button to.
|  @param    image_button      The button to remove.
|  @return void
|
|  Removes a image button to the interface.
|
\-----------------------------------------------------------------------------*/
void SSL_Interface_Remove_Image_Button(SSL_Interface *interface, SSL_Image_Button *image_button) {
	SSL_List_Remove(interface->buttons, image_button);
}


/*!--------------------------------------------------------------------------
|  @brief    Removes a check box to the interface
|  @param    interface         Interface to remove the check box to.
|  @param    image_button      The check box to remove.
|  @return void
|
|  Removes a check box  to the interface.
|
\-----------------------------------------------------------------------------*/
void SSL_Interface_Remove_Check_Box(SSL_Interface *interface, SSL_Check_box *check_box) {
	SSL_List_Remove(interface->buttons, check_box);
}


/*!--------------------------------------------------------------------------
|  @brief    Draws all gui elements on the interface.
|  @param    interface         Interface to draw
|  @param    window    		   The window to draw them on.
|  @return void
|
|  Draws all gui elements on the interface. TODO: Clean up
|
\-----------------------------------------------------------------------------*/
void interface_draw(SSL_Interface *interface, SSL_Window *window) {
	int i = 1;
	SSL_Text_Button * text_button;
	SSL_Image_Button * image_button;
	SSL_Check_box * check_box;

	while (SSL_List_Get(interface->buttons, i) != (void *)-1) {

		text_button = SSL_List_Get(interface->buttons, i);

		if (text_button->button->type == TEXT_BUTTON) {
				SDL_Color *c;
				c = (SDL_Color *)SSL_Color_Create(255, 255, 255, 255);
				SDL_GetRenderDrawColor(window->renderer, &c->r, &c->g, &c->b, &c->a);
				SDL_SetRenderDrawColor(window->renderer, text_button->button_text_info->background_color->r, text_button->button_text_info->background_color->g, text_button->button_text_info->background_color->b, text_button->button_text_info->background_color->a);
				SDL_RenderFillRect(window->renderer, &text_button->button->position);
				SDL_SetRenderDrawColor(window->renderer, c->r, c->g, c->b, c->a);
				SSL_Font_Draw(text_button->button->position.x + 5, text_button->button->position.y - 5, 0, SDL_FLIP_NONE, text_button->button_text_info->text, text_button->button_text_info->font, text_button->button_text_info->font_color, window);
		} else if (text_button->button->type == CHECK_BOX) {
			check_box = SSL_List_Get(interface->buttons, i);

			if (check_box->check_box_status->active) {
				SSL_Image_Draw(check_box->button_image_info->image, check_box->button->position.x, check_box->button->position.y, 0,check_box->check_box_image_info->active_frame, SDL_FLIP_NONE, window);
			} else if (check_box->button_status->pressed) {
				SSL_Image_Draw(check_box->button_image_info->image, check_box->button->position.x, check_box->button->position.y, 0,check_box->button_image_info->pressed_frame, SDL_FLIP_NONE, window);
			} else if (check_box->button_status->hovered) {
				SSL_Image_Draw(check_box->button_image_info->image, check_box->button->position.x, check_box->button->position.y, 0,check_box->button_image_info->hovered_frame, SDL_FLIP_NONE, window);
			} else {
				SSL_Image_Draw(check_box->button_image_info->image, check_box->button->position.x, check_box->button->position.y, 0,check_box->button_image_info->default_frame, SDL_FLIP_NONE, window);
			}
		} else {
			image_button = SSL_List_Get(interface->buttons, i);

			if (image_button->button_status->pressed) {
				SSL_Image_Draw(image_button->button_image_info->image, image_button->button->position.x, image_button->button->position.y, 0,image_button->button_image_info->pressed_frame, SDL_FLIP_NONE, window);
			} else if (image_button->button_status->hovered) {
				SSL_Image_Draw(image_button->button_image_info->image, image_button->button->position.x, image_button->button->position.y, 0,image_button->button_image_info->hovered_frame, SDL_FLIP_NONE, window);
			} else {
				SSL_Image_Draw(image_button->button_image_info->image, image_button->button->position.x, image_button->button->position.y, 0,image_button->button_image_info->default_frame, SDL_FLIP_NONE, window);
			}
		}
	 i++;
	}
}


/*!--------------------------------------------------------------------------
|  @brief    Updates all gui elements on the interface.
|  @param    interface         Interface to update
|  @param    event    		   The SDL_Event queue to update them with.
|  @return void
|
|  interface all gui elements on the interface. TODO: Clean Up
|
\-----------------------------------------------------------------------------*/
void interface_update(SSL_Interface *interface, SDL_Event event) {
	SSL_Text_Button *button;

	int i = 1;
	int x = event.button.x;
	int y = event.button.y;

	while (SSL_List_Get(interface->buttons, i) != (void *)-1) {

		button = SSL_List_Get(interface->buttons, i);

		if (( x > button->button->position.x ) && ( x < button->button->position.x + button->button->position.w ) && ( y > button->button->position.y ) && ( y < button->button->position.y + button->button->position.h )) {
				button->button_status->hovered = 1;
		} else {
				button->button_status->hovered = 0;
		}

		if (event.type == SDL_MOUSEBUTTONUP) {
			if(event.button.button == SDL_BUTTON_LEFT) {						// Left Button
				button->button_status->pressed = 0;

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

		if (event.type == SDL_MOUSEBUTTONDOWN || button->button_status->pressed == 1) {
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
		}

		if (button->button->type == CHECK_BOX && button->button_status->clicked) {
			SSL_Check_box *box = SSL_List_Get(interface->buttons, i);
			box->check_box_status->active = !box->check_box_status->active;
			button->button_status->pressed = 0;
			button->button_status->hovered = 0;
			button->button_status->clicked = 0;
		}
	 i++;
	}
}


/*!--------------------------------------------------------------------------
|  @brief    Destroys the SSL_Interface Object.
|  @param    image      The SSL_Interface object to destroy.
|  @return 	 1 on success else 0.
|
|  Destroys the SSL_Interface object.
|
|  If it cannot destroy the object it will return 0.
\-----------------------------------------------------------------------------*/
int SSL_Interface_Destroy(SSL_Interface *interface) {
	free(interface);

	return 1;
}
