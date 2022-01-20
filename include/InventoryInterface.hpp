#pragma once

#include "Game.hpp"
#include "Interface.hpp"
#include "Inventory.hpp"

class InventoryInterface : public Interface {
public:
    InventoryInterface(Game *game) {
        InventoryInterface::game = game;
        InventoryInterface::inventory = new Inventory();
    };

    ~InventoryInterface();

    void handleEvents();

    void update();

    void render();

    bool isActive();

private:
    Game *game;

    Inventory *inventory;
};
