#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "../include/AttacksFlag.hpp"
#include "../include/AttackInterface.hpp"
#include "../include/Colors.hpp"
#include "../include/Game.hpp"
#include "../include/Map.hpp"
#include "../include/Text.hpp"

/**
 * @brief Handle SDL Events in the exploration part
 */
void AttackInterface::handleEvents() {
    SDL_Event event = game->event;
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT) {
        game->setRunning(false);
    }

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_e:
                game->changeInterfaceToExplorationAndLevelUp();
                break;
        }
    }
}

/**
 * @brief Update objects in the exploration part
 */
void AttackInterface::update() {
}

/**
 * @brief Render the exploration part (map and objects)
 */
void AttackInterface::render() {
    SDL_RenderClear(Game::renderer);

    battle->draw();

    SDL_RenderPresent(Game::renderer);
}