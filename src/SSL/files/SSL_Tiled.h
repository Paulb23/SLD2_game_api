/*-------------------------------------------------------------------------*/
/**
   @file    SSL_Tiled.h
   @author  P. Batty
   @brief   Implements a Tiled .tmx map handler

   This module implements a way to load access and draw .tmx maps
*/
/*--------------------------------------------------------------------------*/

#ifndef SSL_TILED_READER_H_
#define SSL_TILED_READER_H_


/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/


#include "../misc/SSL_Hashmap.h"
#include "../graphics/SSL_Image.h"


/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/


/*!--------------------------------------------------------------------------
  @brief    SSL_Map

  This object contains information about the map such as size, version ect

\----------------------------------------------------------------------------*/
typedef struct _SSL_MAP_ {
	const char *version;		/**< Map version 	 	 */
	const char *orientation;	/**< Map orientation	 */
	int map_width;			    /**< Map width in tiles  */
	int map_height;				/**< Map height in tiles */
	int tile_width;				/**< Tile width			 */
	int tile_height;			/**< Tile height		 */
} SSL_Map;


/*!--------------------------------------------------------------------------
  @brief    SSL_Tileset

  This object contains lists of the tiles and tilesets in the map

\----------------------------------------------------------------------------*/
typedef struct _SSL_Tileset_ {
	SSL_Hashmap *tilesets;			/**< The list of tilesets */
	SSL_Hashmap *tiles;				/**< The list of tiles */
} SSL_Tileset;


/*!--------------------------------------------------------------------------
  @brief    SSL_Tileset_Info

  This object contains information about the tilesets.

\----------------------------------------------------------------------------*/
typedef struct _SSL_Tileset_Info_ {
	const char  *firstGid;			/**< The id  	      */
	const char *name;				/**< The name 	      */
	int  tile_width;				/**< the tile width   */
	int  tile_height;				/**< the tile height  */
	int  spacing;				    /**< the tile spacing */
	int  margin;					/**< the tile margin  */
	SSL_Image *image;				/**< the tile image   */
} SSL_Tileset_Info;


/*!--------------------------------------------------------------------------
  @brief    SSL_Tile

  This object contains information about the tiles.

\----------------------------------------------------------------------------*/
typedef struct _SSL_Tile_ {
	int id;						/**< The id  	      				*/
	SSL_Hashmap *properties;	/**< The properties on this tile   */
} SSL_Tile;


/*!--------------------------------------------------------------------------
  @brief    SSL_Tiled_Map

  The Main object all tiled maps will be made with this object, containing all the
  information on the map stored in it.

  Destroy with SSL_Tiled_Map_Destroy.

\----------------------------------------------------------------------------*/
typedef struct _SSL_Tiled_Map_ {
	SSL_Map	    *map;				/**<  The map information */
	SSL_Tileset *tileset;			/**<  The tileset */
	SSL_Hashmap *layer;				/**<  The layers */
} SSL_Tiled_Map;


/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief    Loads and creates new Tiled map
  @param    file		 the path to the file
  @param    window       The renderer to use
  @return A SSL_Tiled_Map object

  Loads and creates new Tiled map.
  Destroy with SSL_Tiled_Map_Destroy.

\-----------------------------------------------------------------------------*/
SSL_Tiled_Map *SSL_Tiled_Map_Load(char *file, SSL_Window *window);


/*!--------------------------------------------------------------------------
  @brief    Draws a loaded map to the screen
  @param    map			 the map to draw
  @param    xOffset		 X Offset to draw the map
  @param    yOffset		 y Offset to draw the map
  @param    window       The window to draw to
  @return A SSL_Tiled_Map object

  Draws the map to the given window.

\-----------------------------------------------------------------------------*/
void SSL_Tiled_Draw_Map(SSL_Tiled_Map *map, int xOffset, int yOffset, SSL_Window *window);


/*!--------------------------------------------------------------------------
  @brief    Destroys the map
  @param    map		The map to destroy
  @return   void

  Destroys the map.

\-----------------------------------------------------------------------------*/
void SSL_Tiled_Map_Destroy(SSL_Tiled_Map *map);


#endif
