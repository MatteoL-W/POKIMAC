#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "../include/Ending.hpp"
#include "../include/Inventory.hpp"
#include "../include/Text.hpp"
#include "../include/Colors.hpp"
#include "../include/Map.hpp"
#include "../include/Game.hpp"
#include "../include/Pokemon.hpp"


void Ending::draw() {
    // Draw the background
    SDL_RenderCopy(Game::renderer, backgroundTexture, NULL, NULL);

    // Draw the pokemons
    int xOperator = 0;
    for (int i = 0; i < Game::inventoryLength; i++) {
        Pokemon *pokemon = Game::inventory[i];
        drawPokemons(pokemon, xOperator);
        xOperator++;
    }

    drawSprite();
    //drawText();

}


void Ending::drawSprite() {
    srcPlayer.x = srcPlayer.y = 0;
    destPlayer.w = destPlayer.h = (Game::WINDOW_WIDTH / 4);
    destPlayer.x = (Game::WINDOW_WIDTH / 2) - (destPlayer.w / 2);
    destPlayer.y = Game::WINDOW_WIDTH * 2/5;

    SDL_RenderCopy(Game::renderer, playerTexture, &srcPlayer, &destPlayer);
}

void Ending::drawPokemons(Pokemon *pokemon, int xOperator) {
    srcPokemon.x = pokemon->getXSpriteCoordinate();
    srcPokemon.y = pokemon->getYSpriteCoordinate();
    srcPokemon.w = srcPokemon.h = 32; 

    destPokemon.w = destPokemon.h = (Game::WINDOW_WIDTH / 6) - 40;
    //destPokemon.x = 20 + destPokemon.w * xOperator;
    destPokemon.x = (Game::WINDOW_WIDTH / 6) * xOperator + 20;
    destPokemon.y = Game::WINDOW_WIDTH * 3/5; 

    SDL_RenderCopy(Game::renderer, Game::pokemonsTexture, &srcPokemon, &destPokemon);
}

// void Ending::drawText() {
//     congratsText->create("Bravo !", WhiteColor, "Press");
//     congratsText->changeDestRect(86, Game::WINDOW_WIDTH * 1/6);

//     creditsText->create("Matteo Leclercq, Emily-Rose Strich", WhiteColor, "Press");
//     creditsText->changeDestRect(86, Game::WINDOW_WIDTH * 5/6);

//     congratsText->draw();
//     creditsText->draw();
// }