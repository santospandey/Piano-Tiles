#include "display.h"

bool Display::init(){

	//Initialization flag
	bool success = true;

    if(TTF_Init() < 0){
        std::cout<<"error in ttf initializing";
    }


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
	TTF_Quit();
}

void Display::initializeTiles(){

    for(int i=0; i<9; i++){
        tiles[i].setDimension(i*screenWidth/8, i*screenHeight/8-screenHeight/8, screenWidth/8, screenHeight/8);
        if(i%2){
            tiles[i].setColor(0x00, 0x00, 0x00, 0x88);
        }
        else{
            tiles[i].setColor(0x00, 0x00, 0xFF, 0x88);
        }
    }
}

void Display::textInput(){
    // for text
    TTF_Font* Sans = TTF_OpenFont("OpenSans-Regular.ttf", 24); //this opens a font style and sets a size

    SDL_Color White = {255, 255, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "aaabbbccedd", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture

    SDL_Rect Message_rect; //create a rect
    Message_rect.x = 0;  //controls the rect's x coordinate
    Message_rect.y = 0; // controls the rect's y coordinte
    Message_rect.w = 100; // controls the width of the rect
    Message_rect.h = 100; // controls the height of the rect
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
}


void Display::draw(){

    //Clear screen
    SDL_SetRenderDrawColor(renderer, 0x00, 0xBB, 0xAC, 0x08);
    SDL_RenderClear(renderer);

    Message_rect.x = screenWidth/2;  //controls the rect's x coordinate
    Message_rect.y = 0; // controls the rect's y coordinte
    Message_rect.w = 50; // controls the width of the rect
    Message_rect.h = 50; // controls the height of the rect

    TTF_Font* Sans = TTF_OpenFont("OpenSans-Regular.ttf", 30); //this opens a font style and sets a size

    std::stringstream ss;
    ss << score;
    std::string num = ss.str();

    // render text
    surfaceMessage = TTF_RenderText_Solid(Sans, &num[0], White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
    Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);


    for(int i=0; i<9; i++){
        tiles[i].render(renderer);
        tiles[i].moveDown();

        if(tiles[i].posY + tiles[i].height > screenHeight){

            int random = rand()%8;
            tiles[i].setDimension(screenWidth/8 * random, -1*screenHeight/8, screenWidth/8, screenHeight/8);
            if(i%2){
                tiles[i].setColor(0x00, 0x00, 0x00, 0x88);
            }
            else{
                tiles[i].setColor(0x00, 0x00, 0xFF, 0x88);
            }
        }
    }

    //Update screen
    SDL_RenderPresent(renderer);

    TTF_CloseFont(Sans);
    SDL_DestroyTexture(Message);
    SDL_FreeSurface(surfaceMessage);
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
        for(int i=0; i<9; i++){
            if(x > tiles[i].posX && x<tiles[i].posX+tiles[i].width && y > tiles[i].posY && y < tiles[i].posY + tiles[i].height){

                ++score;
                std::cout<<"\n"<<score;
                tiles[i].rgbColor.red = 0x00;
                tiles[i].rgbColor.green = 0xBB;
                tiles[i].rgbColor.blue = 0xAC;
                tiles[i].rgbColor.alpha = 0x08;
            }
        }
    }
}
