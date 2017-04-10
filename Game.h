#ifndef PROJECT_GAME_H
#define PROJECT_GAME_H

#include <vector>
#include "Sprite.h"

namespace project
{

/**
 * Represents the state of the game
 */
class Game
{
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

  /**
   * Move the player sprite left based on velocity.
   * Player cannot move if game is paused.
   */
  void movePlayerLeft() noexcept;

  /**
   * Move the player sprite right based on velocity
   * Player cannot move if game is paused.
   */
  void movePlayerRight() noexcept;

  /**
   * Move the player up if at a ladder.
   * Player cannot move if game is paused.
   */
  void movePlayerUp() noexcept;

  /**
   * Move the player down if at a ladder.
   * Playre cannot move if game is paused.
   */
  void movePlayerDown() noexcept;

  /**
   * Pauses the game if not paused, or unpauses if paused
   */
  void pauseUnpause();

  /**
   * Evolves the state of the game by one tick
   */
  void evolve() noexcept;

  /**
   * Stops player movement
   */
   void stopPlayer() noexcept;

private:
  Sprite player_;  // Player game object
  Sprite background_;  // Background object
  Sprite pausedSprite_ = Sprite(330, 84, 400, 300, 4);  // Paused label
  Sprite winnerSprite_ = Sprite(363, 84, 400, 300, 5);  // winner text
  Sprite exit_ = Sprite(44, 82, 150, 175, 7);  // exit
  Sprite loserSprite_ = Sprite(412, 80, 400, 300, 6);  // loser text
  std::vector<Sprite> enemies_;  // Enemy game objects
  std::vector<Sprite> ladders_;  // Ladders in the game world
  std::vector<Sprite> collectibles_;  // Collectible game objects
  std::vector<Sprite> platforms_;  // The floor objects
  const int width_;  // width of the game in pixels
  const int height_;  // height of the game in pixels
  bool paused_ = false;  // is the game in paused state? defaults to false
  bool blockPlayerMove_ = false;  // is the player blocked from moving?
  bool gameOver_ = false;  // is the game in progress?
  bool wonGame_ = false;  // true = winner, false = loser
  int playerStopVertical_ = 0;

  /**
   * Add a platform to the game at the given height
   */
  void addPlatform(/** Height in pixels */ int height,
                    /** Width in floor tiles */ int width,
                    /** How far in to start in floor tiles */ int startIdx);

  /**
   * Calculate if the player is currently in front of a ladder
   * @return true if the player sprite collides with a ladder
   */
  bool playerAtLadder() const noexcept;
};

}

#endif
