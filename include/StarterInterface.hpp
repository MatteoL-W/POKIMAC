#pragma once

#include "Interface.hpp"
#include "Game.hpp"
#include "Map.hpp"
#include "Starter.hpp"

class StarterInterface : public Interface {
public:
    StarterInterface(Game *game) {
        StarterInterface::game = game;
        StarterInterface::starter = new Starter();
    }

    ~StarterInterface() = default;

    void handleEvents() override;

    void update() override;

    void render() override;

    bool isActive() override;

private:
    bool readingRules = true;

    Game *game;

    Starter *starter;

};
