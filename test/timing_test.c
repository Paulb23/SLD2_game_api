#include "tests.h"
#include <stdio.h>
#include "../src/ssl/timing/SSL_Timing.h"
#include "../lib/sdl2/sdl.h"


void timing_test() {
	SDL_Init(SDL_INIT_EVERYTHING);

	SSL_Timer_Init();
	SSL_Timer_Stop();


	SDL_Quit();
}
