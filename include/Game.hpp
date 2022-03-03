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

    void changeInterfaceToAttack(Pokemon *enemy);

    void changeInterfaceToExplorationAndLevelUp();

    void changeInterfaceToExploration();

    void changeInterfaceToInventory();

    void changeInterfaceToEnding();

    void clean();

    void refresh();

    void setRunning(bool newState) { isRunning = newState; }

    bool running() { return isRunning; };

    bool starting() { return activity == "inStarter"; };

    bool exploring() { return activity == "inExploration"; };

    bool attacking() { return activity == "inAttack"; };

    bool displayingInventory() { return activity == "inInventory"; };

    bool ending() { return activity == "inEnd"; };

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
