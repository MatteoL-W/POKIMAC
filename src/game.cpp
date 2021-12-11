#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "../include/game.hpp"

const std::string GAME_NAME = "POKIMAC";
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
int cnt = 0;

SDL_Texture* playerTexture;
SDL_Rect dstRect;

/**
 * @brief Init SDL_Window, render the first frame and update isGameRunning.
 * 
 * @param window 
 * @param renderer 
 * @param isGameRunning 
 */
void initGame(SDL_Window* window, SDL_Renderer*& renderer, bool *isGameRunning) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        // remplacer SDL_WINDOW_SHOWN par fullscreen si on veut fullscreen
        window = SDL_CreateWindow(GAME_NAME.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, 0);
        *isGameRunning = true;

        playerTexture = IMG_LoadTexture(renderer, "assets/ethan_sprite.png");

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
    cnt++;
    dstRect.w = 128;
    dstRect.h = 128;
    dstRect.x = cnt / 100;
}

/**
 * @brief Render the game
 * 
 * @param renderer 
 */
void renderGame(SDL_Renderer *renderer) {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, playerTexture, NULL, &dstRect);
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