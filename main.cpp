#include <iostream>
#include "display.h"

int main(int argc, char* args[])
{
    Display display;
    if(!display.init()){
        std::cout<<"failed to inititalize";
    }

    else{
        //Load media
		if( !display.loadMedia())
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
				}

				//Clear screen
				SDL_SetRenderDrawColor(display.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(display.renderer);

				//Render red filled quad
				SDL_Rect fillRect = { display.screenWidth/4, display.screenHeight/4, display.screenWidth/2, display.screenHeight/2 };
				SDL_SetRenderDrawColor( display.renderer, 0xFF, 0x00, 0x00, 0xFF );
				SDL_RenderFillRect( display.renderer, &fillRect );

				//Render green outlined quad
				SDL_Rect outlineRect = { display.screenWidth / 6, display.screenHeight/6, display.screenWidth*2/3, display.screenHeight*2/3 };
				SDL_SetRenderDrawColor( display.renderer, 0x00, 0xFF, 0x00, 0xFF );
				SDL_RenderDrawRect( display.renderer, &outlineRect);

				//Draw blue horizontal line
				SDL_SetRenderDrawColor( display.renderer, 0x00, 0x00, 0xFF, 0xFF );
				SDL_RenderDrawLine( display.renderer, 0, display.screenHeight/2, display.screenWidth, display.screenHeight/2);

				//Draw vertical line of yellow dots
				SDL_SetRenderDrawColor( display.renderer, 0xFF, 0xFF, 0x00, 0xFF );
				for( int i = 0; i < display.screenHeight; i += 4 )
				{
					SDL_RenderDrawPoint( display.renderer, display.screenWidth / 2, i );
				}

				//Update screen
				SDL_RenderPresent(display.renderer);
			}
		}
	}

	//Free resources and close SDL
	display.close();

	return 0;
}
