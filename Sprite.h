#ifndef PING_SPRITE_H
#define PING_SPRITE_H

#include <random>
#include "SpriteType.h"

namespace ping {

/**
 * A sprite with a width, height, position, and type
 */
class Sprite {
public:
  /**
   * Construct a sprite.
   * @throw domain_error if the arguments are invalid
   */
  Sprite(/** Width of the sprite in pixels */ int width,
         /** Height of the sprite in pixels */ int height,
         /** Starting X position of the sprite */ int startX,
         /** Starting Y position of the sprite */ int startY,
         /** Type of sprite this is */ SpriteType type);

  /**
   * The x-coordinate of a square containing the sprite. (Leftmost pos)
   * @return The x-coordinate of the sprite.
   */
  int getXCoordinate() const noexcept;

  /**
   * The y-coordinate of a square containing the sprite. (Topmost pos)
   * @return The y-coordinate of the sprite.
   */
  int getYCoordinate() const noexcept;

  /**
   * Get the image index of the sprite.
   * @return The index of the image to use for the sprite.
   */
  int getImageIndex() const noexcept;

  /**
   * Move the sprite to a new position as
   * determined by the the specified period of
   * time.
   */
  void move(/** The interval of time during which
	    the sprite moves. */ double delta) noexcept;

  /**
   * Determine whether two sprites are hitting each other.
   * @return Whether the two sprites are too close.
   */
  bool hits(/** The other sprite that may be hitting this one. */
	    const Sprite& other) const noexcept;

private:
  /** The width of the sprite in pixels. */
  const int width_ = 640;
  /** The height of the sprite in pixels. */
  const int height_ = 480;

  /** Index of the image to use for the sprite. */
  const unsigned int imageIndex_ = 0;

  /** The current x-coordinate of the center of the sprite. */
  double cx_ = 0.0;
  /** The current y-coordinate of the center of the sprite. */
  double cy_ = 0.0;

  /** The type of sprite this is; defines how it will interact with other sprites */
  SpriteType type_;
};

}

#endif
