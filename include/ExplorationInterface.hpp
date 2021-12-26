#pragma once

#include "Interface.hpp"
#include "Game.hpp"
#include "Map.hpp"

class ExplorationInterface : public Interface {
public:
    ExplorationInterface(Game *game) {
        ExplorationInterface::game = game;
        ExplorationInterface::map = new Map(true);
    };

    ~ExplorationInterface();

    void handleEvents();

    void update();

    void render();

private:
    Game *game;

    Map *map;
};
