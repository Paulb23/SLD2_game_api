#include <stdio.h>
#include "../test/tests.h"

int main(int argc, char *args[]) {
	hello_world();
	sdl_install_test();
	hashmap_test();
	ini_reader_test();
	sdl_window_test();
	sdl_image_test();

	printf("\n All Tests passed, Press any key to continue...");
	getch();

	return 0;
}
