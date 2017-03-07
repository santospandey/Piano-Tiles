#include <iostream>
#include "color.h"
#include <SDL2/SDL.h>

class Tile{

    private:
        int posX;
        int posY;
        int width;
        int height;
        color rgbColor;

    public:
        // default constructor
        Tile();

        // parameterized constructor
        Tile(int posX, int posY, int width, int height);

        // set the rgb value of color
        void setColor(int r, int g, int b, int alp);

        // render to main window
        void render(SDL_Renderer* renderer);
};
