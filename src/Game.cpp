#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "../include/Pokemon.hpp"
#include "../include/Game.hpp"
#include "../include/Map.hpp"
#include "../include/Text.hpp"
#include "../include/Colors.hpp"

SDL_Renderer *Game::renderer = nullptr;

Game::Game() {}

Game::~Game() {}

/**
 * @brief Initialize the game (assign the window, renderer, define the game as running)
 * @param title
 */
void Game::init(const std::string title) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        TTF_Init();
        window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                                  WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, 0);

        isRunning = true;
    }
}

/**
 * @brief Change the interface
 */
void Game::changeInterfaceToAttack(Pokemon *enemy) {
    setActivity("inAttack");

    // load le pokemon en paramètre dans le private du game
}

/**
 * @brief Quit the game properly
 */
void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
