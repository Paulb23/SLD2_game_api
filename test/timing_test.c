#include "tests.h"
#include <stdio.h>
#include "../src/ssl/timing/SSL_Timing.h"
#include "../lib/sdl2/sdl.h"


void timing_test() {
	SDL_Init(SDL_INIT_EVERYTHING);
	SSL_Timer_Init();

	while (1) {

	}

	SDL_Quit();
}
