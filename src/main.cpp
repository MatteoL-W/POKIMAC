#include <SDL2/SDL.h>
#include "../include/main.hpp"
#include "../include/Game.hpp"
#include "../include/Map.hpp"
#include "../include/ExplorationInterface.hpp"

Game *game = nullptr;
Map *map = nullptr;
ExplorationInterface *exploration = nullptr;

int main(int argc, char *argv[]) {
    game = new Game();
    game->init("POKIMAC");
    exploration = new ExplorationInterface(game);

    while (game->running()) {
        game->handleEvents();
        frameStart = SDL_GetTicks();

        if (game->exploring()) {
            exploration->handleEvents();
            exploration->update();
            exploration->render();
        }

        if (game->attacking()) {
            //attack->handleEvents();
            //attack->update();
            //attack->render();
        }

        // LIMITING THE FRAMERATE
        frameTime = SDL_GetTicks() - frameStart;
        if (FRAME_DELAY > frameTime) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }

    return 1;
}