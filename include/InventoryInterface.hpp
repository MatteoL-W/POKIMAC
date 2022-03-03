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

    ~InventoryInterface() = default;

    void handleEvents() override;

    void update() override {};

    void render() override;

    bool isActive() override;

private:
    Game *game;

    Inventory *inventory;
};
