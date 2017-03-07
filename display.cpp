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
				SDL_SetRenderDrawColor( renderer, 0x23, 0x98, 0xAB, 0xBC);

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
    t1.setColor(0xFF, 0x00, 0x00, 0xFF);
    t1.setDimension(0, 0, screenWidth/4, screenHeight/4);
}


void Display::draw(){

    //Clear screen
    SDL_SetRenderDrawColor(renderer, 0x00, 0xBB, 0xAC, 0x08);
    SDL_RenderClear(renderer);

    t1.render(renderer);

    //Update screen
    SDL_RenderPresent(renderer);
}


void Display::handleEvents(SDL_Event& e){

    //If a key was pressed
	if( e.type == SDL_KEYDOWN)
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: t1.moveUp(); break;
            case SDLK_DOWN: t1.moveDown(); break;
            case SDLK_LEFT: t1.moveLeft(); break;
            case SDLK_RIGHT: t1.moveRight(); break;
        }
    }
}
