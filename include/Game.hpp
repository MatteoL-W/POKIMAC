#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include "Pokemon.hpp"

const int MAX_POKEMON_INV = 6;
const int MAX_POKEMONS_POKEDEX = 38;

class Game {
public:
    Game(const std::string title);

    ~Game();

    void init(const std::string title);

    void changeInterfaceToAttack(Pokemon *enemy);

    void changeInterfaceToExplorationAndLevelUp();

    void changeInterfaceToExploration();

    void changeInterfaceToInventory();

    void changeInterfaceToEnding();

    void clean();

    void refresh();

    void setRunning(bool newState) { isRunning = newState; }

    bool running() { return isRunning; };

    bool starting() {
        if (activity == "inStarter") {
            return true;
        }
        return false;
    };

    bool exploring() {
        if (activity == "inExploration") {
            return true;
        }
        return false;
    };

    bool attacking() {
        if (activity == "inAttack") {
            return true;
        }
        return false;
    };

    bool displayingInventory() {
        if (activity == "inInventory") {
            return true;
        }
        return false;
    };

    bool ending() {
        if (activity == "inEnd") {
            return true;
        }
        return false;
    }

    void setActivity(std::string newActivity) { activity = newActivity; };

    static SDL_Renderer *renderer;

    static Pokemon *pokedex[MAX_POKEMONS_POKEDEX];

    static Pokemon *inventory[MAX_POKEMON_INV];

    static int inventoryLength;

    static int level;

    static SDL_Texture *pokemonsTexture;

    static SDL_Texture *characterTexture;

    static const int WINDOW_WIDTH = 750;

    static const int WINDOW_HEIGHT = 750;

    static constexpr float SCALE_CAMERA = WINDOW_WIDTH / (float) 800;

    SDL_Event event;

private:
    bool isRunning = false;

    std::string activity = "inStarter";

    SDL_Window *window;
};
