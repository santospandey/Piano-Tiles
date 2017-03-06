#include <iostream>
#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>


class Display{

private:

    //The window we'll be rendering to
    SDL_Window* window = NULL;

public:

    const int screenWidth=640;
    const int screenHeight=480;

    //The window renderer
    SDL_Renderer* renderer = NULL;

    //Starts up SDL and creates window
    bool init();

    //Loads media
    bool loadMedia();

    //Frees media and shuts down SDL
    void close();

    //Loads individual image as texture
    SDL_Texture* loadTexture(std::string path);
};
