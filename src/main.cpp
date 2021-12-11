#include <SDL2/SDL.h>
#include "../include/main.hpp"
#include "../include/game.hpp"

int main(int argc, char *argv[])
{
    initGame(window, renderer);

    while (isGameRunning) {
        handleEvents();
        updateGame();
        renderGame(renderer);
    }

    return 1;
}