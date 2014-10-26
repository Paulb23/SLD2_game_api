#ifndef SSL_TILED_READER_H_
#define SSL_TILED_READER_H_

#include "../misc/SSL_Hashmap.h"
#include "../graphics/SSL_Image.h"

typedef struct _SSL_MAP_ {
	const char *version;
	const char *orientation;
	const int *map_width;
	const int *map_height;
	const int *tile_width;
	const int *tile_height;
} SSL_Map;

typedef struct _SSL_Tileset_ {
	const int  *amount;
	SSL_Hashmap *tilesets;
	SSL_Hashmap *tiles;
} SSL_Tileset;

typedef struct _SSL_Tileset_Info_ {
	const int  *firstGid;
	const char *name;
	const int  *tile_width;
	const int  *tile_height;
	const int  *spacing;
	const int  *margin;
	SSL_Image *image;
} SSL_Tileset_Info;

typedef struct _SSL_Tile_ {
	const int *id;
	SSL_Hashmap *properties;
} SSL_Tile;


typedef struct _SSL_Tiled_Map_ {
	SSL_Map	    *map;
	SSL_Tileset *tileset;
	SSL_Hashmap *layer;
} SSL_Tiled_Map;


SSL_Tiled_Map *SSL_Tiled_Map_Load(SSL_Window *window);

#endif /* SSL_TILED_READER_H_ */
