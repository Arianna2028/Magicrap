#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdexcept>
#include <iostream>
#include <vector>

#include "Sprite.h"
#include "Display.h"

using namespace std;
using namespace project;

Display::Display(int width, int height) : width_(width), height_(height)
{
  cout << "Constructing display." << endl;

  // Initialize SDL2
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    throw domain_error(string("SDL Initialization failed due to: ") + SDL_GetError());
  }

  // Construct the screen window
  window_ = SDL_CreateWindow("Display", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
  width_, height_, SDL_WINDOW_SHOWN);

  if (!window_) {
    close();
    throw domain_error(string("Unable to create the window due to: ") + SDL_GetError());
  }

  // Construct the renderer
  renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (!renderer_) {
    close();
    throw domain_error(string("Unable to create the renderer due to: ") + SDL_GetError());
  }

  if (TTF_Init() == -1) {
    throw domain_error(string("TTF Initialization failed due to: ") + SDL_GetError());
  }

  font1_ = TTF_OpenFont("graphics/rubber-biscuit.bold.ttf", 32);
  font2_ = TTF_OpenFont("graphics/myriad_pro.ttf", 32);

  if (!font1_) {
    close();
    throw domain_error(string("Unable to create font1 due to: ") + SDL_GetError());
  }else if (!font2_) {
    close();
    throw domain_error(string("Unable to create font1 due to: ") + SDL_GetError());
  }

  // Clear the window
  clearBackground();
}

Display::~Display()
{
  close();
}

void Display::close() noexcept
{
  cout << "Closing display." << endl;

  // Delete the SDL2 resources in reverse order of their construction, starting with the images
  for (SDL_Texture* image : images_) {
    if (image) {
      SDL_DestroyTexture(image);
    }
  }

  // Clear the collection of images to ensure idempotence
  images_.clear();

  // Destroy the renderer and window, and set the variables to nullptr to ensure idempotence
  if (renderer_) {
    SDL_DestroyRenderer(renderer_);
    renderer_ = nullptr;
  }

  if (window_) {
    SDL_DestroyWindow(window_);
    window_ = nullptr;
  }

  if (font1_ || font2_) {
    TTF_CloseFont(font1_);
    TTF_CloseFont(font2_);
    TTF_Quit();
  }

  // The last step is to quit SDL
  SDL_Quit();
}

void Display::addImage(const string& fileLocation) noexcept
{
  if (renderer_) {
    // Load the image from the file
    // SDL_Surface* imageSurface = SDL_LoadBMP(fileLocation.c_str());
    SDL_Surface* imageSurface = IMG_Load(fileLocation.c_str());
    if (imageSurface) {

      // Convert the image to a texture
      SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer_, imageSurface);
      if (imageTexture) {
        // Add the image to the collection
        images_.push_back(imageTexture);
      } else {
        cerr << "1 - Unable to load the image file at " << fileLocation
        << " due to: " << SDL_GetError() << endl;
      }

      // The surface is not longer needed
      SDL_FreeSurface(imageSurface);
    } else {
      cerr << "2 - Unable to load the image file at " << fileLocation
      << " due to: " << SDL_GetError() << endl;
    }
  }
}

unsigned int Display::getImageCount() const noexcept
{
  return images_.size();
}

void Display::refresh(vector<Sprite> sprites, string score)
{
  if (renderer_) {
    // clear the window
    clearBackground();

    // Draw all sprites
    for (Sprite sprite : sprites)
    {
      // The location of the sprite is a square
      SDL_Rect destination;
      destination.x = sprite.getXCoordinate();
      destination.y = sprite.getYCoordinate();
      destination.w = sprite.getWidth();
      destination.h = sprite.getHeight();

      // Get the image index and check that it is valid
      unsigned int imageIndex = sprite.getImageIndex();

      if (imageIndex >= 0 && imageIndex < images_.size()) {
        // Get the image for the sprite
        SDL_Texture* imageTexture = images_.at(imageIndex);

        if (imageTexture) {
          // Render the image at the location
          int rv;

          if (!sprite.getDirection()) {
            rv = SDL_RenderCopyEx(renderer_, imageTexture, nullptr, &destination, 0, nullptr, SDL_FLIP_HORIZONTAL);
          } else {
            rv = SDL_RenderCopyEx(renderer_, imageTexture, nullptr, &destination, 0, nullptr, SDL_FLIP_NONE);
          }

          if  (rv != 0) {
            close();
            throw domain_error(string("Unable to render a sprite due to: ") + SDL_GetError());
          }
        } else {
          close();
          throw domain_error("Missing image texture at index " + to_string(imageIndex));
        }
      } else {
        close();
        throw domain_error("Invalid image index " + to_string(imageIndex));
      }
    }

    // render score in top left of screen
    if (font1_ && font2_) {
      SDL_Color white = {255, 255, 255};
      // construct strings
      string labelpp = "Your Score ";
      string separatorpp = ":";
      // construct c-style strings
      auto label = labelpp.c_str();
      auto separator = separatorpp.c_str();
      auto scoreCString = score.c_str();
      // create Surfaces from text
      SDL_Surface* labelSurface = TTF_RenderText_Solid(font1_, label, white);
      SDL_Surface* separatorSurface = TTF_RenderText_Solid(font2_, separator, white);
      SDL_Surface* scoreSurface = TTF_RenderText_Solid(font1_, scoreCString, white);
      // create actual texture from surface
      SDL_Texture* labelTexture = SDL_CreateTextureFromSurface(renderer_, labelSurface);
      SDL_Texture* separatorTexture = SDL_CreateTextureFromSurface(renderer_, separatorSurface);
      SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer_, scoreSurface);
      // create rectangles in top left to hold text
      SDL_Rect labelRect = {0, 0, 250, 32};
      SDL_Rect separatorRect = {250, 0, 8, 32};
      SDL_Rect scoreRect = {258, 0, 30, 32};
      // add textures to renderer
      SDL_RenderCopy(renderer_, labelTexture, nullptr, &labelRect);
      SDL_RenderCopy(renderer_, separatorTexture, nullptr, &separatorRect);
      SDL_RenderCopy(renderer_, scoreTexture, nullptr, &scoreRect);
      //SDL_QueryTexture(solidTexture, NULL, NULL, &textRect.w, &textRect.h);
    }

    SDL_RenderPresent(renderer_);
  }
}

void Display::clearBackground()
{
  if (renderer_) {
    // Clear the window to opaque white
    if (SDL_SetRenderDrawColor(renderer_, 0xff, 0xff, 0xff, 0xff) != 0) {
      close();
      throw domain_error(string("Unable to set the background color due to: ")
      + SDL_GetError());
    }

    if (SDL_RenderClear(renderer_) != 0) {
      close();
      throw domain_error(string("Unable to set the background color due to: ")
      + SDL_GetError());
    }
  }
}
