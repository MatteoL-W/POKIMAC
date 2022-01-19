#pragma once

#include "Game.hpp"
#include "Interface.hpp"

class EndingInterface : public Interface {
public:
    EndingInterface(Game *game) {
        EndingInterface::game = game;
    };

    ~EndingInterface();

    void handleEvents();

    void update();

    void render();

    bool isActive();

private:
    Game *game;
};
