#pragma once

#include <SDL2/SDL.h>
#include "Battle.hpp"
#include "Game.hpp"
#include "Interface.hpp"
#include "Pokemon.hpp"
#include "AttacksFlag.hpp"

class AttackInterface : public Interface {
public:
    AttackInterface(Game *game, Pokemon *attackedPokemon, Pokemon *attackerPokemon) {
        AttackInterface::game = game;
        AttackInterface::enemy = attackedPokemon;
        AttackInterface::pokemon = attackerPokemon;
        AttackInterface::battle = new Battle(enemy, pokemon, game);
    };

    ~AttackInterface() = default;

    void handleEvents() override;

    void update() override;

    void render() override;

    bool isActive() override;

    Battle *getBattle() { return battle; };

private:
    Game *game;

    Pokemon *enemy;

    Pokemon *pokemon;

    Battle *battle;

};
