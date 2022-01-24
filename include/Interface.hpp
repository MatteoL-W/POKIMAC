#pragma once

#include "Game.hpp"

class Interface {
public:
    virtual void handleEvents() = 0;

    virtual void update() = 0;

    virtual void render() = 0;

    virtual bool isActive() = 0;

private:
    Game *game;

};
