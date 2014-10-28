#include "../src/SSL/misc/SSL_List.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "tests.h"

/* check creation and destruction of lists */
static void test_1() {
	SSL_List *list[1000];

	/* creation */
	int i = 0;
	for(i = 0; i < 1000; i ++) {
		list[i] = SSL_List_Create();
		assert(list[i] != NULL);
	}

	/* Destruction */
	for(i = 0; i < 1000; i ++) {
		SSL_List_Destroy(list[i]);
	}
}

/* Adding and removing data */
static void test_2() {

	/* create a list */
	SSL_List *list  = SSL_List_Create();
	assert(list != NULL);

	/* add loads of data */
	int i = 0;
	for(i = 0; i < 1000; i ++) {
		SSL_List_Add(list, &i);
	}

	/* remove loads of data */
	for(i = 0; i < 1000; i ++) {
		SSL_List_Remove(list, &i);
	}

	/* Destroy list */
	SSL_List_Destroy(list);
}


/* getting data */
static void test_3() {

	/* create a list */
	SSL_List *list  = SSL_List_Create();
	assert(list != NULL);

	/* add some items */
	SSL_List_Add(list, "Item 1");
	SSL_List_Add(list, "Item 2");
	SSL_List_Add(list, "Item 3");
	SSL_List_Add(list, "Item 4");
	SSL_List_Add(list, "Item 5");

	/* test */
	assert(!strcmp(SSL_List_Get(list, 2),"Item 2"));

	SSL_List_Remove(list, "Item 2");

	assert(!strcmp(SSL_List_Get(list, 2),"Item 3"));
	assert(SSL_List_Get(list, 20) == (void *)-1);
	assert(!strcmp(SSL_List_Get_String(list, 2),"Item 3"));
	assert(SSL_List_Get_Int(list, 2) == atoi("Item 3"));
	assert(SSL_List_Get_Float(list, 2) == atof("Item 3"));
	assert(SSL_List_Get_Pos(list, "Item 3") == 2);
	assert(SSL_List_Get_Pos(list, "Item 5") == 4);
	assert(SSL_List_Get_Pos(list, "Item 8") == -1);
	assert(SSL_List_Size(list) == 4);

	/* Destroy list */
	SSL_List_Destroy(list);
}


void list_test() {
	printf("\n Starting List tests...\n");

	test_1();
	test_2();
	test_3();

	printf(" List test passed...\n");
}
