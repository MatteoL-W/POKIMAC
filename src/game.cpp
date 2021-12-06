#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include "../include/game.hpp"

const std::string GAME_NAME = "POKIMAC";
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

/**
 * @brief Init SDL_Window, render the first frame and update isGameRunning.
 * 
 * @param window 
 * @param renderer 
 * @param isGameRunning 
 */
void initGame(SDL_Window* window, SDL_Renderer* renderer, bool *isGameRunning) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        // remplacer SDL_WINDOW_SHOWN par fullscreen si on veut fullscreen
        window = SDL_CreateWindow(GAME_NAME.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, 0);

        *isGameRunning = true;

        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        renderGame(renderer);
    }
}

/**
 * @brief Handle SDL Events
 * 
 * @param isGameRunning 
 */
void handleEvents(bool *isGameRunning) {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            *isGameRunning = false;
            break;

        default:
            break;
    }
}

void updateGame() {
}

/**
 * @brief Render the game
 * 
 * @param renderer 
 */
void renderGame(SDL_Renderer *renderer) {
    SDL_RenderClear(renderer);
    //ici on met ce qui change je crois
    SDL_RenderPresent(renderer);
}

/**
 * @brief Close the window
 * 
 * @param window 
 * @param renderer 
 */
void cleanGame(SDL_Window *window, SDL_Renderer *renderer) {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}