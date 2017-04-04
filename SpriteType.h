#ifndef SPRITE_TYPE_H_
#define SPRITE_TYPE_H_

namespace project {

/**
 * Types of sprites for the platformer game
 */
enum class SpriteType
{
  /** The player; controlled by the user */ PLAYER,
  /** An enemy; controlled by game logic */ ENEMY,
  /** A collectible; player can collect for points */ COLLECTIBLE,
  /** Ladders that the player can use for vertical movement */ LADDER,
  /** Platforms for the player to stand on */ PLATFORM,
  /** Background for the whole game */ BACKGROUND
};

}

#endif
