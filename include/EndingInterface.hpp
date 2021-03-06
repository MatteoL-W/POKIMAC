#pragma once

#include "Game.hpp"
#include "Interface.hpp"
#include "Ending.hpp"

class EndingInterface : public Interface {
public:
    EndingInterface(Game *game) {
        EndingInterface::game = game;
        EndingInterface::ending = new Ending();
    };

    ~EndingInterface();

    void handleEvents();

    void update() {};

    void render();

    bool isActive();


private:
    Game *game;

    Ending *ending;
};
