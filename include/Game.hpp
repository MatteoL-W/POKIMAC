#pragma once

#include <iostream>

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

    static const int WINDOW_WIDTH = 800;

    static const int WINDOW_HEIGHT = 800;
private:

    bool isRunning = false;

    bool inExploration = true;

    bool inAttack = false;

    int level = 1;

    SDL_Window *window;
};
