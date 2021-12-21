#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include "../include/Game.hpp"
#include "../include/Text.hpp"
#include "../include/Colors.hpp"

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
    Text::message = text;
    Text::color = color;
    Text::font = createFont(fontName);
    Text::surface = TTF_RenderText_Solid(Text::font, Text::message.c_str(), Text::color);
    Text::texture = SDL_CreateTextureFromSurface(Game::renderer, Text::surface);
    Text::destRect = createDestRect(Text::font, Text::message);
}

/**
 * @brief Draw the text
 */
void Text::draw() {
    SDL_RenderCopy(Game::renderer, Text::texture, NULL, &(Text::destRect));
    SDL_FreeSurface(Text::surface);
    SDL_DestroyTexture(Text::texture);
}

/**
 * @brief Change the text
 * @param newText
 */
void Text::changeText(std::string newText) {
    Text::message = newText.c_str();
    Text::surface = TTF_RenderText_Solid(Text::font, Text::message.c_str(), Text::color);
    Text::texture = SDL_CreateTextureFromSurface(Game::renderer, Text::surface);
    Text::destRect = createDestRect(Text::font, Text::message);
}

/**
 * @brief Returns a TTF_Font* from a simple string if the font is located in assets.
 * @param fontName
 * @return TTF_Font*
 */
TTF_Font *createFont(std::string fontName) {
    std::string fullFontName = "./assets/" + fontName + ".ttf";
    TTF_Font *font = TTF_OpenFont(fullFontName.c_str(), 24);

    if (font == nullptr) {
        std::cout << fullFontName << " -> " << "Font not found" << std::endl;
    }

    return font;
}

/**
 * @brief Create a SDL_Rect by using the TTF_SizeText to calculate the right width/height of the font
 * @param font
 * @param text
 * @return SDL_Rect
 */
SDL_Rect createDestRect(TTF_Font *font, std::string text) {
    SDL_Rect destMessage;
    destMessage.x = destMessage.y = 0;

    if (TTF_SizeText(font, text.c_str(), &destMessage.w, &destMessage.h)) {
        std::cout << TTF_GetError() << std::endl;
    }

    return destMessage;
}