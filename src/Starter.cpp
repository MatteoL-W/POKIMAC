#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "../include/Game.hpp"
#include "../include/Pokemon.hpp"
#include "../include/Text.hpp"
#include "../include/Starter.hpp"

Text *chosenStarter = new Text();
Text *chosenCharacter = new Text();

int Starter::starterPokemon = 0;
int Starter::starterCharacter = 2;

void Starter::update() {
    int center = Game::WINDOW_WIDTH / 2;
    int gap = Game::WINDOW_WIDTH / 10;

    for (int i = 0; i < MAX_KEYS_FROM_D_TO_J; i++) {
        if (starterCharacter == i) {
            int destRect = chosenCharacter->getDestRect();
            chosenCharacter->changeDestRect((center + (i - 2) * gap) - (destRect / 2),Game::WINDOW_HEIGHT / 2 - 35);
        }
    }

    for (int i = 0; i < MAX_KEYS_FROM_1_TO_3; i++) {
        if (starterPokemon == i) {
            int destRect = chosenStarter->getDestRect();
            chosenStarter->changeDestRect((center + (i - 1) * gap) - (destRect / 2),Game::WINDOW_HEIGHT / 2 + 120);
        }
    }
}

void Starter::draw() {
    SDL_RenderCopy(Game::renderer, background, NULL, NULL);

    chosenCharacter->draw();
    chosenStarter->draw();
}