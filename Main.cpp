#include <ctime>
#include <iostream>
#include <stdexcept>
#include <SDL2/SDL.h>

#include "Sprites.h"
#include "Display.h"

using namespace std;
using namespace project;

void handleKeyIn(SDL_Event e);

/**
 * Main program for the bouncing image display.
 * @return The status code. Status code 0 means
 * the program succeeds, and nonzero status code
 * means the program failed.
 */
int main() {
  try {

    // Initialize the graphical display
    Display display;

    // Add some images to the display
    display.addImage("graphics/image1.bmp");

    // Construct the sprite collection

    Sprites sprites(display.getImageCount());

    // Run until quit.
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
					handleKeyIn(e);
				}

			}

			sprites.evolve();
      display.refresh(sprites);
		}

  } catch (const exception& e) {
    cerr << e.what() << endl;
    return 1;
  }
}

void handleKeyIn(SDL_Event e)
{
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
			break;
		case SDLK_RIGHT:
			cout << "RIGHT BUTTON PRESSED" << endl;
			break;
		default:
			break;
	}
}
