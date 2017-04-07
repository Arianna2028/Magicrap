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
const int playerSpeed = 3;

Game::Game(int width, int height) : width_(width), height_(height),
  player_(SpriteType::PLAYER, 69, 60, width / 2.0, height - 35, 0),
  background_(SpriteType::BACKGROUND, width, height, width / 2, height / 2, 3)
{
  cout << "Constructing game." << endl;

  // Build platforms
  addPlatform(height - (platformHeight / 2), int((width / platformWidth) + 1), 1);
  addPlatform(height - ladderHeight + platformHeight, 5, 3);

  // Build ladders
  Sprite ladder1(SpriteType::LADDER, ladderWidth, ladderHeight,
    250, height - (ladderHeight / 2) - platformHeight, 1);
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
      player_.setHorizontalVelocity(-playerSpeed);
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
    player_.setHorizontalVelocity(playerSpeed);
  }
}

void Game::movePlayerUp() noexcept
{
  if (playerAtLadder()) {
    player_.setVerticalVelocity(playerSpeed);
  }
}

void Game::movePlayerDown() noexcept
{
  if (playerAtLadder()) {
    player_.setVerticalVelocity(-playerSpeed);
  }
}

void Game::addPlatform(int height, int width, int startIdx)
{
  for (int ii = startIdx; ii < startIdx + width; ii++)
  {
    platforms_.push_back(Sprite(SpriteType::PLATFORM, platformWidth,
      platformHeight, (ii * platformWidth) - (platformWidth / 2),
      height, 2));
  }
}

void Game::pauseUnpause()
{
  paused_ = !paused_;
}

bool Game::playerAtLadder() const noexcept
{
  for (Sprite l : ladders_)
  {
    if (player_.hits(l)) {
      return true;
    }
  }

  return false;
}

bool Game::playerOnFloor() const noexcept
{
  for (Sprite p : platforms_)
  {
    if ((player_.getYCoordinate() + (player_.getHeight() / 2)) == p.getYCoordinate()) {
      return true;
    }
  }
}

void Game::evolve() noexcept
{
  // Check that player doesn't continue moving vertically past a ladder
  if (playerOnFloor()) {
    player_.setVerticalVelocity(0);
  }

  if (!paused_) {
    player_.evolve();

    //TODO evolve everything else too
  }
}

void Game::stopPlayer() noexcept
{
  player_.setVerticalVelocity(0);
  player_.setHorizontalVelocity(0);
}
