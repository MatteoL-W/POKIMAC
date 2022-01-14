#pragma once

#include "Game.hpp"
#include "Interface.hpp"

class InventoryInterface : public Interface {
public:
    InventoryInterface(Game *game) {
        InventoryInterface::game = game;
    };

    ~InventoryInterface();

    void handleEvents();

    void update();

    void render();


private:
    Game *game;
};
