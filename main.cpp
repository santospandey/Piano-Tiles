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

            // at first initialize tiles.
            display.initializeTiles();

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

					//Handle input for the dot
					display.handleEvents(e);
				}

                // call to draw the stuff.
                display.draw();
			}
		}
	}

	//Free resources and close SDL
	display.close();

	return 0;
}
