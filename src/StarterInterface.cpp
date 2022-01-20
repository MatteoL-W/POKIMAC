#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "../include/Game.hpp"
#include "../include/StarterInterface.hpp"
#include "../include/Pokemon.hpp"

Pokemon *starter = nullptr;
std::string characterSpritePath = "";

const int MAX_KEYS_FROM_1_TO_3 = 3;
int SDL_KeysFrom1To3[MAX_KEYS_FROM_1_TO_3] = {
        SDLK_0, SDLK_1, SDLK_2
};

const int MAX_KEYS_FROM_D_TO_J = 5;
int SDL_KeysFromDToJ[MAX_KEYS_FROM_D_TO_J] = {
        SDLK_d, SDLK_f, SDLK_g, SDLK_h, SDLK_j
};
std::string charactersSpritesPaths[MAX_KEYS_FROM_D_TO_J] = {
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
        for (int i = 0; i < MAX_KEYS_FROM_1_TO_3; i++) {
            if (event.key.keysym.sym == SDL_KeysFrom1To3[i]) {
                starter = new Pokemon(i);
            }
        }

        for (int i = 0; i < MAX_KEYS_FROM_D_TO_J; i++) {
            if (event.key.keysym.sym == SDL_KeysFromDToJ[i]) {
                characterSpritePath = "assets/characters/" + charactersSpritesPaths[i];
            }
        }

        switch(event.key.keysym.sym) {
            case SDLK_RETURN:
                if (starter == nullptr)
                    starter = new Pokemon(0);
                if (characterSpritePath == "")
                    characterSpritePath = "assets/characters/" + charactersSpritesPaths[0];

                Game::inventory[0] = starter;
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