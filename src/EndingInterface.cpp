#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/EndingInterface.hpp"

/**
 * @brief Handle SDL Events in the ending part
 */
void EndingInterface::handleEvents() {
    SDL_Event event = game->event;
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT) {
        game->setRunning(false);
    }
}

/**
 * @brief Update objects in the ending part
 */
void EndingInterface::update() {

}

/**
 * @brief Render the ending part
 */
void EndingInterface::render() {
    SDL_RenderClear(Game::renderer);

    SDL_RenderPresent(Game::renderer);
}

bool EndingInterface::isActive() {
    if (game->ending())
        return true;
    return false;
}