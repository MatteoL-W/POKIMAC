#include <SDL2/SDL.h>
#include "../include/main.hpp"
#include "../include/Pokemon.hpp"
#include "../include/Game.hpp"
#include "../include/Map.hpp"
#include "../include/ExplorationInterface.hpp"
#include "../include/AttackInterface.hpp"

Game *game = nullptr;

int main(int argc, char *argv[]) {
    game = new Game("POKIMAC");

    while (game->running()) {
        frameStart = SDL_GetTicks();

        game->refresh();

        // LIMITING THE FRAMERATE
        frameTime = SDL_GetTicks() - frameStart;
        if (FRAME_DELAY > frameTime) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }

    return 1;
}