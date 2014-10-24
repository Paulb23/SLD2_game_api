#include "../src/SSL/misc/SSL_List.h"
#include <stdio.h>
#include <string.h>
#include "tests.h"


void list_test() {

	SSL_List *list  = SSL_List_Create();

	if (list == 0) {printf("\n List failed to create...\n"); return;}

	SSL_List_Add(list, "Item 1");
	SSL_List_Add(list, "Item 2");
	SSL_List_Add(list, "Item 3");
	SSL_List_Add(list, "Item 4");
	SSL_List_Add(list, "Item 5");

	if (strcmp(SSL_List_Get(list, 2),"Item 2")){ printf("\n Hashmap failed to get / store...\n"); return;}

	SSL_List_Remove(list, "Item 2");

	if (strcmp(SSL_List_Get(list, 2),"Item 3")){ printf("\n Hashmap failed to get / store...\n"); return;}

	SSL_List_Destroy(list);

	printf("\n List test passed...\n");
}
