#include "SSL_Tiled.h"
#include "../misc/SSL_Hashmap.h"
#include "../graphics/SSL_Image.h"
#include "../graphics/SSL_Window.h"
#include <stdlib.h>
#include <string.h>
#include "mxml/mxml.h"
#include "base64.h"
#include "zlib.h"
#include "zconf.h"

SSL_Tiled_Map *SSL_Tiled_Map_Load(SSL_Window *window) {
	SSL_Tiled_Map *map = malloc(sizeof(SSL_Tiled_Map));
	map->map = malloc(sizeof(SSL_Map));
	map->tileset = malloc(sizeof(SSL_Tileset));
	map->tileset->amount = 0;
	map->tileset->tilesets = SSL_Hashmap_Create();
	map->tileset->tiles = SSL_Hashmap_Create();

	FILE *fp;
	mxml_node_t *tree, *node;

	fp = fopen("../extras/resources/map.tmx", "r");
	if (fp == NULL) {
		printf("What!");
	}
	tree = mxmlLoadFile(NULL, fp, MXML_TEXT_CALLBACK );
	fclose(fp);

	if (!tree) {
		printf("Hey!");
	}
	node = mxmlFindElement(tree, tree, "map", NULL, NULL, MXML_DESCEND);
	map->map->version = mxmlElementGetAttr(node, "version");
	map->map->orientation = mxmlElementGetAttr(node, "orientation");
	map->map->map_width = atoi(mxmlElementGetAttr(node, "width"));
	map->map->map_height = atoi(mxmlElementGetAttr(node, "height"));
	map->map->tile_width = atoi(mxmlElementGetAttr(node, "tilewidth"));
	map->map->tile_height = atoi(mxmlElementGetAttr(node, "tileheight"));
	map->layer = SSL_Hashmap_Create();

	node = mxmlFindElement(node, tree, "tileset", NULL, NULL, MXML_DESCEND);
	tree = node;

	SSL_Tileset_Info *curr_tileset;
	SSL_Tile *curr_tile;
	const char *curr_layer;
	while (node != NULL) {

		if ( mxmlGetType(node) == MXML_ELEMENT) {

		      if (!strcmp(node->value.element.name, "tileset")) {
		  		SSL_Tileset_Info *tileset = malloc(sizeof(SSL_Tileset_Info));

		  		tileset->firstGid = mxmlElementGetAttr(node, "firstgid");
		  		tileset->name = mxmlElementGetAttr(node, "name");
		  		tileset->tile_width = atoi(mxmlElementGetAttr(node, "tilewidth"));
		  		tileset->tile_height = atoi(mxmlElementGetAttr(node, "tileheight"));
		  		tileset->spacing = atoi(mxmlElementGetAttr(node, "spacing"));
		  		tileset->margin = atoi(mxmlElementGetAttr(node, "margin"));

		  		SSL_Hashmap_Add(map->tileset->tilesets, tileset->firstGid, tileset);

		  		curr_tileset = tileset;
		  		curr_tile = NULL;
		      } else if (!strcmp(node->value.element.name, "image")) {
			  		curr_tileset->image = SSL_Image_Load(mxmlElementGetAttr(node, "source"), map->map->tile_width,map->map->tile_height, window);
		      } else if (!strcmp(node->value.element.name, "tile")) {
		    	  SSL_Tile *tile = malloc(sizeof(SSL_Tile));

		    	  tile->id = atoi(mxmlElementGetAttr(node, "id"));
		    	  tile->properties = SSL_Hashmap_Create();

		    	  curr_tile = tile;
		      } else if (!strcmp(node->value.element.name, "property") && curr_tile != NULL) {
		    	  SSL_Hashmap_Add(curr_tile->properties, mxmlElementGetAttr(node, "name"), mxmlElementGetAttr(node, "value"));
		      } else if (!strcmp(node->value.element.name, "layer")) {
		    	  curr_layer =  mxmlElementGetAttr(node, "name");
		      } else if (!strcmp(node->value.element.name, "data") && curr_layer != NULL) {
		    	  char base64DecodeOutput[9999];
		    	  b64_decode((char *)mxmlGetText(node, 0), base64DecodeOutput);

		    	  int tile_map[map->map->map_width * map->map->map_height];
		    	  int (*tiles)[map->map->map_width][map->map->map_height] = malloc (sizeof(map->map->map_width*map->map->map_height));

		    	  uLongf outlen = map->map->map_width * map->map->map_height * 4;
		    	  uncompress((Bytef *)tile_map, &outlen, (const Bytef *)base64DecodeOutput, strlen(base64DecodeOutput));


		    	  int k = 0;
		    	  int i, j;
		    	  for ( i = 0; i < map->map->map_width;i++)
		    	  {
		    	      for ( j = 0; j < map->map->map_height;j++)
		    	      {
		    	    	  (*tiles)[i][j] = tile_map[k++];
		    	      }

		    	  }

		    	 SSL_Hashmap_Add(map->layer, curr_layer, (*tiles));
		    	 curr_layer = NULL;
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


void SSL_Tiled_Draw_Map(SSL_Tiled_Map *map, SSL_Window *window) {
	int (*tiles)[map->map->map_width][map->map->map_height];
	tiles = map->layer->next->value;
	SSL_Tileset_Info *tileset = map->tileset->tilesets->next->value;

	SSL_Hashmap * curr = map->layer->next;
	int i, j;
	while (curr != 0) {
		tiles = curr->value;

		for (i = 0; i <map->map->map_width; i++) {
		  for (j = 0; j <map->map->map_height; j++) {
				SSL_Image_Draw(tileset->image, i * map->map->tile_width, j*map->map->tile_height,0,(*tiles)[j][i],SDL_FLIP_NONE, window);
			}
		 }

		curr = curr->next;
	}
}
