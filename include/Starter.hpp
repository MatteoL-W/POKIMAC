#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include "Game.hpp"
#include "Text.hpp"
#include "Colors.hpp"

class Starter {
public:
    Starter() {
        Starter::chosenCharacter = new Text();
        Starter::chosenStarter = new Text();

        Starter::background = IMG_LoadTexture(Game::renderer, "assets/starter.png");
        chosenCharacter->create("x", GreyColor, "Press");
        chosenStarter->create("x", GreyColor, "Press");
    };

    ~Starter() {};

    void update();

    void draw();

    static const int MAX_KEYS_FROM_1_TO_3 = 3;

    static const int MAX_KEYS_FROM_D_TO_J = 5;

    static int starterPokemon;

    static int starterCharacter;

private:
    Text *chosenCharacter;

    Text *chosenStarter;

    SDL_Texture *background;

};
