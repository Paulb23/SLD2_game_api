#include "SSL_Tiled_Reader.h"
#include "../misc/SSL_Hashmap.h"
#include "../graphics/SSL_Image.h"
#include "../graphics/SSL_Window.h"
#include <stdlib.h>
#include <string.h>
#include "mxml/mxml.h"
#include "base64.h"
#include "zlib.h"
#include "zconf.h"

void sax_cb(mxml_node_t *node, mxml_sax_event_t event, void *data) {

}

SSL_Tiled_Map *SSL_Tiled_Map_Load(SSL_Window *window) {
	SSL_Tiled_Map *map = malloc(sizeof(SSL_Tiled_Map));
	map->map = malloc(sizeof(SSL_Map));
	map->tileset = malloc(sizeof(SSL_Tileset));
	map->tileset->amount = 0;
	map->tileset->tilesets = SSL_Hashmap_Create();
	map->tileset->tiles = SSL_Hashmap_Create();

	FILE *fp;
	mxml_node_t *tree, *node, *pre, *next;

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
	map->map->map_width = (int *)mxmlElementGetAttr(node, "width");
	map->map->map_height = (int *)mxmlElementGetAttr(node, "height");
	map->map->tile_width = (int *)mxmlElementGetAttr(node, "tilewidth");
	map->map->tile_height = (int *)mxmlElementGetAttr(node, "tileheight");
	map->layer = SSL_Hashmap_Create();

	node = mxmlFindElement(node, tree, "tileset", NULL, NULL, MXML_DESCEND);
	tree = node;

	SSL_Tileset_Info *curr_tileset;
	SSL_Tile *curr_tile;
	const char *curr_layer;
	while (node != NULL) {

		if ( mxmlGetType(node) == MXML_ELEMENT) {
		      fprintf(stdout,"Element = %s\n",node->value.element.name);

		      if (!strcmp(node->value.element.name, "tileset")) {
		  		SSL_Tileset_Info *tileset = malloc(sizeof(SSL_Tileset_Info));

		  		tileset->firstGid = (int *)mxmlElementGetAttr(node, "firstgid");
		  		tileset->name = mxmlElementGetAttr(node, "name");
		  		tileset->tile_width = (int *)mxmlElementGetAttr(node, "tilewidth");
		  		tileset->tile_height = (int *)mxmlElementGetAttr(node, "tileheight");
		  		tileset->spacing = (int *)mxmlElementGetAttr(node, "spacing");
		  		tileset->margin = (int *)mxmlElementGetAttr(node, "margin");

		  		SSL_Hashmap_Add(map->tileset->tilesets, tileset->firstGid, tileset);

		  		curr_tileset = tileset;
		  		curr_tile = NULL;
		      } else if (!strcmp(node->value.element.name, "image")) {
			  		curr_tileset->image = SSL_Image_Load(mxmlElementGetAttr(node, "source"), 16,16, window);
		      } else if (!strcmp(node->value.element.name, "tile")) {
		    	  SSL_Tile *tile = malloc(sizeof(SSL_Tile));

		    	  tile->id = mxmlElementGetAttr(node, "id");
		    	  tile->properties = SSL_Hashmap_Create();

		    	  curr_tile = tile;
		      } else if (!strcmp(node->value.element.name, "property") && curr_tile != NULL) {
		    	  SSL_Hashmap_Add(curr_tile->properties, mxmlElementGetAttr(node, "name"), mxmlElementGetAttr(node, "value"));
		      } else if (!strcmp(node->value.element.name, "layer")) {
		    	  curr_layer =  mxmlElementGetAttr(node, "name");
		      } else if (!strcmp(node->value.element.name, "data") && curr_layer != NULL) {
		    	  char base64DecodeOutput[9999];
		    	  b64_decode((char *)mxmlGetText(node, 0), base64DecodeOutput);

		    	  int tile_map[16 * 16];
		    	  int (*tiles)[16][16] = malloc (sizeof(16*16));

		    	  uLongf outlen = 16 * 16 * 4;
		    	  uncompress((Bytef *)tile_map, &outlen, (const Bytef *)base64DecodeOutput, strlen(base64DecodeOutput));


		    	  int k = 0;
		    	  int i, j;
		    	  for ( i = 0; i < 16;i++)
		    	  {
		    	      for ( j = 0; j < 16;j++)
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
			pre = next;
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

	/*while((node = mxmlFindElement(node, tree, "tileset", NULL, NULL, MXML_DESCEND)) != NULL) {


	}
	//printf("\n%i\n", node->value.element.num_attrs);*/
	return map;
}
