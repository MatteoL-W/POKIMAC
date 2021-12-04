#include "../include/game.hpp"

void initGame(SDL_Window* window, SDL_Renderer* renderer, bool *isGameRunning) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        // remplacer SDL_WINDOW_SHOWN par fullscreen si on veut fullscreen
        window = SDL_CreateWindow(GAME_NAME.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, 0);

        *isGameRunning = true;

        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        renderGame(renderer);
        SDL_Delay(3000);
    }
}

void handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            //isGameRunning = false;
            break;

        default:
            break;
    }
}

void updateGame() {

}

void renderGame(SDL_Renderer *renderer) {
    SDL_RenderClear(renderer);
    //ici on met ce qui change je crois
    SDL_RenderPresent(renderer);
}

void cleanGame(SDL_Window *window, SDL_Renderer *renderer) {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned" << std::endl;
}