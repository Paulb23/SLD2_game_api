#include "../src/game_api/files/ini_reader.h"
#include <stdio.h>
#include <string.h>
#include "tests.h"

void ini_reader_test() {
	Ini_Reader *ini = ini_create();
	ini_add_catorgory(ini, "test");
	ini_add_value(ini, "test", "test", "10");
	if (strcmp(ini_get_value(ini, "test", "test"), "10")) {printf("\n Ini reader falied to get value \n"); return;};

	ini_read_file(ini, "../conf/config.ini");
	//ini_add_catorgory(ini, "animal");
	//ini_add_value(ini, "animal", "cat", "lion");
	if (strcmp(ini_get_value(ini, "animal", "cat"), "lion")) {printf("\n Ini reader falied to get value \n"); return;};
	printf("\n ini reader test passed...\n");
}
