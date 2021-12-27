#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

TTF_Font *createFont(std::string fontName);

SDL_Rect createDestRect(TTF_Font *font, std::string text, int x, int y);

class Text {
public:
    Text();

    ~Text();

    void create(std::string text, SDL_Color color, std::string fontName);

    void draw();

    void changeText(std::string newText);

    void changeColor(SDL_Color newColor);

    void changeDestRect(int x, int y);

    std::string getText() { return message; };

private:
    std::string message;

    TTF_Font *font;

    SDL_Surface *surface;

    SDL_Color color;

    SDL_Texture *texture;

    SDL_Rect destRect;
};
