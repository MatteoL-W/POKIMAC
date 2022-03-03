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
 * @brief Render the ending part
 */
void EndingInterface::render() {
    SDL_RenderClear(Game::renderer);

    ending->draw();

    SDL_RenderPresent(Game::renderer);
}

/**
 * @brief Return true if the ending interface is active
 * @return
 */
bool EndingInterface::isActive() { return game->ending(); }