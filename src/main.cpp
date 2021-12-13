#include <SDL2/SDL.h>
#include "../include/main.hpp"
#include "../include/game.hpp"

int main(int argc, char *argv[])
{
    initGame(window, renderer);

    while (isGameRunning) {
        frameStart = SDL_GetTicks();

        handleEvents();
        updateGame();
        renderGame(renderer);

        // LIMITING THE FRAMERATE
        frameTime = SDL_GetTicks() - frameStart;
        if (FRAME_DELAY > frameTime) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }

    return 1;
}