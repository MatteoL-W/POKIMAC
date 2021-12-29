#pragma once

#include "Interface.hpp"
#include "Game.hpp"
#include "Pokemon.hpp"

class AttackInterface : public Interface {
public:
    AttackInterface(Game *game, Pokemon *pokemon) {
        AttackInterface::game = game;
        AttackInterface::enemy = pokemon;
    };

    ~AttackInterface();

    void handleEvents();

    void update();

    void render();

private:
    Game *game;

    Pokemon *enemy;
};
