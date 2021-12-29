#include "../include/AttackInterface.hpp"
#include "../include/Battle.hpp"

Battle::Battle(Pokemon *enemy, Pokemon *myPokemon) {
    Battle::enemyPokemon = enemy;
    Battle::pokemon = myPokemon;
}

Battle::~Battle() {

}

/**
 * @brief Load the battle
 */
void Battle::load() {

}

/**
 * @brief Draw the battle scne
 */
void Battle::draw() {

}