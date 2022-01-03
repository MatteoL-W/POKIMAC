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
Text* thirdPokemonText = new Text();
Text* fourthPokemonText = new Text();
Text* fifthPokemonText = new Text();
Text* sixPokemonText = new Text();
Text* dialogText = new Text();

Text* pokemonListsTexts[6] = {
        firstAttackText,
        secondAttackText,
        thirdPokemonText,
        fourthPokemonText,
        fifthPokemonText,
        sixPokemonText
};

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
    firstAttackText->create("", WhiteColor, "Press");
    secondAttackText->create("", WhiteColor, "Press");
    thirdPokemonText->create("", WhiteColor, "Press");
    fourthPokemonText->create("", WhiteColor, "Press");
    fifthPokemonText->create("", WhiteColor, "Press");
    sixPokemonText->create("", WhiteColor, "Press");
    dialogText->create("", WhiteColor, "Press");

    sceneBackgroundTexture = IMG_LoadTexture(Game::renderer, "assets/attack_scene.png");
    pokemonsTexture = IMG_LoadTexture(Game::renderer, "assets/pokemon_sprite.png");
    pokemonPlatformTexture = IMG_LoadTexture(Game::renderer, "assets/attack_platform.png");
}

/**
 * @brief Draw the battle scne
 */
void Battle::draw() {
    drawBackground();
    drawPokemon(enemyPokemon, 175, 180);
    drawDialog();
}

/**
 * @brief Draw the background of the battle scene
 */
void Battle::drawBackground() {
    SDL_SetRenderDrawColor(Game::renderer, 51, 57, 58, 255);

    SDL_Rect destBackground;
    destBackground.w = Game::WINDOW_WIDTH;
    destBackground.h = Game::WINDOW_HEIGHT / 2;
    destBackground.x = destBackground.y = 0;

    SDL_RenderCopy(Game::renderer, sceneBackgroundTexture, NULL, &destBackground);
}

void Battle::drawPokemon(Pokemon *pokemon, int x, int y) {
    // Drawing pokemon
    SDL_Rect destPokemon, srcPokemon, destPlatform;
    destPokemon.w = destPokemon.h = 64;
    destPokemon.x = x;
    destPokemon.y = y;
    srcPokemon.w = srcPokemon.h = 32;
    srcPokemon.x = pokemon->getXSpriteCoordinate();
    srcPokemon.y = pokemon->getYSpriteCoordinate();

    destPlatform.w = 137;
    destPlatform.h = 46;
    destPlatform.x = destPokemon.x - 40;
    destPlatform.y = destPokemon.y + 30;

    SDL_RenderCopy(Game::renderer, pokemonPlatformTexture, NULL, &destPlatform);
    SDL_RenderCopy(Game::renderer, pokemonsTexture, &srcPokemon, &destPokemon);
    //________________________________________________________________________

    // Drawing hp

    //std::string enemyHP = std::to_string(pokemon->getHealthPoint()) + " / " + std::to_string(pokemon->getMaxHealthPoint());
    std::string enemyHP = "19 / " + std::to_string(pokemon->getHealthPoint());
    enemyTextHP->create(enemyHP, WhiteColor, "Press");
    enemyTextHP->changeDestRect(destPokemon.x - 55, destPokemon.y + 140);
    enemyTextHP->draw();

    //________________________________________________________________________
}

void Battle::drawDialog() {
    if (pokemon == nullptr) {
        dialogText->changeText("Choisissez votre pokemon");

        //for (int i = 0; i < inventoryLength; i++) {
        for (int i = 0; i < 6; i++) {
            //pokemonListsTexts[i]->changeText("[" + std::to_string(i) + "] " + inventory[i]->getName());
            pokemonListsTexts[i]->changeText("Pokemon");
            pokemonListsTexts[i]->changeDestRect(86, 550 + 30 * i);
            pokemonListsTexts[i]->draw();
        }
    }

    else {
        dialogText->changeText("Tortank vous a enlevé 7 pv");

        firstAttackText->changeText("[E] " + attacks[0]);
        //TODO: increase font
        firstAttackText->draw();

        secondAttackText->changeText("[G] " + attacks[1]);
        //TODO: increase font
        secondAttackText->draw();
    }

    firstAttackText->changeDestRect(86,630);
    secondAttackText->changeDestRect(86,660);
    dialogText->changeDestRect(86,485);
    dialogText->draw();
}