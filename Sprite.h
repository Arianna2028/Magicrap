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
         /** Type of sprite this is */ SpriteType type,
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
   * Move the sprite to a new horizontal position as determined by the the
   * specified period of time and a direction
   */
  void moveHorizontal(/** The interval of time during which the sprite moves. */ double delta) noexcept;

  /**
   * Determine whether two sprites are hitting each other.
   * @return Whether the two sprites are too close.
   */
  bool hits(/** The other sprite that may be hitting this one. */
	    const Sprite& other) const noexcept;

  /**
   * Returns the direction the sprite is facing.
   * @returns true if the sprite is facing left
   */
  bool getDirection() const noexcept;

  /**
   * Flips the direction the sprite is facing
   */
  void flip() noexcept;

private:
  const int width_;  // width in pixels
  const int height_;  // height in pixels

  double cx_;  // x-coordinate of the center of the sprite
  double cy_;  // y-coordinate of the center of the sprite

  double hv_ = -50;  // horizontal velocity; > 0 facing right; pixels/sec

  const unsigned int imageIndex_;  // index in the list of images to use
  SpriteType type_; // The type of sprite this is; defines how it will interact with other sprites

  /**
   *  TODO: Fields we might want:
   *  - bool moving
   *  - direction
   */
};

}

#endif
