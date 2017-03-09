#include "display.h"

bool Display::init(){

	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else{
        //Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		window = SDL_CreateWindow( "Piano Tiles", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN );

		if( window == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);
			if( renderer == NULL)
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( renderer, 0x00, 0xBB, 0xAC, 0x08);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

    return success;
}

bool Display::loadMedia(){
    //Loading success flag
	bool success = true;

	//Nothing to load
	return success;
}

void Display::close(){
    //Destroy window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void Display::initializeTiles(){

    tiles[0].setDimension(0, 0, screenWidth/8, screenHeight/8);
    tiles[0].setColor(0xFF, 0x00, 0x00, 0xFF);
}

void Display::generateTile(int n){
    int random = rand()%n;
}


void Display::draw(){

    //Clear screen
    SDL_SetRenderDrawColor(renderer, 0x00, 0xBB, 0xAC, 0x08);
    SDL_RenderClear(renderer);

    tiles[0].render(renderer);
    tiles[0].moveDown();

    if(tiles[0].posY + tiles[0].height > screenHeight){
        int random = rand()%8;

        tiles[0].setDimension(screenWidth/8 * random, 0, screenWidth/8, screenHeight/8);
    }
    //Update screen
    SDL_RenderPresent(renderer);
}


void Display::handleEvents(SDL_Event& e){

    //If a key was pressed
	if(e.type == SDL_KEYDOWN)
    {
        //defines the functions for keys
        switch(e.key.keysym.sym)
        {
            case SDLK_UP: tiles[0].moveUp(); break;
            case SDLK_DOWN: tiles[0].moveDown(); break;
            case SDLK_LEFT: tiles[0].moveLeft(); break;
            case SDLK_RIGHT: tiles[0].moveRight(); break;
        }
    }

    if(e.type == SDL_MOUSEBUTTONDOWN){

        //get the position of mouse.
        int x, y;
        SDL_GetMouseState(&x, &y);
        if(x > tiles[0].posX && x<tiles[0].posX+tiles[0].width && y > tiles[0].posY && y < tiles[0].posY + tiles[0].height){
            tiles[0].rgbColor.red = 0x00;
            tiles[0].rgbColor.green = 0xBB;
            tiles[0].rgbColor.blue = 0xAC;
            tiles[0].rgbColor.alpha = 0x08;
        }
    }
}
