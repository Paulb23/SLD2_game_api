#ifndef INI_READER_H_
#define INI_READER_H_

#include "../misc/hashmap.h"

/* ini reader struct  */
typedef struct _ini_reader {
	Hashmap *categories; 		/* categories hashmap */
} Ini_Reader;


/* function prototyping */
Ini_Reader *ini_create();
void ini_read_file(Ini_Reader *ini, char *file);
void ini_add_catorgory(Ini_Reader *ini, char *catorgory);
void ini_add_value(Ini_Reader *ini, char *catorgory, void *key, void *value);
void *ini_get_value(Ini_Reader *ini, char *catorgory, void *key);

#endif /* INI_READER_H_ */
