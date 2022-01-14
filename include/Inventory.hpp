#pragma once

#include "Game.hpp"
#include "Pokemon.hpp"

int getPadding(int blockWidth, int textWidth);

class Inventory {
public:
    Inventory() {
        Inventory::pokemonsTexture = IMG_LoadTexture(Game::renderer, "assets/pokemon_sprite.png");
    };

    ~Inventory() {};

    void draw();
    void drawBlock(int xOperator, int yOperator);
    void drawPokemon(Pokemon* pokemon, int xOperator, int yOperator);
    void drawPokemonSprite(int xOperator, int yOperator, SDL_Rect *srcPokemon, SDL_Rect *dstPokemon);
    void drawPokemonInfo(int xOperator, int yOperator, Pokemon* pokemon, SDL_Rect dstPokemon);

private:
    SDL_Texture *pokemonsTexture;
};
