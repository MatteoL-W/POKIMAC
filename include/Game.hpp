#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include "Pokemon.hpp"

const int MAX_POKEMON_INV = 6;

class Game {
public:
    Game();

    ~Game();

    void init(const std::string title);

    void changeInterfaceToAttack(Pokemon *enemy);

    void changeInterfaceToExplorationAndLevelUp();

    void changeInterfaceToExploration();

    void changeInterfaceToInventory();

    void clean();

    void refresh();

    void setRunning(bool newState) { isRunning = newState; }

    bool running() { return isRunning; };

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

    void setActivity(std::string newActivity) { activity = newActivity; };

    static SDL_Renderer *renderer;

    static Pokemon *inventory[MAX_POKEMON_INV];

    static int inventoryLength;

    static int level;

    static const int WINDOW_WIDTH = 1000;
    static const int WINDOW_HEIGHT = 1000;
    static constexpr float SCALE_CAMERA = WINDOW_WIDTH / (float)800;

    SDL_Event event;

private:
    bool isRunning = false;

    std::string activity = "inExploration";

    SDL_Window *window;
};
