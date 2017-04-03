#ifndef PROJECT_GAME_H
#define PROJECT_GAME_H

#include <vector>
#include "Sprite.h"

namespace project {

/**
 * A sprite with a width, height, position, and type
 */
class Game {
public:
  /**
   * Construct a game
   */
   Game(/** Width of the game in pixels */  int width,
        /** Height of the game in pixels */ int height);

   /**
    * Destruct a game
    */
    ~Game();

  /**
   * Get the list of all sprites in this game
   * @return the sprites in this game
   */
  std::vector<Sprite> getSprites() const noexcept;

private:
  Sprite player_;  // Player game object
  std::vector<Sprite> enemies_;  // Enemy game objects
  const int width_;  // width of the game in pixels
  const int height_;  // height of the game in pixels
};

}

#endif
