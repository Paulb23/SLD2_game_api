/*-------------------------------------------------------------------------*/
/**
   @file    SSL_Font.c
   @author  P. Batty
   @brief   Implements a TTF_Font lading and drawing.

   This module implements a simple font object, a structure containing a
   TTF_Font, which will be used where ever font is needed.
*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "SSL_window.h"
#include "SSL_Font.h"
#include "../misc/SSL_Logger.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include <stdlib.h>
#include <string.h>


/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief    Creates memory for the font ( INTERNAL USE ONLY )
  @return 	 A Empty font object

  Allocates memory for a font

\-----------------------------------------------------------------------------*/
static SSL_Font *create_memory() {

	/* Allocate memory */
	SSL_Font *font = malloc(sizeof(SSL_Font));

	/* return if failed allocation */
	if (!font) {
		SSL_Log_Write("Failed to allocate memory, loading font! ");
		return 0;
	}

 return font;
}


/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
   @brief	 Creates a new SSL_Font object.
   @param    file         The path to the font including file name.extention.
   @param    size         The font size.
   @param	 type		  The format of the font
   @param	 window		 The window render to use
   @return 	 A pointer to a SDL_Font on successful creation otherwise 0.

   Creates a new SSL_Font object with allocated memory destroy with
   SSL_Font_Destroy.

   If it cannot create the object it will return 0

\-----------------------------------------------------------------------------*/
SSL_Font *SSL_Font_Load(char *file, int size, SSL_Font_Type type, SSL_Window *window) {

	/* Allocate memory */
	SSL_Font *font = create_memory();

	/* return if failed allocation */
	if (!font) {
		return 0;
	}

	/* set the type */
	font->type = type;

	/* set the size */
	font->font_size = size;

	/* load the font */
	font->font = TTF_OpenFont(file, size);

	/* return the font */
	return font;
}


/*!--------------------------------------------------------------------------
  @brief	 Creates a new SSL_Font object.
  @param    file         	The path to the font including file name.extention.
  @param    size         	The font size.
  @param	char_width	 	width of each character
  @param	char_height	 	height of each character
  @param	character_set 	The characters on the image in the order they appear
  @param	window			The window render to use
  @return 	 A pointer to a SDL_Font on successful creation otherwise 0.

  Creates a new SSL_Font object with allocated memory destroy with
  SSL_Font_Destroy.

  If it cannot create the object it will return 0

\-----------------------------------------------------------------------------*/
SSL_Font *SSL_IMG_Font_Load(char *file, int size, int char_width, int char_height, char *character_set, SSL_Window *window) {

	/* Allocate memory */
	SSL_Font *font = create_memory();

	/* return if failed allocation */
	if (!font) {
		return 0;
	}

	/* set the type */
	font->type = SSL_FONT_IMG;

	/* set the character set */
	font->character_set = character_set;

	/* set the size */
	font->font_size = size;

	/* load the image */
	font->img_font = SSL_Image_Load(file, char_width, char_height, window);

	/* return the font */
	return font;
}


/*!--------------------------------------------------------------------------
  @brief    Draws an SSL_Font object to the window.
  @param    x   		  X position on the window to draw.
  @param    y  		  Y position on the window to draw.
  @param    angle        Angle to draw the image at, 0 - 360.
  @param    flip         Flip state of the image, one of the following:
								:: SDL_FLIP_NONE :: SDL_FLIP_HORIZONTAL :: SDL_FLIP_VERTICAL
  @param	 text		  The text to draw.
  @param    font         The SSL_Font object to draw.
  @param    fontColor    The SDL_Color representing the color of the text.
  @param    window       The SSL_Window object to draw the SSL_Font too.
  @return 	 void

  Draws an SSL_Font to the SSL_Window passed.

------------------------------------------------------------------------------*/
void SSL_Font_Draw(int x, int y, int angle, SDL_RendererFlip flip, char *text, SSL_Font *font, SDL_Color fontColor, SSL_Window *window) {

	switch (font->type) {
		case (SSL_FONT_TTF): {
			/* create the font texture */
				SDL_Surface *textSurface = TTF_RenderText_Solid(font->font, text, fontColor);
				SDL_Texture *textTexture = SDL_CreateTextureFromSurface(window->renderer, textSurface);

				/* check that it's valid */
				if (SDL_QueryTexture(textTexture, NULL, NULL, &textSurface->w, &textSurface->h) != 0) {
					SSL_Log_Write("Failed to create font texture! ");
					return;
				} else {

					/* rectangle to hold the position */
					SDL_Rect offset;
						offset.x = x;
						offset.y = y;
						offset.w = textSurface->w;
						offset.h = textSurface->h;

					/* draw the text */
					SDL_RenderCopyEx( window->renderer, textTexture, NULL, &offset, angle, NULL, flip);
				}

				/* DO NOT REMOVE STOPS MEMORY LEAK */
				SDL_FreeSurface(textSurface);
				SDL_DestroyTexture(textTexture);
		}
		break;
		case (SSL_FONT_IMG): {
			int x_inc = font->img_font->frame_width;
			int i;
			int total_char_count = strlen(font->character_set);
			int char_count = strlen(text);

			for (i = 0; i < char_count; i++) {
				int j;
				int frame = 0;
				for (j = 0; j < total_char_count; j++) {
					if (text[i] == font->character_set[j]) {
						frame = j;
						frame++;
					}
				}

				if (frame != 0) {
					SSL_Image_Draw(font->img_font, x, y, angle, frame, flip, window);
					x += x_inc + (x_inc / 4);
				}
			}
		}
		break;
	}
}

/*!--------------------------------------------------------------------------
   @brief    Destroys the SSL_Font Object.
   @param    font      The SSL_Font object to destroy.
   @return 	 1 on success else 0.

   Destroys the SSL_Font object.

   If it cannot destroy the object it will return 0.
\-----------------------------------------------------------------------------*/
int SSL_Font_Destroy(SSL_Font *font) {
	switch (font->type) {
		case (SSL_FONT_TTF): {
			 free(font->font);
		}
		break;
		case (SSL_FONT_IMG): {
			SSL_Image_Destroy(font->img_font);
		}
		break;
	}
	free(font);

 return 1;
}

