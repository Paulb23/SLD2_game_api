#include "../../../lib/SDL2/SDL.h"
#include "../misc/SSL_Logger.h"
#include <time.h>

static int loaded = 0;
static int running = 0;

int uptime = 0;
double delta = 0;
double fps = 0;
double tick = 0;

int canTick = 0;

static int update_time(void *data) {
	long lastTime = SDL_GetTicks();
	const double ns = 1000.0 / 60;
	Uint32 timer = SDL_GetTicks();

	while(running) {
		Uint32 now = SDL_GetTicks();
		delta += (now - lastTime) / ns;
		lastTime = now;

		while (delta >= 1) {
			canTick = 1;
			tick++;
			delta--;
		}
		fps++;
		canTick = 0;

		if (now > timer + 1000) {
			timer += 1000;
			fps = 0;
			tick = 0;
			uptime += 1;
		}

	SDL_Delay(1);
	}

	return 0;
}


void SSL_Timer_Init() {
	if (!loaded) {
		loaded = 1;
		running = 1;
		static SDL_Thread *thread;
		thread = SDL_CreateThread(update_time, "Timer", (void *)NULL);

		if (thread == NULL) {
			SSL_Log_Write("Failed to create timing thread!" );
		}
	}
}
