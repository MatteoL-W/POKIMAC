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

void Inventory::draw() {
    SDL_SetRenderDrawColor(Game::renderer, 51, 57, 58, 255);
    SDL_RenderClear(Game::renderer);

    // Health Bar Max
    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);

    SDL_Rect blockItem;
    blockItem.x = 20;
    blockItem.y = 20;
    blockItem.w = Game::WINDOW_WIDTH / 3 - 40;
    blockItem.h = Game::WINDOW_HEIGHT / 2 - 40;

    SDL_RenderFillRect(Game::renderer, &blockItem);

    //__________________________________________________________________
    Pokemon *pokemon = Game::inventory[0];

    SDL_Rect srcPokemon, dstPokemon;
    srcPokemon.x = pokemon->getXSpriteCoordinate();
    srcPokemon.y = pokemon->getYSpriteCoordinate();
    srcPokemon.w = srcPokemon.h = 32;

    dstPokemon.x = dstPokemon.y = 20;
    dstPokemon.w = dstPokemon.h = Game::WINDOW_WIDTH / 3 - 40;

    SDL_RenderCopy(Game::renderer, pokemonsTexture, &srcPokemon, &dstPokemon);

    //__________________________________________________________________
    Text *nameText = new Text();
    nameText->changeFont("Press", 18);
    nameText->create(pokemon->getName(), BlackColor, "Press");
    nameText->changeDestRect(getPadding(dstPokemon.w, nameText->getDestRect()) + dstPokemon.x, dstPokemon.h + 25);
    nameText->draw();

    Text *typeText = new Text();
    typeText->changeFont("Press", 18);
    typeText->create(types[pokemon->getType()], BlackColor, "Press");
    typeText->changeDestRect(getPadding(dstPokemon.w, typeText->getDestRect()) + dstPokemon.x, dstPokemon.h + 25 + 30);
    typeText->draw();

    Text *healthPointText = new Text();
    healthPointText->changeFont("Press", 15);
    std::string pokemonHP =
            std::to_string(pokemon->getHealthPoint()) + " / " + std::to_string(pokemon->getMaxHealthPoint());
    healthPointText->create(pokemonHP, BlackColor, "Press");
    healthPointText->changeDestRect(getPadding(dstPokemon.w, healthPointText->getDestRect()) + dstPokemon.x, dstPokemon.h + 25 + 30 * 2);
    healthPointText->draw();
}

int getPadding(int blockWidth, int textWidth) {
    return (blockWidth - textWidth) / 2;
}