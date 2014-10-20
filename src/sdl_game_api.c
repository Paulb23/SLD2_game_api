#include <stdio.h>
#include "../test/tests.h"

int main(int argc, char *args[]) {
	hello_world();
	sdl_install_test();
	hashmap_test();

	printf("\nAll Tests passed, Press any key to continue...");
	getch();

	return 0;
}
