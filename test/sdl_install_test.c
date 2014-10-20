#include "../lib/SDL2/SDL.h"
#include "../lib/SDL2/SDL_ttf.h"
#include "../lib/SDL2/SDL_image.h"
#include "../lib/SDL2/SDL_mixer.h"
#include "tests.h"

void sdl_install_test() {

    //Start SDL
    SDL_Init( SDL_INIT_EVERYTHING );
    TTF_Init();
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF);
    Mix_Init(MIX_INIT_MP3 | MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_OGG);


    //Quit SDL
    SDL_Quit();
}
