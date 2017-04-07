#include <iostream>
#include <stdexcept>
#include <SDL2/SDL.h>

#include "Display.h"
#include "Game.h"

using namespace std;
using namespace project;

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
    display.addImage("graphics/koffing.png");  // idx 0
    display.addImage("graphics/ladder.png");  // idx 1
    display.addImage("graphics/floor.png");  // idx 2
    display.addImage("graphics/background.png");  // idx 3

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
				} else if (e.type == SDL_KEYDOWN) {
          switch (e.key.keysym.sym)
        	{
        		case SDLK_UP:
              game.movePlayerUp();
        			break;
        		case SDLK_DOWN:
              game.movePlayerDown();
        			break;
        		case SDLK_LEFT:
              game.movePlayerLeft();
        			break;
        		case SDLK_RIGHT:
              game.movePlayerRight();
        			break;
            case SDLK_q:
              quit = true;
              break;
            case SDLK_p:
              game.pauseUnpause();
              cout << "PAUSE TOGGLED" << endl;
              break;
        		default:
        			break;
        	}
				} else if (e.type == SDL_KEYUP) {
          if (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_DOWN ||
              e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_RIGHT) {
            game.stopPlayer();
          }
        }
			}

      game.evolve();
      display.refresh(game.getSprites());
		}

    display.close();
  } catch (const exception& e) {
    cerr << e.what() << endl;
    return 1;
  }
}
