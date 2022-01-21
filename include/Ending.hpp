#pragma once

#include "Game.hpp"
#include "Pokemon.hpp"
#include "Text.hpp"
#include "Inventory.hpp"


class Ending {
public:
    Ending() {
        Ending::backgroundTexture = IMG_LoadTexture(Game::renderer, "assets/endingBackground.png");
        Ending::playerTexture = IMG_LoadTexture(Game::renderer, "assets/ethan_sprite.png");

        // Ending::congratsText = new Text();
        // Ending::creditsText = new Text();

        // congratsText->changeFont("Press", 18);
        // creditsText->changeFont("Press", 18);
    }

    ~Ending() {};

    void draw();

    void drawSprite();

    //void drawText();

    void drawPokemons(Pokemon *pokemon, int xOperator);

private:
    SDL_Texture *backgroundTexture;
    SDL_Texture *playerTexture;

    // Text *congratsText;
    // Text *creditsText;

    SDL_Rect srcPlayer, srcPokemon;
    SDL_Rect destPlayer, destPokemon;
};

