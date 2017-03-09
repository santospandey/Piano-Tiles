#include <iostream>
#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include "tiles.h"
#include <stdlib.h>
#include <sstream>

// global variable for delay
//int delay = 40;

class Display{

private:

    const int screenWidth=480;
    const int screenHeight=640;

    //The window we'll be rendering to
    SDL_Window* window = NULL;

    //The window renderer
    SDL_Renderer* renderer = NULL;

    Tile tiles[9];

    int score = 0;

    SDL_Color White = {255, 255, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

    SDL_Surface* surfaceMessage;
    SDL_Texture* Message;

    SDL_Rect Message_rect; //create a rect

public:

    //Starts up SDL and creates window
    bool init();

    //Loads media
    bool loadMedia();

    // initialize position and color of tiles.
    void initializeTiles();

    // call to draw the stuff in the screen.
    void draw();

    // handle events like keyboard events and mouse events
    void handleEvents(SDL_Event& e);

    // Frees media and shuts down SDL
    void close();

    // generate random tile between 0 and n.
    void generateTile(int n);

    void textInput();
};
