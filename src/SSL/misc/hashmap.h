#ifndef HASHMAP_H_
#define HASHMAP_H_

/** Hashmap struct */
typedef struct _Hashmap {
	void *key;					/** unique key */
	void *value;				/** value tied to the key */
	struct _Hashmap *next;		/** next element in the hashmap */
} Hashmap;

/* function prototypes */
Hashmap *hashmap_create();
void hashmap_set(Hashmap *map, void *key, void *value);
void *hashmap_get(Hashmap *map, void *key);
void hashmap_remove(Hashmap *map, void *key);
void hashmap_destroy(Hashmap *map);

#endif /* HASHMAP_H_ */
