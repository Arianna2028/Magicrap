#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

#include "Game.h"
#include "SpriteType.h"
#include "Sprite.h"

using namespace std;
using namespace project;

const int platformWidth = 80;
const int platformHeight = 10;
const int ladderWidth = 50;
const int ladderHeight = 80;

Game::Game(int width, int height) : width_(width), height_(height),
  player_(SpriteType::PLAYER, 69, 60, width / 2.0, height - 35, 0),
  background_(SpriteType::BACKGROUND, width, height, width / 2, height / 2, 3)
{
  cout << "Constructing game." << endl;

  // Build platforms
  addPlatform(height - (platformHeight / 2), int((width / platformWidth) + 1), 1);


  // Build ladders
  Sprite ladder1(SpriteType::LADDER, ladderWidth, ladderHeight,
    250, height - (ladderHeight / 2) - platformHeight, 1, 0);
  ladders_.push_back(ladder1);
}

Game::~Game() {}

vector<Sprite> Game::getSprites() const noexcept
{
  vector<Sprite> allSprites;
  // TODO: These should compile but won't
  // allSprites.insert(platforms_.begin(), platforms_.end());
  // allSprites.insert(ladders_.begin(), ladders_.end());
  // allSprites.insert(enemies_.begin(), enemies_.end());
  // allSprites.insert(collectibles_.begin(), collectibles_.end());

  // TODO: Temporary solution
  allSprites.push_back(background_);

  for (Sprite s : platforms_)
  {
    allSprites.push_back(s);
  }

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

void Game::addPlatform(int height, int width, int startIdx)
{
  for (int ii = startIdx; ii < width ; ii++)
  {
    platforms_.push_back(Sprite(SpriteType::PLATFORM, platformWidth, platformHeight,
    (platformWidth * ii) - (platformWidth / 2), height, 2, 0));
  }
}
