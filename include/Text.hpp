#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Text {
public:
    Text();

    ~Text();

    void create(std::string text, SDL_Color color, std::string fontName);

private:
};
