#pragma once

#include "Game.hpp"
#include "Pokemon.hpp"
#include "Text.hpp"
#include "Inventory.hpp"


class Ending {
public:
    Ending() {
        Ending::backgroundTexture = IMG_LoadTexture(Game::renderer, "assets/endingBackground.png");

    }

    ~Ending() {};

    void draw();

    void drawSprite();

    void drawPokemons(Pokemon *pokemon, int xOperator);

private:
    SDL_Texture *backgroundTexture;

    SDL_Rect srcPlayer, srcPokemon;
    SDL_Rect destPlayer, destPokemon;
};

