#pragma once

#include <iostream>

class Game {
public:
    Game();

    ~Game();

    void init(const std::string title);

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

    bool inExploration = false;

    bool inAttack = true;

    SDL_Window *window;
};
