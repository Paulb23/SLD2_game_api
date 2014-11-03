#include "../src/SSL/files/iniparser.h"
#include "../lib/SDL2/SDL.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "tests.h"


/**
 *  Creates and manipulates a ini reader
 */
void ini_reader_test() {
	printf("\n Starting iniparser tests...\n");

	dictionary *d = iniparser_load("../conf/config.ini");

	assert(!strcmp(iniparser_getstring(d, "animal:cat", "cat"), "lion"));

	printf(" ini reader test passed...\n");
}
