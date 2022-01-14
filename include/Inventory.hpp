#pragma once

#include "Game.hpp"

int getPadding(int blockWidth, int textWidth);

class Inventory {
public:
    Inventory() {
        Inventory::pokemonsTexture = IMG_LoadTexture(Game::renderer, "assets/pokemon_sprite.png");
    };

    ~Inventory() {};

    void draw();

private:
    SDL_Texture *pokemonsTexture;
};
