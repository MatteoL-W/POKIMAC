#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include "../include/Game.hpp"
#include "../include/Text.hpp"

Text::Text() {

}

Text::~Text() {

}

/**
 * @brief Create a text
 * @param text
 * @param color
 * @param fontName
 */
void Text::create(std::string text, SDL_Color color, std::string fontName) {
    std::string fullFontName = "./assets/" + fontName + ".ttf";
    TTF_Font* font = TTF_OpenFont(fullFontName.c_str(), 24);

    if (font == nullptr) {
        std::cout << fullFontName << " -> " << "Font not found" << std::endl;
    }

    //TTF_SizeText(TTF_Font *font, const char *text, int *w, int *h)
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* message = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage);

    SDL_Rect destMessage;
    destMessage.x = destMessage.y = 0;
    destMessage.w = destMessage.h = 100;

    SDL_RenderCopy(Game::renderer, message, NULL, NULL);
    SDL_RenderPresent(Game::renderer);

    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
}