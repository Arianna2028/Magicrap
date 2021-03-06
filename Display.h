#ifndef PING_DISPLAY_H
#define PING_DISPLAY_H

#include <vector>
#include <SDL2/SDL_ttf.h>
#include "Sprite.h"

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;

namespace project {

/**
 * SDL Display.  The purpose of this class is to
 * encapsulate all uses of SDL2 by this program.
 * Note that SDL.h was not included so that other
 * classes will not have direct access to SDL2.
 * All uses of SDL2 must be made through this
 * class.
 *
 * @author Ken Baclawski
 */
class Display {
public:
  /**
   * Create a graphical display with specified size.
   * @throw domain_error if the display could not
   * be created and initialized.
   */
  Display(/** Display width. */ int width = 640,
	        /** Display height. */ int height = 480);

  /**
   * Destruct the graphical display.  This closes
   * the display.
   */
  ~Display();

  /**
   * Close the graphical display and release the
   * resources.
   */
  void close() noexcept;

  /**
   * Add an image to the collection.
   */
  void addImage(/** The location of the file. */
		const std::string& fileLocation) noexcept;

  /**
   * Get the number of images.
   */
  unsigned int getImageCount() const noexcept;

  /**
   * Refresh the display.
   * @throw domain_error if the display could not
   * be refreshed.
   */
  void refresh(std::vector<Sprite> sprites, std::string text);

private:
  /** The display window. */
  SDL_Window* window_ = nullptr;

  /** The display rendering tool. */
  SDL_Renderer* renderer_ = nullptr;

  /** First font to disply text */
  TTF_Font* font1_ = nullptr;

  /** First font to disply text */
  TTF_Font* font2_ = nullptr;

  /** The collection of images. */
  std::vector<SDL_Texture*> images_;

  /** The width of the window. */
  const int width_ = 0;

  /** The height of the window. */
  const int height_ = 0;

  /**
   * Clear the background to opaque white.
   */
  void clearBackground();
};

}

#endif
