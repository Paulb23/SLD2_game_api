#include <stdio.h>
#include "../test/tests.h"

/**
 *  Runs all the tests
 */
int main(int argc, char *args[]) {
	hello_world();
	sdl_install_test();
	hashmap_test();
	list_test();
	ini_reader_test();
	sdl_window_test();
	sdl_image_test();
	sdl_font_test();
	keybord_input_test();
	mouse_input_test();
	user_interface_test();

	printf("\n All Tests passed, Press any key to continue...");
	getch();

	return 0;
}
