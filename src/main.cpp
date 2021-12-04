#include <SDL2/SDL.h>
#include <stdio.h>
#include "../include/main.hpp"
#include "../include/game.hpp"

int main(int argc, char *argv[])
{
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    initGame(window, renderer, &isGameRunning);

    while (isGameRunning) {
        handleEvents(&isGameRunning);
        updateGame();
        renderGame(renderer);
    }

    return 1;
}