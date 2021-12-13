#ifndef FLAG_GAME
#define FLAG_GAME
#include <iostream>

class Game {
    public:
        Game();
        ~Game();

        void init(const std::string title);

        void handleEvents();
        void update();
        void render();
        void clean();

        bool running() { return isRunning; };

    private:
        const int WINDOW_WIDTH = 800;
        const int WINDOW_HEIGHT = 600;

        bool isRunning = false;
        int updateCounter = 0;

        SDL_Window* window;
        SDL_Renderer* renderer;
};

/*TODO: pouvoir retirer ça sans provoquer de bugs! (dans le makefile, lié game.cpp à gameobject.hpp aussi)*/
class GameObject {
    public:
        GameObject(const std::string textureSheet, SDL_Renderer* rendererParameter, int x, int y);
        ~GameObject();

        void update();
        void render();

    private:
        int xPosition;
        int yPosition;

        SDL_Renderer* renderer;
        SDL_Texture* objectTexture;
        SDL_Rect srcRect, dstRect;

};

#endif