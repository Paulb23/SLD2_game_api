#include "hashmap.h"
#include "logger.h"
#include <stdlib.h>

/**************************//**
 *
 * Creates a Hashmap an returns it
 * If it fails to create return -1
 *
 *************************/
Hashmap *hashmap_create() {
	Hashmap *map = malloc(sizeof(Hashmap));	/* allocate memory */
	map->next = 0;							/* point to empty */

	return (map) ? map : (Hashmap *)0;		/* return hashmap */
}


/**************************//**
 *
 * Adds a value to the hash map
 *
 * @param map - Hashmap to add to
 * @param key - Key to add
 * @Param value - Value to add
 *
 *************************/
void hashmap_set(Hashmap *map, void *key, void *value) {
	Hashmap *tmp = malloc(sizeof(Hashmap));					/* allocate memory */
	if (!tmp) {log_write("Failed to allocate memory for hashmap! "); return;}

	tmp->key = key;											/* fill in the data */
	tmp->value = value;
	tmp->next = 0;

	Hashmap *curr = map;									/* loop until we hit the end of the map */
	while (curr->next != 0) {								/* or we find the key already exists    */
		if (curr->key == key) {
			curr->value = value;
			return;
		}
		curr = curr->next;
	}
	if (curr->key == key) {									/* check the last element isn't the key */
		curr->value = value;
		return;
	}
	curr->next = tmp;										/* else finally we can set the last next to point to the new element */
}


/**************************//**
 *
 * Gets a value from the hashmap
 * returns -1 if key is not found
 *
 * @param map - Hashmap to search
 * @param key - key to look for
 *
 *************************/
void *hashmap_get(Hashmap *map, void *key) {
	Hashmap *curr = map;									/* tmp pointer used to loop */
	while (curr->key != key && curr->next != 0) {			/* loop until we find the key */
		curr = curr->next;
	}

	return (curr->key == key) ? curr->value : (void *)-1;	/* return */
}


/**************************//**
 *
 * Removes a key from the Hashmap
 *
 *@param map - Hashmap with the key to remove
 *@param key - key to remove
 *
 *************************/
void hashmap_remove(Hashmap *map, void *key) {
	Hashmap *pre;											/* Previous and next pointer to loop through the map */
	Hashmap *curr = map;

	while(curr->key != key && curr->next != 0) {			/* loop until the end or we find the key */
		pre = curr;
		curr = curr->next;
	}
	if (curr->key != key) {									/* if it does not equal the key we have reached the end */
		return;
	}

	pre->next = curr->next;									/* else adjust the pointers and return */
	free(curr);
}

/**************************//**
 *
 * Destroys the hashmap
 *
 *@param map - Hashmap to destroy
 *
 *************************/
void hashmap_destroy(Hashmap *map) {
	Hashmap *pre;											/* Previous and next pointer to loop through the map */
	Hashmap *curr = map;

	while(curr->next != 0) {								/* loop through and free everything */
		free(pre);
		pre = curr;
		curr = curr->next;
	}

	free(pre);
	free(curr);
}
