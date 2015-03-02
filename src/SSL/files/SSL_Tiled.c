/*-------------------------------------------------------------------------*/
/**
   @file    SSL_Tiled.c
   @author  P. Batty
   @brief   Implements a Tiled .tmx map handler

   This module implements a way to load access and draw .tmx maps
*/
/*--------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "SSL_Tiled.h"
#include "../SSL_Settings.h"
#include "../data_structures/SSL_Hashmap.h"
#include "../graphics/SSL_Image.h"
#include "../data_structures/SSL_List.h"
#include "../misc/SSL_Logger.h"
#include "../misc/SSL_String.h"

#include "../math/SSL_Math.h"

#include "../graphics/SSL_Window.h"
#include "../graphics/SSL_Light.h"
#include "../wrappers/SSL_Rectangle.h"
#include "../wrappers/SSL_Color.h"
#include <stdlib.h>
#include <string.h>
#include "../ect/mxml/mxml.h"
#include "../misc/base64.h"
#include "zlib.h"
#include "zconf.h"
#include <math.h>

/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/

static SSL_Tiled_Map *SSL_Tiled_Map_Create() {
	SSL_Tiled_Map *map = malloc(sizeof(SSL_Tiled_Map));

	if (!map) {
		SSL_Log_Write("Failed to allocate memory for new map!");
		free(map);
		return 0;
	}

	map->map.properties = SSL_Hashmap_Create();
	map->layers = SSL_List_Create();
	map->tilesets = SSL_List_Create();
	map->lights = SSL_List_Create();
	SDL_Color color = {0,0,0,0};
	map->color = color;

	return map;
}

static void map_properties_handler(mxml_node_t *node, SSL_Tiled_Map *map) {
		map->map.version = mxmlElementGetAttr(node, "version");
		map->map.orientation = mxmlElementGetAttr(node, "orientation");
		map->map.map_width = atoi(mxmlElementGetAttr(node, "width"));
		map->map.map_height = atoi(mxmlElementGetAttr(node, "height"));
		map->map.tile_width = atoi(mxmlElementGetAttr(node, "tilewidth"));
		map->map.tile_height = atoi(mxmlElementGetAttr(node, "tileheight"));
		map->map.total_layers = 0;
		map->map.total_tilesets = 0;

		// load properties function
}

static void map_tileset_handeler(mxml_node_t *node, SSL_Tiled_Map *map, char *filePath, SSL_Window *window) {
		SSL_Tileset *tileset = malloc(sizeof(SSL_Tileset));

		if(!tileset) {
			SSL_Log_Write("ERROR: Unable to create memory for tileset! ");
			return;
		}

		tileset->firstGid = atoi(mxmlElementGetAttr(node, "firstgid"));
		tileset->name = mxmlElementGetAttr(node, "name");
		tileset->tile_width = atoi(mxmlElementGetAttr(node, "tilewidth"));
		tileset->tile_height = atoi(mxmlElementGetAttr(node, "tileheight"));
		tileset->spacing = atoi(mxmlElementGetAttr(node, "spacing"));
		tileset->margin = atoi(mxmlElementGetAttr(node, "margin"));

		// TODO: Get size of for allocation
		char path[9999];
		sprintf(path, "%s%s", filePath, mxmlElementGetAttr(node->child->next, "source"));
		tileset->image =  SSL_Image_Load(path, map->map.tile_width,map->map.tile_height, window);

		tileset->tiles = SSL_List_Create();
		tileset->properties = SSL_Hashmap_Create();

		//load properties function

		SSL_List_Add(map->tilesets, tileset);
		map->map.total_tilesets++;
}

static void map_tile_layer_handeler(mxml_node_t *node, SSL_Tiled_Map *map) {
	SSL_Tile_Layer *layer = malloc(sizeof(SSL_Tile_Layer));

	if(!layer) {
		SSL_Log_Write("ERROR: Unable to create memory for map layer! ");
		return;
	}

	layer->name = mxmlElementGetAttr(node, "name");
	layer->width = atoi(mxmlElementGetAttr(node, "width"));
	layer->height = atoi(mxmlElementGetAttr(node, "height"));
	layer->opacity = atoi(mxmlElementGetAttr(node, "opacity"));

	if(mxmlElementGetAttr(node, "visible") == NULL || strcmp(mxmlElementGetAttr(node, "visible"), "1") == 0) {
		layer->visible = 1;
	} else {
		layer->visible = 0;
	}

	mxml_node_t *data;
	data = mxmlFindElement(node, node, "data", NULL, NULL, MXML_DESCEND);

	int *tile_map = malloc(map->map.map_width * map->map.map_height * 4);
	memset(tile_map, 0, map->map.map_width * map->map.map_height * 4);

	if (mxmlElementGetAttr(node, "encoding") == NULL) {
		int tiles[map->map.map_width * map->map.map_height * 4];
		mxml_node_t * tile = mxmlFindElement(node, node, "tile",NULL, NULL,MXML_DESCEND);

		int l = 0;
		while(tile != NULL) {
			if(mxmlGetType(tile) == MXML_ELEMENT) {
			     tiles[l] = atoi(mxmlElementGetAttr(tile, "gid"));
			     l++;
			}
		 tile = mxmlWalkNext(tile, data, MXML_NO_DESCEND);
		}

		int i, j;
		l = 0;
		for (i=0;i<layer->height;i++){
			for (j=0;j<layer->width;j++){
				tile_map[map->map.map_width * i + j] = tiles[l++];
			}
		}
	} else {
		//TODO: Get size of allocation
		char base64DecodeOutput[9999];
		b64_decode((char *)mxmlGetText(data, 0), base64DecodeOutput);

		uLongf outlen = map->map.map_width * map->map.map_height * 4;
		uncompress((Bytef *)tile_map, &outlen, (const Bytef *)base64DecodeOutput, strlen(base64DecodeOutput));
	}

	layer->data = tile_map;

	layer->properties = SSL_Hashmap_Create();

	// load tile properties

	SSL_List_Add(map->layers, layer);
	map->map.total_layers++;
}



static int SSL_Tiled_Get_Tile_FrameNumber(SSL_Tiled_Map *map, int tile_id) {
	 SSL_Tileset *tileset;
	 int k;
	 if (map->map.total_tilesets != 1) {
		 for (k = 0; k < SSL_List_Size(map->tilesets)-1; k++) {
			 tileset = SSL_List_Get(map->tilesets, k+1);
			 if (tile_id < tileset->firstGid || tileset == NULL) {
				 tileset = SSL_List_Get(map->tilesets, k);
				 break;
			 }
		 }
	 } else {
		 k = 0;
		 tileset = SSL_List_Get(map->tilesets, k);
	 }
	 int frame = 1;

	 if (k != 0) {
		 frame = tile_id - (tileset->firstGid - 1);
	 } else {
		 frame = tile_id;
	 }

 return frame;
}


/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/


/*!--------------------------------------------------------------------------
  @brief    Loads and creates new Tiled map
  @param    file		 the path to the file
  @param    window       The renderer to use
  @return A SSL_Tiled_Map object

  Loads and creates new Tiled map.
  Destroy with SSL_Tiled_Map_Destroy.

\-----------------------------------------------------------------------------*/
SSL_Tiled_Map *SSL_Tiled_Map_Load(const char *file,  SSL_Window *window) {

	/* create the map */
	SSL_Tiled_Map *map = SSL_Tiled_Map_Create();
	if(map == 0) {
		return 0;
	}

	/* open the file */
	FILE *fp = fopen(file, "r");
	if (fp == NULL) {
		SSL_Log_Write("Failed to find file!");
		SSL_Tiled_Map_Destroy(map);
		return 0;
	}

	mxml_node_t *tree, *node;
	tree = mxmlLoadFile(NULL, fp, MXML_TEXT_CALLBACK );
	fclose(fp);

	if (!tree) {
		SSL_Log_Write("Failed to find file!");
		SSL_Tiled_Map_Destroy(map);
		return 0;
	}

	/* load the map properties */
	node = mxmlFindElement(tree, tree, "map", NULL, NULL, MXML_DESCEND);
	map_properties_handler(node, map);
	tree = node;

	while (node != NULL) {
		if ( mxmlGetType(node) == MXML_ELEMENT) {

			 if (!strcmp(node->value.element.name, "tileset")) {
				 map_tileset_handeler(node, map, SSL_String_Substring(file, 0, SSL_String_Last_Index_Of(file, "/")), window);
		      } else if (!strcmp(node->value.element.name, "layer")) {
			 	  map_tile_layer_handeler(node, map);
		      }
		}
		mxml_node_t* next = mxmlGetFirstChild(node);
		if ( next != NULL ) {
		      node = next;
		} else {
		    next = mxmlGetNextSibling(node);
		    if ( next != NULL ) {
		    	node = next;
			} else {
				next = mxmlGetNextSibling(node->parent);
				if( next != NULL) {
					node = next;
				} else {
					node = mxmlGetNextSibling(tree);
					tree = node;
				}
			}
		}
	}

	return map;
}


/*!--------------------------------------------------------------------------
  @brief    Draws a loaded map to the screen
  @param    map			 the map to draw
  @param    xOffset		 X Offset to draw the map
  @param    yOffset		 y Offset to draw the map
  @param    window       The window to draw to
  @return Void

  Draws the map to the given window.

\-----------------------------------------------------------------------------*/
void SSL_Tiled_Draw_Map(SSL_Tiled_Map *map, int xOffset, int yOffset, SSL_Window *window) {

	int layer = 0;
	int *tiles;

	int i, j;
	while (layer < map->map.total_layers) {
		SSL_Tile_Layer *tile_layer = SSL_List_Get(map->layers, layer);

		if (tile_layer->visible != 0) {

			tiles = tile_layer->data;

			int width = 0;
			int height = 0;
			SDL_GetWindowSize(window->window, &width, &height);
			int startX = abs(xOffset / SSL_Tiled_Get_Tile_Width(map));
			int startY = abs(yOffset / SSL_Tiled_Get_Tile_Height(map));
			if (xOffset / SSL_Tiled_Get_Tile_Width(map) > 0) {
				startX = 0;
			}
			if (yOffset / SSL_Tiled_Get_Tile_Height(map) > 0) {
				startY = 0;
			}

			width = (width / map->map.tile_width) + startX;
			if (width > SSL_Tiled_Get_Width(map)) {
				width = SSL_Tiled_Get_Width(map);
			}

			height = (height / map->map.tile_height) + startY;
			if (height > SSL_Tiled_Get_Height(map)) {
				height = SSL_Tiled_Get_Height(map);
			}

			for (i = startX; i <= width + 1; i++) {
				for (j = startY; j <= height + 1; j++) {
					if (tiles[map->map.map_width * j + i] != 0 && j < SSL_Tiled_Get_Height(map) && i < SSL_Tiled_Get_Width(map)) {

						 SSL_Tileset *tileset;
						 int k;
						 if (map->map.total_tilesets != 1) {
							 for (k = 0; k < SSL_List_Size(map->tilesets)-1; k++) {
								 tileset = SSL_List_Get(map->tilesets, k+1);
								 if (tiles[map->map.map_width * j + i] < tileset->firstGid || tileset == NULL) {
									 tileset = SSL_List_Get(map->tilesets, k);
									 break;
								 }
							 }
						 } else {
							 k = 0;
							 tileset = SSL_List_Get(map->tilesets, k);
						 }
						 int frame = 1;

						 if (k != 0) {
							 frame = tiles[map->map.map_width * j + i] - (tileset->firstGid - 1);
						 } else {
							 frame = tiles[map->map.map_width * j + i];
						 }
						 SSL_Image_Draw(tileset->image, i * map->map.tile_width + xOffset, j*map->map.tile_height + yOffset,0,frame ,SDL_FLIP_NONE, window);
					}
				}
			}
		}
		layer++;
	}
}


/*!--------------------------------------------------------------------------
  @brief    Draws a lights on the map
  @param    map			 the map to draw
  @param    xOffset		 X Offset to draw the map
  @param    yOffset		 y Offset to draw the map
  @param    window       The window to draw to
  @param	func		 The raytrace callback function to determine what's solid
  @return Void

  Draws the lights on the map

\-----------------------------------------------------------------------------*/
void SSL_Tiled_Draw_Lights(SSL_Tiled_Map *map, int xOffset, int yOffset, SSL_Window *window, int(*func)(int, int, void *)) {
	int i, j, k;

	int tile_width = map->map.tile_width;
	int tile_height = map->map.tile_height;

	float light_map[map->map.map_width][map->map.map_height];
	memset(light_map, 0, sizeof(float) * map->map.map_width * map->map.map_height);

	int width = 0;
	int height = 0;
	SDL_GetWindowSize(window->window, &width, &height);
	int startX = abs(xOffset / SSL_Tiled_Get_Tile_Width(map));
	int startY = abs(yOffset / SSL_Tiled_Get_Tile_Height(map));
	if (xOffset / SSL_Tiled_Get_Tile_Width(map) > 0) {
		startX = 0;
	}
	if (yOffset / SSL_Tiled_Get_Tile_Height(map) > 0) {
		startY = 0;
	}

	width = (width / map->map.tile_width) + startX;
	if (width > SSL_Tiled_Get_Width(map)) {
		width = SSL_Tiled_Get_Width(map);
	}

	height = (height / map->map.tile_height) + startY;
	if (height > SSL_Tiled_Get_Height(map)) {
		height = SSL_Tiled_Get_Height(map);
	}

	SDL_Color c = SSL_Color_Create(0, 0, 0, 0);
	SDL_GetRenderDrawColor(window->renderer, &c.r, &c.g, &c.b, &c.a);
	SDL_SetRenderDrawBlendMode(window->renderer, SDL_BLENDMODE_MOD);
	for (k = 0; k < SSL_List_Size(map->lights); k++) {
		SSL_Light *light = SSL_List_Get(map->lights, k);
		int x = (light->x / map->map.tile_width);
		int y = (light->y / map->map.tile_height);

		for (i = startX; i <= width + 1; i++) {
			for (j = startY; j <= height + 1; j++) {
				int x1 = i-x;
				int y1 = j-y;
				int l = sqrt(x1*x1+y1*y1);
				if (l < light->range && SSL_Raytrace(x * tile_width, y * tile_height, i * tile_width, j * tile_height, map, func) == 0) {
					light_map[i][j] = 1;
				}


				if (light_map[i][j] == 1) {
					SDL_SetRenderDrawColor(window->renderer, light->color.r, light->color.g, light->color.b, light->color.a);
					SDL_Rect rect = SSL_Rectangle_Create(i * tile_width + xOffset, j * tile_height + yOffset, tile_width, tile_height);
					SDL_RenderFillRect(window->renderer, &rect);
					light_map[i][j] = -1;
				}
			}
		}
	}

	SDL_SetRenderDrawBlendMode(window->renderer, SDL_BLENDMODE_BLEND);

	for (i = startX; i <= width + 1; i++) {
		for (j = startY; j <= height + 1; j++) {
			if (light_map[i][j] == 0) {
				SDL_SetRenderDrawColor(window->renderer, map->color.r, map->color.g, map->color.b, map->color.a);
				SDL_Rect rect = SSL_Rectangle_Create(i * tile_width + xOffset, j * tile_height + yOffset, tile_width, tile_height);
				SDL_RenderFillRect(window->renderer, &rect);
			}
		}
	}

	SDL_SetRenderDrawColor(window->renderer, c.r, c.g, c.b, c.a);
}


/*!--------------------------------------------------------------------------
  @brief    Adds a light object to the map
  @param    map			 map to add the light to
  @param	light		 SSL_Light to add
  @return Void

  Adds a light object to the map

\-----------------------------------------------------------------------------*/
void SSL_Tiled_Add_Light(SSL_Tiled_Map *map, SSL_Light *light) {
	SSL_List_Add(map->lights, light);
}


/*!--------------------------------------------------------------------------
  @brief    Changes the Lighting
  @param    map			 map to change the lighting on
  @param	color		 the lighting to change to
  @return Void

  Changes the defualt lighting color

\-----------------------------------------------------------------------------*/
void SSL_Tiled_Set_Lighting(SSL_Tiled_Map *map, SDL_Color color) {
	map->color = color;
}


/*!--------------------------------------------------------------------------
  @brief    Gets a SSL_Tileset
  @param    map			 map containing the tileset
  @param    gid			 gid of the tile set to get
  @return A SLL_Tileset object else -1

  Gets a SSL_Tileset object from the SSL_Map with the given gid else -1

\-----------------------------------------------------------------------------*/
SSL_Tileset *SSL_Tiled_Get_Tileset(SSL_Tiled_Map *map, int gid) {
	int i;
	for (i = 0; i < map->map.total_tilesets; i++) {
		SSL_Tileset *tileset = SSL_List_Get(map->tilesets, i);
		if (tileset->firstGid == gid) {
			return tileset;
		}
	}
	return (void*)-1;
}


/*!--------------------------------------------------------------------------
  @brief    Gets the map height in tiles
  @param    map			 map to get the height of
  @return Map height in tiles

  Map height in tiles

\-----------------------------------------------------------------------------*/
unsigned int SSL_Tiled_Get_Height(SSL_Tiled_Map *map) {
	return map->map.map_height;
}


/*!--------------------------------------------------------------------------
  @brief    Gets the map width in tiles
  @param    map			 map to get the width of
  @return Map width in tiles

  Map width in tiles

\-----------------------------------------------------------------------------*/
unsigned int SSL_Tiled_Get_Width(SSL_Tiled_Map *map) {
	return map->map.map_width;
}


/*!--------------------------------------------------------------------------
  @brief    Gets the map height in pixels
  @param    map			 map to get the height of
  @return Map height in pixels

  Map height in pixels

\-----------------------------------------------------------------------------*/
int SSL_Tiled_Get_Height_px(SSL_Tiled_Map *map) {
	return map->map.map_height * map->map.tile_height;
}


/*!--------------------------------------------------------------------------
  @brief    Gets the map width in pixels
  @param    map			 map to get the width of
  @return Map width in pixels

  Map width in pixels

\-----------------------------------------------------------------------------*/
int SSL_Tiled_Get_Width_px(SSL_Tiled_Map *map) {
	return map->map.map_height * map->map.tile_width;
}


/*!--------------------------------------------------------------------------
  @brief    Gets the tile width in pixels
  @param    map			 map to get the tile width of
  @return Tile width in pixels

  Tile width in pixels

\-----------------------------------------------------------------------------*/
int SSL_Tiled_Get_Tile_Width(SSL_Tiled_Map *map) {
	return map->map.tile_width;
}


/*!--------------------------------------------------------------------------
  @brief    Gets the tile height in pixels
  @param    map			 map to get the tile height of
  @return Tile height in pixels

  Tile height in pixels

\-----------------------------------------------------------------------------*/
int SSL_Tiled_Get_Tile_Height(SSL_Tiled_Map *map) {
	return map->map.tile_height;
}


/*!--------------------------------------------------------------------------
  @brief    Gets the number of layers in the map
  @param    map			 map to get the number of layers
  @return Number of layers

  Number of layers

\-----------------------------------------------------------------------------*/
int SSL_Tiled_Get_Layercount(SSL_Tiled_Map *map) {
	return map->map.total_layers;
}


/*!--------------------------------------------------------------------------
  @brief    Gets the number of tilesets in the map
  @param    map			 map to get the number of tilesets
  @return Number of tilesets

  Number of tilesets

\-----------------------------------------------------------------------------*/
int SSL_Tiled_Get_Tileset_Count(SSL_Tiled_Map *map) {
	return map->map.total_tilesets;
}


/*!--------------------------------------------------------------------------
  @brief    Gets the tile id at the location specified
  @param    map			 map to get the number of tile id from
  @param	x			 x position of the tile
  @param	y			 y position of the tile
  @param	layer_index	 layer number position of the tile
  @return tile id at the location specified

  Tile id at the location specified

\-----------------------------------------------------------------------------*/
int SSL_Tiled_Get_TileId(SSL_Tiled_Map *map, int x, int y, int layer_index) {
	SSL_Tile_Layer *layer = SSL_List_Get(map->layers, layer_index);

	if (layer != (void *)-1) {
		int *tiles = layer->data;

		return SSL_Tiled_Get_Tile_FrameNumber(map, tiles[map->map.map_width * y + x]);
	}

	return -1;
}


/*!--------------------------------------------------------------------------
  @brief    Gets the layer index on the map
  @param    map			 map to get the number of layer index from
  @param	name		 name of the layer
  @return layer index of the given layer name else -1

  Layer index of the given layer name else -1

\-----------------------------------------------------------------------------*/
int SSL_Tiled_Get_LayerIndex(SSL_Tiled_Map *map, char *name) {
	int i;
	for (i =0; i < map->map.total_layers; i++) {
		SSL_Tile_Layer *layer = SSL_List_Get(map->layers, i);
		if (strcmp(layer->name, name) == 0) {
			return i;
		}
	}
	return -1;
}


/*!--------------------------------------------------------------------------
  @brief    Removes a light from the map
  @param    map			 map to remove the light from
  @param	light		 The light to remove
  @return Void

  Removes a light from the map

\-----------------------------------------------------------------------------*/
void SSL_Tiled_Remove_Light(SSL_Tiled_Map *map, SSL_Light *light) {
	SSL_List_Remove(map->lights, light);
}


/*!--------------------------------------------------------------------------
  @brief    Gets the light on the map
  @param    map			 map to get the light from
  @param	n			 nth position of the light
  @return The SSL_Light else -1

  Gets the light on the map and return is else -1

\-----------------------------------------------------------------------------*/
SSL_Light *SSL_Tiled_Get_Light(SSL_Tiled_Map *map, int n) {
	if (n >= 0 && n < SSL_List_Size(map->lights)) {
		return (SSL_Light *)SSL_List_Get(map-> lights, n);
	}
	return (void *)-1;
}


/*!--------------------------------------------------------------------------
  @brief    Destroys the map
  @param    map		The map to destroy
  @return   void

  Destroys the map.

\-----------------------------------------------------------------------------*/
void SSL_Tiled_Map_Destroy(SSL_Tiled_Map *map) {
	SSL_Hashmap_Destroy(map->map.properties);
	SSL_List_Destroy(map->layers);
	SSL_List_Destroy(map->tilesets);
}
