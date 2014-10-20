#ifndef HASHMAP_H_
#define HASHMAP_H_

/* Hashmap struct */
typedef struct _Hashmap {
	void *key;
	void *value;
	struct _Hashmap *next;
} Hashmap;

Hashmap *hashmap_create();
void hashmap_set(Hashmap *map, void *key, void *value);
void *hashmap_get(Hashmap *map, void *key);
void hashmap_remove(Hashmap *map, void *key);
void hashmap_destroy(Hashmap *map);

#endif /* HASHMAP_H_ */
