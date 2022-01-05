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

int SDL_KeysFrom1To6[6] = {
        SDLK_0, SDLK_1, SDLK_2, SDLK_3, SDLK_4, SDLK_5,
};

/**
 * @brief Handle SDL Events in the exploration part
 */
void AttackInterface::handleEvents() {
    SDL_Event event = game->event;
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT) {
        game->setRunning(false);
    }

    if (battle->isWaitingForPokemon() && event.type == SDL_KEYDOWN) {
        for (int i = 0; i < Game::inventoryLength; i++) {
            if (event.key.keysym.sym == SDL_KeysFrom1To6[i] && Game::inventory[i]->getHealthPoint() != 0) {
                battle->setPokemon(Game::inventory[i]);
                Battle::state = "waitingForAttack";
            }
        }

    }

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                game->changeInterfaceToExploration();
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