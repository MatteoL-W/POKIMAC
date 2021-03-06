#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <vector>
#include "../include/Pokemon.hpp"
#include "../include/Game.hpp"
#include "../include/Map.hpp"
#include "../include/MapsArray.hpp"
#include "../include/Text.hpp"
#include "../include/Colors.hpp"
#include "../include/Interface.hpp"
#include "../include/StarterInterface.hpp"
#include "../include/AttackInterface.hpp"
#include "../include/ExplorationInterface.hpp"
#include "../include/InventoryInterface.hpp"
#include "../include/EndingInterface.hpp"
#include "../include/MapsArray.hpp"

std::vector<Interface *> interfaces;

SDL_Renderer *Game::renderer = nullptr;
SDL_Texture *Game::pokemonsTexture = nullptr;
SDL_Texture *Game::characterTexture = nullptr;
int Game::level = 0;
int Game::inventoryLength = 0;

StarterInterface *starterInterface = nullptr;
AttackInterface *attackInterface = nullptr;
ExplorationInterface *explorationInterface = nullptr;
InventoryInterface *inventoryInterface = nullptr;

EndingInterface *endingInterface = nullptr;
Pokemon *attackedPokemon = nullptr;

Pokemon *attackerPokemon = nullptr;
Battle *battle = nullptr;

Map *map = nullptr;
Pokemon *Game::pokedex[MAX_POKEMONS_POKEDEX];
Pokemon *Game::inventory[MAX_POKEMON_INV];

/**
 * @brief Initialize the game (assign the window, renderer, define the game as running)
 * @param title
 */
Game::Game(const std::string title) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        TTF_Init();
        window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                                  WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, 0);
        Game::pokemonsTexture = IMG_LoadTexture(Game::renderer, "assets/pokemon_sprite.png");

        starterInterface = new StarterInterface(this);
        explorationInterface = new ExplorationInterface(this);
        attackInterface = new AttackInterface(this, attackedPokemon, attackerPokemon);
        inventoryInterface = new InventoryInterface(this);
        endingInterface = new EndingInterface(this);
        map = explorationInterface->getMap();
        battle = attackInterface->getBattle();

        interfaces.push_back(starterInterface);
        interfaces.push_back(explorationInterface);
        interfaces.push_back(attackInterface);
        interfaces.push_back(inventoryInterface);
        interfaces.push_back(endingInterface);

        isRunning = true;
        level = 0;
    }
}

Game::~Game() {}

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
    level++;
    Battle::state = "inactive";
    map->loadMap(allMaps[Game::level]);
    changeInterfaceToExploration();
}

/**
 * @brief Change the interface to exploration
 */
void Game::changeInterfaceToExploration() {
    setActivity("inExploration");
}

/**
 * @brief Change the interface to inventory
 */
void Game::changeInterfaceToInventory() {
    setActivity("inInventory");
}

/**
 * @brief Change the interface to ending
 */
void Game::changeInterfaceToEnding() {
    setActivity("inEnd");
}

/**
 * @brief Quit the game properly
 */
void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

/**
 * @brief Refresh the game
 */
void Game::refresh() {
    for (size_t i = 0; i < interfaces.size(); i++) {
        if (interfaces[i]->isActive()) {
            interfaces[i]->handleEvents();
            interfaces[i]->update();
            interfaces[i]->render();
        }
    }
}
