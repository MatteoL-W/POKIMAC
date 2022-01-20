#pragma once

#include "Interface.hpp"
#include "Game.hpp"
#include "Map.hpp"
#include "Starter.hpp"

class StarterInterface : public Interface {
public:
    StarterInterface(Game *game) {
        StarterInterface::game = game;
        StarterInterface::starter = new Starter();
    }

    ~StarterInterface();

    void handleEvents();

    void update();

    void render();

    bool isActive();

private:
    Game *game;

    Starter *starter;

};
