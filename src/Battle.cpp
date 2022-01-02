#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/AttackInterface.hpp"
#include "../include/Battle.hpp"
#include "../include/Text.hpp"
#include "../include/Colors.hpp"

Text* enemyTextHP = new Text();

Battle::Battle(Pokemon *enemy, Pokemon *myPokemon) {
    Battle::enemyPokemon = enemy;
    Battle::pokemon = myPokemon;

    load();
}

Battle::~Battle() {

}

/**
 * @brief Load the battle
 */
void Battle::load() {
    enemyTextHP->create("", WhiteColor, "Press");
}

/**
 * @brief Draw the battle scne
 */
void Battle::draw() {
    drawBackground();
    drawPokemons();
}

/**
 * @brief Draw the background of the battle scene
 */
void Battle::drawBackground() {
    SDL_SetRenderDrawColor(Game::renderer, 51, 57, 58, 255);

    SDL_Texture *sceneBackgroundTexture = IMG_LoadTexture(Game::renderer, "assets/attack_scene.png");

    SDL_Rect destBackground;
    destBackground.w = Game::WINDOW_WIDTH;
    destBackground.h = Game::WINDOW_HEIGHT / 2;
    destBackground.x = destBackground.y = 0;

    SDL_RenderCopy(Game::renderer, sceneBackgroundTexture, NULL, &destBackground);
}

void Battle::drawPokemons() {
    // Drawing enemy pokemon
    SDL_Texture *pokemonsTexture = IMG_LoadTexture(Game::renderer, "assets/pokemon_sprite.png");

    SDL_Rect destEnemy, srcEnemy;
    destEnemy.w = destEnemy.h = 64;
    destEnemy.y = 220;
    destEnemy.x = 175;
    srcEnemy.w = srcEnemy.h = 32;
    srcEnemy.x = enemyPokemon->getXSpriteCoordinate();
    srcEnemy.y = enemyPokemon->getYSpriteCoordinate();

    SDL_RenderCopy(Game::renderer, pokemonsTexture, &srcEnemy, &destEnemy);
    //________________________________________________________________________

    // Drawing hp
    std::string enemyHP = "19 / " + std::to_string(enemyPokemon->getHealthPoint());

    enemyTextHP->changeText(enemyHP);
    enemyTextHP->changeDestRect(120, 323);
    enemyTextHP->draw();
}