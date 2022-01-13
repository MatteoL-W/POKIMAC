#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "../include/Pokemon.hpp"
#include "../include/Game.hpp"
#include "../include/Map.hpp"
#include "../include/MapsArray.hpp"
#include "../include/Text.hpp"
#include "../include/Colors.hpp"
#include "../include/AttackInterface.hpp"
#include "../include/ExplorationInterface.hpp"
#include "../include/StarterInterface.hpp"
#include "../include/MapsArray.hpp"

SDL_Renderer *Game::renderer = nullptr;
int Game::level = 0;

StarterInterface *starterInterface = nullptr;
AttackInterface *attackInterface = nullptr;
ExplorationInterface *explorationInterface = nullptr;

Pokemon *attackedPokemon = nullptr;
Pokemon *attackerPokemon = nullptr;

Battle *battle = nullptr;
Map *map = nullptr;

Pokemon *Game::inventory[MAX_POKEMON_INV];
int Game::inventoryLength = 0;

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

        explorationInterface = new ExplorationInterface(this);
        attackInterface = new AttackInterface(this, attackedPokemon, attackerPokemon);
        starterInterface = new StarterInterface(this);
        battle = attackInterface->getBattle();
        map = explorationInterface->getMap();

        isRunning = true;
        level = 0;
    }
}

/**
 * @brief Change the interface to attack
 */
void Game::changeInterfaceToAttack(Pokemon *enemy) {
    battle->reload();
    setActivity("inAttack");
    battle->setEnemy(enemy);
}

/**
 * @brief Change the interface to exploration and level up
 */
void Game::changeInterfaceToExplorationAndLevelUp() {
    if (level + 1 < MAX_MAPS)
        level++;
    Battle::state = "inactive";
    map->loadMap(allMaps[Game::level]);
    setActivity("inExploration");
}

/**
 * @brief Change the interface to exploration
 */
void Game::changeInterfaceToExploration() {
    Battle::state = "inactive";
    setActivity("inExploration");
}

/**
 * @brief Quit the game properly
 */
void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Game::refresh() {
    if (starting()) {
        starterInterface->handleEvents();
        starterInterface->update();
        starterInterface->render();
    } else if (exploring()) {
        explorationInterface->handleEvents();
        explorationInterface->update();
        explorationInterface->render();
    } else if (attacking()) {
        attackInterface->handleEvents();
        attackInterface->update();
        attackInterface->render();
    }
}
