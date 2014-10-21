#include "hashmap.h"
#include <stdlib.h>
#include <string.h>

/**************************
 *
 * Creates a Hashmap an returns it
 * If it fails to create return -1
 *
 *************************/
Hashmap *hashmap_create() {
	Hashmap *map = malloc(sizeof(Hashmap));
	map->next = 0;

	return (map) ? map : (Hashmap *)0;
}

/**************************
 *
 * Adds a value to the hash map
 *
 *************************/
void hashmap_set(Hashmap *map, void *key, void *value) {
	Hashmap *tmp = malloc(sizeof(Hashmap));
	if (!tmp) return;
	tmp->key = key;
	tmp->value = value;
	tmp->next = 0;

	Hashmap *curr = map;
	while (curr->next != 0) {
		if (curr->key == key) {
			curr->value = value;
			return;
		}
		curr = curr->next;
	}
	if (curr->key == key) {
		curr->value = value;
		return;
	}
	curr->next = tmp;
}


/**************************
 *
 * Gets a value from the hashmap
 * returns -1 if key is not found
 *
 *************************/
void *hashmap_get(Hashmap *map, void *key) {
	Hashmap *curr = map;
	while (curr->key != key && curr->next != 0) {
		curr = curr->next;
	}

	return (curr->key == key) ? curr->value : (void *)-1;
}

/**************************
 *
 * Removes a key from the Hashmap
 *
 *************************/
void hashmap_remove(Hashmap *map, void *key) {
	Hashmap *pre;
	Hashmap *curr = map;

	while(curr->key != key && curr->next != 0) {
		pre = curr;
		curr = curr->next;
	}
	if (curr->key != key) {
		return;
	}

	pre->next = curr->next;
	free(curr);
}

/**************************
 *
 * Destroys the hashmap
 *
 *************************/
void hashmap_destroy(Hashmap *map) {
	Hashmap *pre;
	Hashmap *curr = map;

	while(curr->next != 0) {
		free(pre);
		pre = curr;
		curr = curr->next;
	}

	free(pre);
	free(curr);
}
