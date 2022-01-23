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

    drawSprite();

    // Draw the pokemons
    int xOperator = 0;
    for (int i = 0; i < Game::inventoryLength; i++) {
        Pokemon *pokemon = Game::inventory[i];
        drawPokemons(pokemon, xOperator);
        xOperator++;
    }

}


void Ending::drawSprite() {
    srcPlayer.x = srcPlayer.y = 0;
    srcPlayer.h = srcPlayer.w = 64;
    destPlayer.w = destPlayer.h = (Game::WINDOW_WIDTH / 4);
    destPlayer.x = (Game::WINDOW_WIDTH / 2) - (destPlayer.w / 2);
    destPlayer.y = Game::WINDOW_WIDTH * 3/10;

    SDL_RenderCopy(Game::renderer, Game::characterTexture, &srcPlayer, &destPlayer);
}

void Ending::drawPokemons(Pokemon *pokemon, int xOperator) {
    srcPokemon.x = pokemon->getXSpriteCoordinate();
    srcPokemon.y = pokemon->getYSpriteCoordinate();
    srcPokemon.w = srcPokemon.h = 32; 

    destPokemon.w = destPokemon.h = (Game::WINDOW_WIDTH / 6) - 40;
    destPokemon.x = (Game::WINDOW_WIDTH / 6) * xOperator + 20;
    destPokemon.y = Game::WINDOW_WIDTH * 3/5; 

    SDL_RenderCopy(Game::renderer, Game::pokemonsTexture, &srcPokemon, &destPokemon);
}
