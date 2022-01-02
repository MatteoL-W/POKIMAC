#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/AttackInterface.hpp"
#include "../include/Battle.hpp"
#include "../include/Text.hpp"
#include "../include/Colors.hpp"

Text* enemyTextHP = new Text();
Text* firstAttackText = new Text();
Text* secondAttackText = new Text();
Text* dialogText = new Text();

// (cf. AttackFlags.hpp)
// Charge is the attack for TYPE_NORMAL (0)
// Tranch'Herbe is the attack for TYPE_PLANT (1)
// ...
std::string attacks[TYPES_LENGTHS] = {
        "Charge",
        "Tranch'Herbe",
        "Vibraqua",
        "Rebondifeu"
};

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
    firstAttackText->create("", WhiteColor, "Press");
    secondAttackText->create("", WhiteColor, "Press");
    dialogText->create("", WhiteColor, "Press");
}

/**
 * @brief Draw the battle scne
 */
void Battle::draw() {
    drawBackground();
    drawPokemons();
    drawDialog();
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
    SDL_Texture *pokemonPlatformTexture = IMG_LoadTexture(Game::renderer, "assets/attack_platform.png");

    SDL_Rect destEnemy, srcEnemy, destEnemyPlatform;
    destEnemy.w = destEnemy.h = 64;
    destEnemy.y = 180;
    destEnemy.x = 175;
    srcEnemy.w = srcEnemy.h = 32;
    srcEnemy.x = enemyPokemon->getXSpriteCoordinate();
    srcEnemy.y = enemyPokemon->getYSpriteCoordinate();

    destEnemyPlatform.w = 137;
    destEnemyPlatform.h = 46;
    destEnemyPlatform.x = 135;
    destEnemyPlatform.y = 210;

    SDL_RenderCopy(Game::renderer, pokemonPlatformTexture, NULL, &destEnemyPlatform);
    SDL_RenderCopy(Game::renderer, pokemonsTexture, &srcEnemy, &destEnemy);
    //________________________________________________________________________

    // Drawing enemy hp
    std::string enemyHP = "19 / " + std::to_string(enemyPokemon->getHealthPoint());

    enemyTextHP->changeText(enemyHP);
    enemyTextHP->changeDestRect(120, 323);
    enemyTextHP->draw();
}

void Battle::drawDialog() {
    if (pokemon == nullptr) {
        //std::cout << "faire définir le pokmeon";
    //}

    //else {
        dialogText->changeText("Tortank vous a enlevé 7 pv");
        dialogText->changeDestRect(86,515);
        dialogText->draw();

        firstAttackText->changeText("[E] " + attacks[0]);
        firstAttackText->changeDestRect(86,630);
        //TODO: increase font
        firstAttackText->draw();

        secondAttackText->changeText("[G] " + attacks[1]);
        //TODO: increase font
        secondAttackText->changeDestRect(86,660);
        secondAttackText->draw();
    }
}