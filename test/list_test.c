#include "../src/game_api/misc/list.h"
#include <stdio.h>
#include <string.h>
#include "tests.h"


void list_test() {

	List *list  = list_create();

	if (list == 0) {printf("\n List failed to create...\n"); return;}

	list_set(list, "Item 1");
	list_set(list, "Item 2");
	list_set(list, "Item 3");
	list_set(list, "Item 4");
	list_set(list, "Item 5");

	if (strcmp(list_get(list, 2),"Item 2")){ printf("\n Hashmap failed to get / store...\n"); return;}

	list_remove(list, "Item 2");

	if (strcmp(list_get(list, 2),"Item 3")){ printf("\n Hashmap failed to get / store...\n"); return;}

	list_destroy(list);

	printf("\n List test passed...\n");
}
