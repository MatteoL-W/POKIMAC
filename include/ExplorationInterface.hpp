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

    void handleEvents() override;

    void update() override;

    void render() override;

    bool isActive() override;

    Map *getMap() { return map; };

private:
    Game *game;

    Map *map;
};
