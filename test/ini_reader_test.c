#include "../src/game_api/files/ini_reader.h"
#include <stdio.h>
#include <string.h>
#include "tests.h"

void ini_reader_test() {
	Ini_Reader *ini = ini_create();
	ini_add_catorgory(ini, "test");
	ini_add_value(ini, "test", "test", "10");
	ini_read_file(ini, "../conf/config.ini");
	if (strcmp(ini_get_value(ini, "test", "test"), "10")) {printf("\n Ini reader falied to get value \n"); return;};


	//if (strcmp(ini_get_value(ini, "animal", "cat"), "lion")) {printf("\n Ini reader falied to get value \n"); return;};
	printf("\n ini reader test passed...\n");
}
