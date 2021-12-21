#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "../include/Game.hpp"
#include "../include/Map.hpp"
#include "../include/Text.hpp"
#include "../include/Colors.hpp"

Map *map = nullptr;
Text *text = new Text();
SDL_Renderer *Game::renderer = nullptr;

Game::Game() {}

Game::~Game() {}

/**
 * @brief Initialize the game (assign the window, renderer, define the game as running
 * @param title
 */
void Game::init(const std::string title) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        TTF_Init();
        window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                                  WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, 0);
        Game::isRunning = true;

        map = new Map();
    }
}

/**
 * @brief Handle SDL Events
 */
void Game::handleEvents() {
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT) {
        Game::isRunning = false;
    }

    // Si une touche est enfoncée, on vérifie si elle correspond à une touche assignée au mouvement (flèches et ZQSD)
    // On enclenche le déplacement si c'est le cas
    if (event.type == SDL_KEYDOWN) {
        map->updatePlayerSprite();
        switch (event.key.keysym.sym) {
            case SDLK_z:
            case SDLK_UP:
                map->updatePlayerPosition(MOVE_UP);
                break;
            case SDLK_q:
            case SDLK_LEFT:
                map->updatePlayerPosition(MOVE_LEFT);
                break;
            case SDLK_d:
            case SDLK_RIGHT:
                map->updatePlayerPosition(MOVE_RIGHT);
                break;
            case SDLK_s:
            case SDLK_DOWN:
                map->updatePlayerPosition(MOVE_DOWN);
                break;
            default:
                break;
        }
    }

    if (event.type == SDL_KEYUP) {
        map->updatePlayerSpriteToDefault();
    }
}

/**
 * @brief Update objects in the game
 */
void Game::update() {
    text->create("Font testing", RedColor, "Press");
    text->changeText("Testttttttttttttttttttttttttttttttttttttttttt");
}

/**
 * @brief Render the game (map and objects)
 */
void Game::render() {
    SDL_RenderClear(renderer);

    map->drawMap();
    text->draw();

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
