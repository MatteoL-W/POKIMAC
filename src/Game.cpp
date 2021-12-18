#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "../include/Game.hpp"
#include "../include/Map.hpp"

Map *map = nullptr;
SDL_Renderer *Game::renderer = nullptr;

Game::Game() {}

Game::~Game() {}

/**
 * @brief Initialize the game (assign the window, renderer, define the game as running
 * @param title
 */
void Game::init(const std::string title) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                                  WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, 0);
        isRunning = true;

        map = new Map();
    }
}

/**
 * @brief Handle SDL Events
 */
void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;

        default:
            break;
    }
}

/**
 * @brief Update objects in the game
 */
void Game::update() {

}

/**
 * @brief Render the game (map and objects)
 */
void Game::render() {
    SDL_RenderClear(renderer);
    map->drawMap();
    SDL_RenderPresent(renderer);
}

/**
 * @brief Quit the game properly
 */
void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
