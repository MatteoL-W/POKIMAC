#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "../include/AttacksFlag.hpp"
#include "../include/Inventory.hpp"
#include "../include/Game.hpp"
#include "../include/Pokemon.hpp"
#include "../include/Text.hpp"
#include "../include/Colors.hpp"

/**
 * @brief Draw the inventory
 */
void Inventory::draw() {
    // Draw the background
    SDL_RenderCopy(Game::renderer, backgroundTexture, NULL, NULL);

    // Draw The blocks and the pokemons
    int xOperator = 0, yOperator = 0;
    for (int i = 0; i < Game::inventoryLength; i++) {
        Pokemon *pokemon = Game::inventory[i];
        xOperator = i % 3;
        if (i > 2) {
            yOperator = 1;
        }
        drawBlock(xOperator, yOperator);
        drawPokemon(pokemon, xOperator, yOperator);
    }

}

void Inventory::drawBlock(int xOperator, int yOperator) {
    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);

    SDL_Rect blockItem;
    blockItem.x = (Game::WINDOW_WIDTH / 3) * xOperator + 20;
    blockItem.y = (Game::WINDOW_HEIGHT / 2) * yOperator + 20;
    blockItem.w = Game::WINDOW_WIDTH / 3 - 40;
    blockItem.h = Game::WINDOW_HEIGHT / 2 - 40;

    SDL_RenderFillRect(Game::renderer, &blockItem);
}

void Inventory::drawPokemon(Pokemon *pokemon, int xOperator, int yOperator) {
    SDL_Rect srcPokemon, dstPokemon;
    srcPokemon.x = pokemon->getXSpriteCoordinate();
    srcPokemon.y = pokemon->getYSpriteCoordinate();
    srcPokemon.w = srcPokemon.h = 32;

    drawPokemonSprite(xOperator, yOperator, &srcPokemon, &dstPokemon);
    drawPokemonInfo(xOperator, yOperator, pokemon, dstPokemon);
}

void Inventory::drawPokemonSprite(int xOperator, int yOperator, SDL_Rect *srcPokemon, SDL_Rect *dstPokemon) {
    dstPokemon->x = (Game::WINDOW_WIDTH / 3) * xOperator + 20;
    dstPokemon->y = (Game::WINDOW_HEIGHT / 2) * yOperator + 20;
    dstPokemon->w = dstPokemon->h = Game::WINDOW_WIDTH / 3 - 40;

    SDL_RenderCopy(Game::renderer, Game::pokemonsTexture, srcPokemon, dstPokemon);
}

void Inventory::drawPokemonInfo(int xOperator, int yOperator, Pokemon *pokemon, SDL_Rect dstPokemon) {
    nameText->create(pokemon->getName(), BlackColor, "Press");
    nameText->changeDestRect(getPadding(dstPokemon.w, nameText->getDestRect()) + dstPokemon.x,
                             yOperator * (dstPokemon.y - 20) + dstPokemon.h + 25);

    typeText->create(types[pokemon->getType()], BlackColor, "Press");
    typeText->changeDestRect(getPadding(dstPokemon.w, typeText->getDestRect()) + dstPokemon.x,
                             yOperator * (dstPokemon.y - 20) + dstPokemon.h + 25 + 30);

    std::string pokemonHP =
            std::to_string(pokemon->getHealthPoint()) + " / " + std::to_string(pokemon->getMaxHealthPoint());
    healthPointText->create(pokemonHP, BlackColor, "Press");
    healthPointText->changeDestRect(getPadding(dstPokemon.w, healthPointText->getDestRect()) + dstPokemon.x,
                                    yOperator * (dstPokemon.y - 20) + dstPokemon.h + 25 + 30 * 2);

    nameText->draw();
    typeText->draw();
    healthPointText->draw();
}

int getPadding(int blockWidth, int textWidth) {
    return (blockWidth - textWidth) / 2;
}