#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "../include/Game.hpp"
#include "../include/StarterInterface.hpp"
#include "../include/Pokemon.hpp"

Pokemon *starter = nullptr;

int SDL_KeysFrom1To3[3] = {
        SDLK_0, SDLK_1, SDLK_2
};

/**
 * @brief Handle SDL Events in the starter interface
 */
void StarterInterface::handleEvents() {
    SDL_Event event = game->event;
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT) {
        game->setRunning(false);
    }

    if (event.type == SDL_KEYDOWN) {
        for (int i = 0; i < 3; i++) {
            if (event.key.keysym.sym == SDL_KeysFrom1To3[i]) {
                starter = new Pokemon(i);
            }
        }

        switch(event.key.keysym.sym) {
            case SDLK_RETURN:
                if (starter == nullptr)
                    starter = new Pokemon(0);

                Game::inventory[0] = starter;
                Game::inventoryLength++;
                game->changeInterfaceToExploration();
                break;
        }

    }

}

/**
 * @brief Update objects in the exploration part
 */
void StarterInterface::update() {

}

/**
 * @brief Render the exploration part (map and objects)
 */
void StarterInterface::render() {
    SDL_RenderClear(Game::renderer);

    SDL_RenderPresent(Game::renderer);
}

bool StarterInterface::isActive() {
    if (game->starting())
        return true;
    return false;
}