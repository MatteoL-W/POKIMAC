#pragma once

#include <iostream>
#include "Pokemon.hpp"

const int MAX_POKEMON_INV = 6;

class Game {
public:
    Game();

    ~Game();

    void init(const std::string title);

    void handleEvents();

    void update();

    void render();

    void clean();

    bool running() { return isRunning; };

    static SDL_Renderer *renderer;

    SDL_Event event;

private:
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;

    bool isRunning = false;

    Pokemon inventory[MAX_POKEMON_INV];

    SDL_Window *window;
};
