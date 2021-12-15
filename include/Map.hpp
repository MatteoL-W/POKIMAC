#ifndef FLAG_MAP
#define FLAG_MAP

class Map {
public:
    static const int MAP_HEIGHT = 20;
    static const int MAP_WIDTH = 25;

    Map();

    ~Map();

    void loadMap(int arr[MAP_HEIGHT][MAP_WIDTH]);

    void drawMap();

private:
    SDL_Rect src, dest;
    SDL_Texture *tilesetMapTexture;
    int map[MAP_HEIGHT][MAP_WIDTH];
};

#endif