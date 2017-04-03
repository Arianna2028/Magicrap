#include <vector>
#include <iostream>
#include "Game.h"
#include "SpriteType.h"
#include "Sprite.h"

using namespace std;
using namespace project;

Game::Game(int width, int height) : width_(width), height_(height),
  player_(SpriteType::PLAYER, 64, 64, width / 2.0, height - 32, 0)
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
