#pragma once

#include "Game.hpp"
#include "Pokemon.hpp"
#include "Text.hpp"

int getPadding(int blockWidth, int textWidth);

class Inventory {
public:
    Inventory() {
        Inventory::backgroundTexture = IMG_LoadTexture(Game::renderer, "assets/inventoryBackground.jpg");

        Inventory::nameText = new Text();
        Inventory::typeText = new Text();
        Inventory::healthPointText = new Text();

        nameText->changeFont("Press", 18);
        typeText->changeFont("Press", 18);
        healthPointText->changeFont("Press", 15);
    };

    ~Inventory() {};

    void draw();
    void drawBlock(int xOperator, int yOperator);
    void drawPokemon(Pokemon* pokemon, int xOperator, int yOperator);
    void drawPokemonSprite(int xOperator, int yOperator, SDL_Rect *srcPokemon, SDL_Rect *dstPokemon);
    void drawPokemonInfo(int xOperator, int yOperator, Pokemon* pokemon, SDL_Rect dstPokemon);

private:
    SDL_Texture *backgroundTexture;

    Text *nameText;
    Text *typeText;
    Text *healthPointText;
};
