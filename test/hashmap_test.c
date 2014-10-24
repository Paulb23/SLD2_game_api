#include "../src/SSL/misc/hashmap.h"
#include <stdio.h>
#include "tests.h"

/**
 *  Creates and manipulates a hashmap
 */
void hashmap_test() {
	Hashmap *map = hashmap_create();

	if (map == 0) {printf("\n Hashmap failed to create...\n"); return;}

	hashmap_set(map, (void *)"1", (void *)11);
	hashmap_set(map, (void *)"2", (void *)12);
	hashmap_set(map, (void *)"2", (void *)13);
	hashmap_set(map, (void *)"3", (void *)14);
	hashmap_set(map, (void *)"4", (void *)15);
	hashmap_set(map, (void *)"5", (void *)16);
	hashmap_set(map, (void *)"6", (void *)17);

	if ((int)hashmap_get(map, "2") != 13){ printf("\n Hashmap failed to get / store...\n"); return;}
	if ((int)hashmap_get(map, "4") != 15){ printf("\nHashmap failed to get / store...\n"); return;}

	hashmap_remove(map, "2");
	hashmap_remove(map, "7");

	if ((int)hashmap_get(map, "2") != -1) {printf("\n Hashmap failed to remove...\n"); return;}
	if ((int)hashmap_get(map, "6") != 17) {printf("\n Hashmap failed to remove...\n"); return;}

	hashmap_destroy(map);

	printf("\n Hashmap test passed...\n");
}
