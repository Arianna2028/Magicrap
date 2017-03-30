#ifndef SPRITE_TYPE_H_
#define SPRITE_TYPE_H_

namespace ping {

/**
 * Types of sprites for the platformer game
 */
enum class SpriteType
{
  /** The player; controlled by the user */ PLAYER,
  /** An enemy; controlled by game logic */ ENEMY,
  /** A collectible; player can collect for points */ COLLECTIBLE
};

}

#endif
