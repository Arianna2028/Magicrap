#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

#include "Game.h"
#include "SpriteType.h"
#include "Sprite.h"

using namespace std;
using namespace project;

Game::Game(int width, int height) : width_(width), height_(height),
  player_(SpriteType::PLAYER, 69, 60, width / 2.0, height - 32, 0)
{
  cout << "Constructing game." << endl;

  Sprite ladder1(SpriteType::LADDER, 48, 76, 250, height - 40, 1, 0);
  ladders_.push_back(ladder1);
}

Game::~Game() {}

vector<Sprite> Game::getSprites() const noexcept
{
  vector<Sprite> allSprites;
  // TODO: These should compile but won't
  // allSprites.insert(ladders_.begin(), ladders_.end());
  // allSprites.insert(enemies_.begin(), enemies_.end());
  // allSprites.insert(collectibles_.begin(), collectibles_.end());

  // TODO: Temporary solution
  for (Sprite s : ladders_)
  {
    allSprites.push_back(s);
  }

  for (Sprite s : enemies_)
  {
    allSprites.push_back(s);
  }

  for (Sprite s : collectibles_)
  {
    allSprites.push_back(s);
  }


  allSprites.push_back(player_);

  return allSprites;
}

void Game::movePlayerLeft() noexcept
{
  // Make sure the player is facing left
  if (!player_.getDirection()) {
    player_.flip();
  }

  // Make sure player isn't at left edge of screen
  if (!(player_.getXCoordinate() <= 0)) {
    player_.moveHorizontal(0.1);
  }
}

void Game::movePlayerRight() noexcept
{
  // Make sure the player is facing right
  if (player_.getDirection()) {
    player_.flip();
  }

  // Make sure player isn't at right edge of screen
  if (!(player_.getXCoordinate() >= (width_ - player_.getWidth()))) {
    player_.moveHorizontal(0.1);
  }
}
