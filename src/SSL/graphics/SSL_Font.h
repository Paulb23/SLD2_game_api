/*-------------------------------------------------------------------------*/
/**
   @file    SSL_Font.h
   @author  P. Batty
   @brief   Implements a TTF_Font lading and drawing.

   This module implements a simple font object, a structure containing a
   TTF_Font, which will be used where ever font is needed.
*/
/*--------------------------------------------------------------------------*/

#ifndef SDL_FONT_H_
#define SDL_FONT_H_


/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "SDL2/SDL_ttf.h"
#include "SSL_Image.h"


/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief    SSL_Font_Type

  This object contains the different types of supported Font format.

  The SSL Font type is used by the library to decide how to handle the font
  object

\----------------------------------------------------------------------------*/
typedef enum _SSL_Font_Type {
	SSL_FONT_INVALID,	/**< invalid TTF font */
	SSL_FONT_TTF,		/**< standard TTF font */
	SSL_FONT_IMG,		/**< straight image font */
	SSL_FONT_FNT		/**< .fnt font */
} SSL_Font_Type;


typedef struct _SSL_IMG_Font_ {
	char *character_set;
	SSL_Image *font;
} SSL_IMG_Font;


typedef struct _SSL_FNT_Font_ {
	SSL_Image *font;
} SSL_FNT_Font;


/*!--------------------------------------------------------------------------
  @brief    SSL_Font

  This object contains a TTF_Font.

  The SSL Font object is used by the library where it will need to draw text.

\----------------------------------------------------------------------------*/
typedef struct _SSL_Font_ {
	SSL_Font_Type type;		 /**< The Type of font */
	int font_size;
	union {
		TTF_Font *font;			 /**< TTF_Font */
		SSL_IMG_Font img_font;	 /**< img font */
		SSL_FNT_Font fnt_font;	 /**< fnt font */
	};
} SSL_Font;


/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief	 Creates a new SSL_Font object.
  @param    file         The path to the font including file name.extention.
  @param    size         The font size.
  @param	window		 The window render to use
  @return 	 A pointer to a SDL_Font on successful creation otherwise 0.

  Creates a new SSL_Font object with allocated memory destroy with
  SSL_Font_Destroy.

  If it cannot create the object it will return 0

\-----------------------------------------------------------------------------*/
SSL_Font *SSL_Font_Load(char *file, int size, SSL_Window *window);


/*!--------------------------------------------------------------------------
  @brief	 Creates a new SSL_Font object.
  @param    file         	The path to the font including file name.extention.
  @param    size         	The font size.
  @param	char_width	 	width of each character
  @param	char_height	 	height of each character
  @param	character_set 	The characters on the image in the order they appear
  @param	window			The window render to use
  @return 	A pointer to a SDL_Font on successful creation otherwise 0.

  Creates a new SSL_Font object with allocated memory destroy with
  SSL_Font_Destroy.

  If it cannot create the object it will return 0

\-----------------------------------------------------------------------------*/
SSL_Font *SSL_IMG_Font_Load(char *file, int size, int char_width, int char_height, char *character_set, SSL_Window *window);


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

\-----------------------------------------------------------------------------*/
void SSL_Font_Draw(int x, int y, int angle, SDL_RendererFlip flip, char *text, SSL_Font *font, SDL_Color fontColor, SSL_Window *window);


/*!--------------------------------------------------------------------------
  @brief    Destroys the SSL_Font Object.
  @param    font      The SSL_Font object to destroy.
  @return 	 1 on success else 0.

  Destroys the SSL_Font object.

  If it cannot destroy the object it will return 0.
\-----------------------------------------------------------------------------*/
int SSL_Font_Destroy(SSL_Font *font);

#endif
