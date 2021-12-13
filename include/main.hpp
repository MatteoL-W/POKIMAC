#ifndef FLAG_MAIN
#define FLAG_MAIN

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

bool isGameRunning = false;
const int FPS = 60;
const int FRAME_DELAY = 1000 / FPS;

Uint32 frameStart;
int frameTime;

#endif