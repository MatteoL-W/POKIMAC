#pragma once

#include <SDL2/SDL.h>
#include "Battle.hpp"
#include "Game.hpp"
#include "Interface.hpp"
#include "Pokemon.hpp"

class AttackInterface : public Interface {
public:
    AttackInterface(Game *game, Pokemon *attackedPokemon, Pokemon *attackerPokemon) {
        AttackInterface::game = game;
        AttackInterface::enemy = attackedPokemon;
        AttackInterface::pokemon = attackerPokemon;
        AttackInterface::battle = new Battle(enemy, pokemon);
    };

    ~AttackInterface();

    void handleEvents();

    void update();

    void render();

private:
    Game *game;

    Pokemon *enemy;

    Pokemon *pokemon;

    Battle *battle;
};
