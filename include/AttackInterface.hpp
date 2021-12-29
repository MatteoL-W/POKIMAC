#pragma once

#include "Interface.hpp"
#include "Game.hpp"
#include "Pokemon.hpp"

class AttackInterface : public Interface {
public:
    AttackInterface(Game *game, Pokemon *attackedPokemon, Pokemon *attackerPokemon) {
        AttackInterface::game = game;
        AttackInterface::enemy = attackedPokemon;
        AttackInterface::pokemon = attackerPokemon;
    };

    ~AttackInterface();

    void handleEvents();

    void update();

    void render();

private:
    Game *game;

    Pokemon *enemy;

    Pokemon *pokemon;
};
