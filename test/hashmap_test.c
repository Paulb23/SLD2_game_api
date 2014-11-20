#include "../src/SSL/misc/SSL_Hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "tests.h"

/* check creation and destruction of lists */
static void test_1() {
	SSL_Hashmap *map[1000];

	/* creation */
	int i = 0;
	for(i = 0; i < 1000; i ++) {
		map[i] = SSL_Hashmap_Create();
		assert(map[i] != NULL);
	}

	/* Destruction */
	for(i = 0; i < 1000; i ++) {
		SSL_Hashmap_Destroy(map[i]);
	}
}

/* Adding and removing data */
static void test_2() {

	/* create a list */
	SSL_Hashmap *map  = SSL_Hashmap_Create();
	assert(map != NULL);

	/* add loads of data */
	int i = 0;
	for(i = 0; i < 1000; i ++) {
		SSL_Hashmap_Add(map, &i, &i);
	}

	/* remove loads of data */
	for(i = 0; i < 1000; i ++) {
		SSL_Hashmap_Remove(map, &i);
	}

	/* Destroy list */
	SSL_Hashmap_Destroy(map);
}


/* getting data */
static void test_3() {

	/* create a list */
	SSL_Hashmap *list  = SSL_Hashmap_Create();
	assert(list != NULL);

	/* add some items */
	SSL_Hashmap_Add(list, "Item 1", "Item 1");
	SSL_Hashmap_Add(list, "Item 2", "Item 2");
	SSL_Hashmap_Add(list, "Item 3", "Item 3");
	SSL_Hashmap_Add(list, "Item 4", "Item 4");
	SSL_Hashmap_Add(list, "Item 5", "Item 5");


	/* test */
	assert(!strcmp(SSL_Hashmap_Get(list, "Item 2"),"Item 2"));

	SSL_Hashmap_Remove(list, "Item 2");

	assert(SSL_Hashmap_Get(list, "Item 2") == (void *)-1);
	assert(SSL_Hashmap_Get(list, "Item What?") == (void *)-1);
	assert(!strcmp(SSL_Hashmap_Get_String(list, "Item 3"),"Item 3"));
	assert(SSL_Hashmap_Get_Int(list, "Item 3") == atoi("Item 3"));
	assert(SSL_Hashmap_Get_Float(list, "Item 3") == atof("Item 3"));
	assert(SSL_Hashmap_Size(list) == 4);

	/* Destroy list */
	SSL_Hashmap_Destroy(list);
}


void hashmap_test() {
	printf("\n Starting Hashmap tests...\n");

	test_1();
	test_2();
	test_3();

	printf(" Hashmap test passed...\n");
}
