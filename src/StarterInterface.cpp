#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "../include/Game.hpp"
#include "../include/StarterInterface.hpp"
#include "../include/Pokemon.hpp"
#include "../include/Text.hpp"

int SDL_KeysFrom1To3[Starter::MAX_KEYS_FROM_1_TO_3] = {
        SDLK_0, SDLK_1, SDLK_2
};

int SDL_KeysFromDToJ[Starter::MAX_KEYS_FROM_D_TO_J] = {
        SDLK_d, SDLK_f, SDLK_g, SDLK_h, SDLK_j
};

std::string characterSpritePath = "";

std::string charactersSpritesPaths[Starter::MAX_KEYS_FROM_D_TO_J] = {
        "baby.png",
        "cameraman.png",
        "ethan.png",
        "girl.png",
        "mountain.png"
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
        for (int i = 0; i < Starter::MAX_KEYS_FROM_1_TO_3; i++) {
            if (event.key.keysym.sym == SDL_KeysFrom1To3[i]) {
                Starter::starterPokemon = i;
            }
        }

        for (int i = 0; i < Starter::MAX_KEYS_FROM_D_TO_J; i++) {
            if (event.key.keysym.sym == SDL_KeysFromDToJ[i]) {
                Starter::starterCharacter = i;
            }
        }

        switch (event.key.keysym.sym) {
            case SDLK_RETURN:
                characterSpritePath = "assets/characters/" + charactersSpritesPaths[Starter::starterCharacter];

                Game::inventory[0] = new Pokemon(Starter::starterPokemon);
                Game::inventoryLength++;
                game->changeInterfaceToExploration();

                Game::characterTexture = IMG_LoadTexture(Game::renderer, characterSpritePath.c_str());
                break;
        }
    }
}

/**
 * @brief Update objects in the exploration part
 */
void StarterInterface::update() {
    starter->update();
}

/**
 * @brief Render the exploration part (map and objects)
 */
void StarterInterface::render() {
    SDL_RenderClear(Game::renderer);

    starter->draw();

    SDL_RenderPresent(Game::renderer);
}

/**
 * @brief Return true if the starter interface is active
 * @return
 */
bool StarterInterface::isActive() {
    if (game->starting())
        return true;
    return false;
}