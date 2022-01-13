#pragma once

#include "Interface.hpp"
#include "Game.hpp"
#include "Map.hpp"

class StarterInterface : public Interface {
public:
    StarterInterface(Game *game) {
        StarterInterface::game = game;
    }

    ~StarterInterface();

    void handleEvents();

    void update();

    void render();

private:
    Game *game;

};
