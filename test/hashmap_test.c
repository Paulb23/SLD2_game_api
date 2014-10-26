#include "../src/SSL/misc/SSL_Hashmap.h"
#include <stdio.h>
#include "tests.h"

/**
 *  Creates and manipulates a hashmap
 */
void hashmap_test() {
	SSL_Hashmap *map = SSL_Hashmap_Create();

	if (map == 0) {printf("\n Hashmap failed to create...\n"); return;}

	SSL_Hashmap_Add(map, (void *)"1", (void *)11);
	SSL_Hashmap_Add(map, (void *)"2", (void *)12);
	SSL_Hashmap_Add(map, (void *)"2", (void *)13);
	SSL_Hashmap_Add(map, (void *)"3", (void *)14);
	SSL_Hashmap_Add(map, (void *)"4", (void *)15);
	SSL_Hashmap_Add(map, (void *)"5", (void *)16);
	SSL_Hashmap_Add(map, (void *)"6", (void *)17);

	if ((int)SSL_Hashmap_Get(map, "2") != 13){ printf("\n Hashmap failed to get / store...\n"); return;}
	if ((int)SSL_Hashmap_Get(map, "4") != 15){ printf("\nHashmap failed to get / store...\n"); return;}

	SSL_Hashmap_Remove(map, "2");
	SSL_Hashmap_Remove(map, "7");

	if ((int)SSL_Hashmap_Get(map, "2") != -1) {printf("\n Hashmap failed to remove...\n"); return;}
	if ((int)SSL_Hashmap_Get(map, "6") != 17) {printf("\n Hashmap failed to remove...\n"); return;}

	SSL_Hashmap_Destroy(map);

	printf("\n Hashmap test passed...\n");
}
