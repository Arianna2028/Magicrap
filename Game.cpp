#include <vector>
#include <iostream>
#include "Game.h"
#include "SpriteType.h"
#include "Sprite.h"

using namespace std;
using namespace project;

Game::Game(int width, int height) : width_(width), height_(height),
  player_(SpriteType::PLAYER, 53, 48, width / 2.0, height - 32, 0)
{
  cout << "Constructing game." << endl;
}

Game::~Game() {}

vector<Sprite> Game::getSprites() const noexcept
{
  // TODO: include enemies and collectibles
  vector<Sprite> allSprites;
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
