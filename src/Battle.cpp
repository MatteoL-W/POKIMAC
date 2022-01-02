#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/AttackInterface.hpp"
#include "../include/Battle.hpp"

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
    // là le pokemon est pas mis dans le enemyPokemon encore
//    std::cout << enemyPokemon;
//    SDL_Texture *pokemonsTexture = IMG_LoadTexture(Game::renderer, "assets/pokemon_sprite.png");
//
//    SDL_Rect destEnemy, srcEnemy;
//    destEnemy.w = destEnemy.h = 64;
//    destEnemy.x = destEnemy.y = 0;
//    srcEnemy.w = srcEnemy.h = 32;
//    srcEnemy.x = enemyPokemon->getXSpriteCoordinate();
//    srcEnemy.y = enemyPokemon->getYSpriteCoordinate();
//
//    SDL_RenderCopy(Game::renderer, pokemonsTexture, &srcEnemy, &destEnemy);
//
//    std::cout << SDL_GetError();
}