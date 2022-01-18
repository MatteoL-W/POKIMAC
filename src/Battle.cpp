#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/AttackInterface.hpp"
#include "../include/Battle.hpp"
#include "../include/Text.hpp"
#include "../include/Colors.hpp"
#include "../include/Game.hpp"

std::string Battle::state = "inactive";

Text *enemyTextHP = new Text();

Text *firstAttackText = new Text();
Text *secondAttackText = new Text();
Text *thirdPokemonText = new Text();
Text *fourthPokemonText = new Text();
Text *fifthPokemonText = new Text();
Text *sixPokemonText = new Text();
Text *exitText = new Text();

Text *dialogText = new Text();

Text *pokemonListsTexts[6] = {
        firstAttackText,
        secondAttackText,
        thirdPokemonText,
        fourthPokemonText,
        fifthPokemonText,
        sixPokemonText
};

int maxWidthBar = 240, dynamicRed, dynamicGreen;

// (cf. AttackFlags.hpp)
// Charge is the attack for TYPE_NORMAL (0)
// Tranch'Herbe is the attack for TYPE_PLANT (1)
// ...
std::string attacks[TYPES_LENGTHS] = {
        "Charge",
        "Tranch'Herbe",
        "Vibraqua",
        "Rebondifeu",
        "Lame de Roc",
        "Laser Glace"
};

Battle::Battle(Pokemon *enemy, Pokemon *myPokemon, Game *game) {
    Battle::enemyPokemon = enemy;
    Battle::pokemon = myPokemon;
    Battle::game = game;

    load();
}

Battle::~Battle() {

}

/**
 * @brief Load texture and text of the battle
 */
void Battle::load() {
    firstAttackText->create("", WhiteColor, "Press");
    secondAttackText->create("", WhiteColor, "Press");
    thirdPokemonText->create("", WhiteColor, "Press");
    fourthPokemonText->create("", WhiteColor, "Press");
    fifthPokemonText->create("", WhiteColor, "Press");
    sixPokemonText->create("", WhiteColor, "Press");
    exitText->create("", WhiteColor, "Press");
    dialogText->create("", WhiteColor, "Press");

    sceneBackgroundTexture = IMG_LoadTexture(Game::renderer, "assets/attack_scene.png");
    pokemonPlatformTexture = IMG_LoadTexture(Game::renderer, "assets/attack_platform.png");
}

/**
 * @brief Method to reload before every battle
 */
void Battle::reload() {
    setPokemon(nullptr);
}

/**
 * @brief Draw the battle secne
 */
void Battle::draw() {
    drawBackground();
    drawPokemonGraphics();
    drawDialog();
}

/**
 * @brief Draw the background of the battle scene
 */
void Battle::drawBackground() {
    SDL_SetRenderDrawColor(Game::renderer, 51, 57, 58, 255);
    SDL_RenderClear(Game::renderer);

    SDL_Rect destBackground;
    destBackground.w = Game::WINDOW_WIDTH;
    destBackground.h = Game::WINDOW_HEIGHT / 2;
    destBackground.x = destBackground.y = 0;

    SDL_RenderCopy(Game::renderer, sceneBackgroundTexture, NULL, &destBackground);
}

/**
 * @brief Order the draw of enemy and pokemon graphics
 */
void Battle::drawPokemonGraphics() {
    // Drawing enemy pokemon
    drawPokemon(enemyPokemon, 175, 180);
    drawHealthPoint(enemyPokemon, 175, 180);
    //________________________________________________________________________

    // Drawing friend pokemon
    if (pokemon != nullptr) {
        drawPokemon(pokemon, Game::WINDOW_WIDTH - 250, 180);
        drawHealthPoint(pokemon, Game::WINDOW_HEIGHT - 250, 180);
    }
    //________________________________________________________________________
}

/**
 * @brief Draw the dialog (pokemon choice / attack)
 */
void Battle::drawDialog() {
    if (pokemon == nullptr) {
        Battle::state = "pokemonChoice";
        dialogText->changeText("Choisissez votre pokemon");

        for (int i = 0; i < Game::inventoryLength; i++) {
            pokemonListsTexts[i]->changeText("[" + std::to_string(i) + "] " + Game::inventory[i]->getName() + " - " +
                                             std::to_string(Game::inventory[i]->getHealthPoint()) + "pv");

            if (Game::inventory[i]->getHealthPoint() == 0) {
                pokemonListsTexts[i]->changeColor(GreyColor);
            }
            pokemonListsTexts[i]->changeDestRect(86, 550 + 30 * i);
            pokemonListsTexts[i]->changeFont("Press", 22);
            pokemonListsTexts[i]->draw();
        }

        exitText->changeText("[EXIT] Annuler");
        exitText->changeFont("Press", 22);
        exitText->changeDestRect(86, 550 + 30 * Game::inventoryLength);
        exitText->draw();
    } else {
        dialogText->changeText("Choisissez votre attaque");

        firstAttackText->changeFont("Press", 32);
        firstAttackText->changeText("[E] " + attacks[0]);
        firstAttackText->changeDestRect(86, 580);
        firstAttackText->draw();

        secondAttackText->changeFont("Press", 32);
        secondAttackText->changeText("[G] " + attacks[pokemon->getType()]);
        secondAttackText->changeDestRect(86, 630);
        secondAttackText->draw();
    }

    dialogText->changeDestRect(86, 485);
    dialogText->draw();
}

/**
 * @brief Draw pokemon sprite and his platform
 * @param pokemon
 * @param x
 * @param y
 */
void Battle::drawPokemon(Pokemon *pokemon, int x, int y) {
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
    SDL_RenderCopy(Game::renderer, Game::pokemonsTexture, &srcPokemon, &destPokemon);
}

/**
 * @brief Draw the health point text and gauge
 * @param pokemon
 * @param x
 * @param y
 */
void Battle::drawHealthPoint(Pokemon *pokemon, int x, int y) {
    // Health Points
    std::string pokemonHP =
            std::to_string(pokemon->getHealthPoint()) + " / " + std::to_string(pokemon->getMaxHealthPoint());
    enemyTextHP->create(pokemonHP, WhiteColor, "Press");

    enemyTextHP->changeDestRect(x - 55, y + 140);
    enemyTextHP->draw();
    //________________________________________________________________________

    // Health Bar Max
    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);

    SDL_Rect healthBarMax;
    healthBarMax.x = x - 90;
    healthBarMax.y = y + 90;
    healthBarMax.w = maxWidthBar;
    healthBarMax.h = 25;

    SDL_RenderFillRect(Game::renderer, &healthBarMax);
    //________________________________________________________________________

    // Dynamic Health Bar
    int healthPercent = pokemon->getHealthPercent();
    // Green(0,255,0); Yellow(255,255,0); Red(255,0,0)
    dynamicGreen = (healthPercent < 50) ? healthPercent * 255 / 50 : 255;
    dynamicRed = (healthPercent < 50) ? 255 : 255 - (healthPercent * 255 / 50);
    SDL_SetRenderDrawColor(Game::renderer, dynamicRed, dynamicGreen, 0, 255);

    SDL_Rect healthBar;
    healthBar.x = x - 90;
    healthBar.y = y + 95;
    healthBar.w = maxWidthBar * healthPercent / 100;
    healthBar.h = 15;

    SDL_RenderFillRect(Game::renderer, &healthBar);
    //________________________________________________________________________
}

/**
 * @brief Let the enemy attack
 */
void Battle::enemysTurn() {
    if (enemyPokemon->getHealthPoint() == 0) {
        if (Game::level == 5) {
            game->changeInterfaceToEnding();
            return;
        }
        win();
        return;
    }

    // TODO: générer l'attaque de l'ennemie, la répercuter puis l'afficher
    Battle::state = "enemysTurn";

    if (pokemon->getHealthPoint() == 0) {
        lose();
    }
}

/**
 * @brief The player wins the battle
 */
void Battle::win() {
    Game::inventory[Game::inventoryLength] = getEnemy();
    Game::inventory[Game::inventoryLength]->heal();
    Game::inventoryLength++;
    game->changeInterfaceToExplorationAndLevelUp();
}

/**
 * @brief The player loses the battle
 */
void Battle::lose() {
    std::cout << "lose";
}