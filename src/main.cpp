#include <SDL2/SDL.h>
#include "../include/main.hpp"
#include "../include/Game.hpp"
#include "../include/Map.hpp"
#include "../include/ExplorationInterface.hpp"
#include "../include/AttackInterface.hpp"

Game *game = nullptr;
Map *map = nullptr;
ExplorationInterface *explorationInterface = nullptr;
AttackInterface *attackInterface = nullptr;
Pokemon *pokemon = new Pokemon(1);

int main(int argc, char *argv[]) {
    game = new Game();
    game->init("POKIMAC");
    explorationInterface = new ExplorationInterface(game);
    attackInterface = new AttackInterface(game, pokemon);

    while (game->running()) {
        frameStart = SDL_GetTicks();

        if (game->exploring()) {
            explorationInterface->handleEvents();
            explorationInterface->update();
            explorationInterface->render();
        } else if (game->attacking()) {
            attackInterface->handleEvents();
            attackInterface->update();
            attackInterface->render();
        }

        // LIMITING THE FRAMERATE
        frameTime = SDL_GetTicks() - frameStart;
        if (FRAME_DELAY > frameTime) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }

    return 1;
}