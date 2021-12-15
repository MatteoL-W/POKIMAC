#include <SDL2/SDL.h>
#include "../include/main.hpp"
#include "../include/Game.hpp"
#include "../include/GameObject.hpp"

Game *game = nullptr;

int main(int argc, char *argv[]) {
    game = new Game();

    game->init("POKIMAC");

    while (game->running()) {
        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        // LIMITING THE FRAMERATE
        frameTime = SDL_GetTicks() - frameStart;
        if (FRAME_DELAY > frameTime) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }

    return 1;
}