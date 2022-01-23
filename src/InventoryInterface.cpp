#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/InventoryInterface.hpp"
#include "../include/Game.hpp"

/**
 * @brief Handle SDL Events in the exploration part
 */
void InventoryInterface::handleEvents() {
    SDL_Event event = game->event;
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT) {
        game->setRunning(false);
    }

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_i:
            case SDLK_ESCAPE:
                game->changeInterfaceToExploration();
                break;
        }
    }
}

/**
 * @brief Render the inventory part (map and objects)
 */
void InventoryInterface::render() {
    SDL_RenderClear(Game::renderer);

    inventory->draw();

    SDL_RenderPresent(Game::renderer);
}

/**
 * @brief Return true if the inventory interface is active
 * @return
 */
bool InventoryInterface::isActive() {
    if (game->displayingInventory())
        return true;
    return false;
}