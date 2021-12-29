#pragma once

#include <iostream>
#include "Pokemon.hpp"

const int MAX_POKEMON_INV = 6;

class Game {
public:
    Game();

    ~Game();

    void init(const std::string title);

    void changeInterface();

    void clean();

    bool running() { return isRunning; };

    void setRunning(bool newState) { isRunning = newState; }

    bool exploring() { return inExploration; };

    bool attacking() { return inAttack; };

    static SDL_Renderer *renderer;

    SDL_Event event;

private:
    const int WINDOW_WIDTH = 800;

    const int WINDOW_HEIGHT = 800;

    bool isRunning = false;

    Pokemon inventory[MAX_POKEMON_INV];

    bool inExploration = true;

    bool inAttack = false;

    int level = 1;

    SDL_Window *window;
};
