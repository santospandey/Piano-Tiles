#include "tiles.h"

// default constructor
Tile::Tile(){
    posX=0;
    posY=0;
    width=20;
    height=20;
}

// parameterized constructor
/*Tile::Tile(int x, int y, int w, int h){
    posX = x;
    posY = y;
    width = w;
    height = h;
}
*/

// set dimension of tile.
void Tile::setDimension(int x, int y, int w, int h){
    posX = x;
    posY = y;
    width = w;
    height = h;
}

// set the color of the tile
void Tile::setColor(int r, int g, int b, int alp){
    rgbColor.red = r;
    rgbColor.green = g;
    rgbColor.blue = b;
    rgbColor.alpha = alp;
}

// render to main window
void Tile::render(SDL_Renderer* renderer){

    SDL_Rect fillRect = {posX, posY, width, height};
    SDL_SetRenderDrawColor(renderer, rgbColor.red, rgbColor.green, rgbColor.blue, rgbColor.alpha);
    SDL_RenderFillRect(renderer, &fillRect);
}

// call to move right the tile
void Tile::moveRight(){
    posX += 5;
}

void Tile::moveLeft(){
    posX -= 5;
}

void Tile::moveUp(){
    posY -= 5;
}

void Tile::moveDown(){
    posY += 5;
}
