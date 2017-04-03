#include <iostream>
#include <stdexcept>
#include <SDL2/SDL.h>

#include "Display.h"
#include "Game.h"

using namespace std;
using namespace project;

void handleKeyIn(SDL_Event e);

/**
 * Main program for the bouncing image display.
 * @return The status code. Status code 0 means
 * the program succeeds, and nonzero status code
 * means the program failed.
 */
int main()
{
  try
  {
    // Initialize the graphical display
    int width = 800;
    int height = 600;
    Game game(width, height);
    Display display(width, height);

    // Add some images to the display
    display.addImage("graphics/koffing.bmp");

    // Construct the sprite collection
    // Sprites sprites(display);

    // Initialize for event loop
		bool quit = false;
		SDL_Event e;

    // Run until quit.
		while (!quit)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT) {
					quit = true;
					display.close();
				} else if (e.type == SDL_KEYDOWN) {
          switch (e.key.keysym.sym)
        	{
        		case SDLK_UP:
        			cout << "UP BUTTON PRESSED" << endl;
        			break;
        		case SDLK_DOWN:
        			cout << "DOWN BUTTON PRESSED" << endl;
        			break;
        		case SDLK_LEFT:
        			cout << "LEFT BUTTON PRESSED" << endl;
              game.movePlayerLeft();
        			break;
        		case SDLK_RIGHT:
        			cout << "RIGHT BUTTON PRESSED" << endl;
              game.movePlayerRight();
        			break;
        		default:
        			break;
        	}
				}

			}

      display.refresh(game.getSprites());
		}

  } catch (const exception& e) {
    cerr << e.what() << endl;
    return 1;
  }
}
