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

    ~EndingInterface() = default;

    void handleEvents() override;

    void update() override {};

    void render() override;

    bool isActive() override;


private:
    Game *game;

    Ending *ending;
};
