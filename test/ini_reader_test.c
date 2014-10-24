#include "../src/SSL/files/iniparser.h"
#include "../lib/SDL2/SDL.h"
#include <stdio.h>
#include <string.h>
#include "tests.h"


/**
 *  Creates and manipulates a ini reader
 */
void ini_reader_test() {
	dictionary *d = iniparser_load("../conf/config.ini");

	if (strcmp(iniparser_getstring(d, "animal:cat", "cat"), "lion")) {printf("\n Ini reader falied to get value \n"); return;};
	printf("\n ini reader test passed...\n");
}
