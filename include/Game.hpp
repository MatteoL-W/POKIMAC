#pragma once

#include <iostream>

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

private:
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;

    bool isRunning = false;
    int updateCounter = 0;

    SDL_Window *window;
};
