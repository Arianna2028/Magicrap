#ifndef PROJECT_SPRITE_H
#define PROJECT_SPRITE_H

#include <iostream>
#include "SpriteType.h"

namespace project {

/**
 * A sprite with a width, height, position, and type
 */
class Sprite {
public:
  /**
   * Construct a sprite.
   * @throw domain_error if the arguments are invalid
   */
  Sprite(
         /** Width of the sprite in pixels */ int width,
         /** Height of the sprite in pixels */ int height,
         /** Starting X position of the sprite */ double startX,
         /** Starting Y position of the sprite */ double startY,
         /** Image to use to display this sprite */ int idx);

  /**
   * The x-coordinate of the sprite. (Leftmost pos)
   * @return The x-coordinate of the sprite.
   */
  int getXCoordinate() const noexcept;

  /**
   * The y-coordinate of the sprite. (Topmost pos)
   * @return The y-coordinate of the sprite.
   */
  int getYCoordinate() const noexcept;

  /**
   * Get the width of the sprite
   * @return the width of the sprite in pixels
   */
  int getWidth() const noexcept;

  /**
   * Get the height of the sprite
   * @return the height of the sprite in pixels
   */
  int getHeight() const noexcept;

  /**
   * Get the image index of the sprite.
   * @return The index of the image to use for the sprite.
   */
   int getImageIndex() const noexcept;

   /**
   * Sets the horizontal velocity of a sprite.
   */
   void setHorizontalVelocity(/** New horizontal velocity */ double hv) noexcept;

   /**
   * Sets the vertical velocity of a sprite.
   */
   void setVerticalVelocity(/** New vertical velocity */ double vv) noexcept;

  /**
   * Determine whether two sprites are hitting each other.
   * @return Whether the two sprites are too close.
   */
  bool hits(/** The other sprite that may be hitting this one. */
	    const Sprite& other) const noexcept;

  /**
   * Returns the direction the sprite is facing.
   * @return true if the sprite is facing left
   */
  bool getDirection() const noexcept;

  /**
   * Flips the direction the sprite is facing
   */
  void flip() noexcept;

  /**
   * Moves the sprite per tick
   */
   void evolve() noexcept;

   /**
    * Get the vertical velocity of the sprite
    * @return vertical velocity of sprite
    */
  double getVerticalVelocity() const noexcept;

  /**
   * Sets this sprite's y coordinate
   */
  void setYCoordinate(/** New y coord */ double yy) noexcept;

  /**
   * Switches direction of horizontal velocity.
   */
  void switchDir() const noexcept;

private:
  const int width_;  // width in pixels
  const int height_;  // height in pixels

  double cx_;  // x-coordinate of the center of the sprite
  double cy_;  // y-coordinate of the center of the sprite

  double hv_ = 0;  // horizontal velocity; > 0 moving right
  double vv_ = 0;  // vertical velocity; > 0 moving up

  bool direction_ = true;  // true if facing left

  const unsigned int imageIndex_;  // index in the list of images to use
};

}

#endif
