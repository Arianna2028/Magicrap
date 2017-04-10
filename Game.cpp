#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <cstdlib>

#include "Game.h"
#include "Sprite.h"

using namespace std;
using namespace project;

const int platformWidth = 80;
const int platformHeight = 10;
const int ladderWidth = 50;
const int ladderHeight = 80;
const int playerSpeed = 3;

Game::Game(int width, int height) : width_(width), height_(height),
  player_(69, 60, width / 2.0, height - 35, 0),
  background_(width, height, width / 2, height / 2, 3)
{
  cout << "Constructing game." << endl;

  // Build platforms & collectibles
  int platformsAcross = (width / platformWidth) + 1;
  int platformStartHeight = height - (platformHeight / 2);
  int platformInterval = 63;

  for (int ii = 0; ii <= 6; ii++)
  {
    addPlatform(platformStartHeight - (ii * platformInterval), platformsAcross, 1);
  }

  addCollectibles();

  // Build ladders
  int ladderStartHeight = height - platformHeight - (ladderHeight / 2);
  Sprite ladder1(ladderWidth, ladderHeight, 250, ladderStartHeight, 1);
  Sprite ladder2(ladderWidth, ladderHeight, 700, ladderStartHeight - platformInterval, 1);
  Sprite ladder3(ladderWidth, ladderHeight, 150, ladderStartHeight - platformInterval, 1);
  Sprite ladder4(ladderWidth, ladderHeight, 550, ladderStartHeight - (2 * platformInterval), 1);
  Sprite ladder5(ladderWidth, ladderHeight, 400, ladderStartHeight - (3 * platformInterval), 1);
  Sprite ladder6(ladderWidth, ladderHeight, 200, ladderStartHeight - (4 * platformInterval), 1);
  Sprite ladder7(ladderWidth, ladderHeight, 500, ladderStartHeight - (4 * platformInterval), 1);
  Sprite ladder8(ladderWidth, ladderHeight, 650, ladderStartHeight - (5 * platformInterval), 1);
  ladders_.push_back(ladder1);
  ladders_.push_back(ladder2);
  ladders_.push_back(ladder3);
  ladders_.push_back(ladder4);
  ladders_.push_back(ladder5);
  ladders_.push_back(ladder6);
  ladders_.push_back(ladder7);
  ladders_.push_back(ladder8);

  // spawn enemies
  spawnEnemies();
}

Game::~Game() {}

vector<Sprite> Game::getSprites() const noexcept
{
  vector<Sprite> allSprites;

  allSprites.push_back(background_);

  for (Sprite s : platforms_)
  {
    allSprites.push_back(s);
  }

  for (Sprite s : ladders_)
  {
    allSprites.push_back(s);
  }

  for (Sprite s : collectibles_)
  {
    allSprites.push_back(s);
  }

  for (Sprite s : enemies_)
  {
    allSprites.push_back(s);
  }

  allSprites.push_back(exit_);
  allSprites.push_back(player_);

  if (paused_) {
    allSprites.push_back(pausedSprite_);
  }

  if (gameOver_ && wonGame_) {
    allSprites.push_back(winnerSprite_);
  } else if (gameOver_ && !wonGame_) {
    allSprites.push_back(loserSprite_);
  }

  return allSprites;
}

void Game::movePlayerLeft() noexcept
{
    // Make sure the player is facing left
    if (!player_.getDirection()) {
      player_.flip();
    }

    // Make sure player isn't at left edge of screen
    if ((player_.getXCoordinate() >= 0) && !blockPlayerMove_) {
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
  if ((player_.getXCoordinate() <= (width_ - player_.getWidth())) && !blockPlayerMove_) {
    player_.setHorizontalVelocity(playerSpeed);
  }
}

void Game::movePlayerUp() noexcept
{
  if (playerAtLadder() && !blockPlayerMove_) {
    player_.setVerticalVelocity(playerSpeed);
    player_.setYCoordinate(player_.getYCoordinate() + (player_.getHeight() / 2) - 1);
    blockPlayerMove_ = true;
    playerStopVertical_ = player_.getYCoordinate() - 63;
  }
}

void Game::movePlayerDown() noexcept
{
  if (playerAtLadder() && !blockPlayerMove_) {
    player_.setVerticalVelocity(-playerSpeed);
    player_.setYCoordinate(player_.getYCoordinate() + (player_.getHeight() / 2) + 1);
    blockPlayerMove_ = true;
    playerStopVertical_ = player_.getYCoordinate() + 63;
  }
}

void Game::addPlatform(int height, int width, int startIdx)
{
  for (int ii = startIdx; ii < startIdx + width; ii++)
  {
    platforms_.push_back(Sprite(platformWidth,
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

void Game::evolve() noexcept
{
  // Stop vertical movement if not at a ladder
  if (!playerAtLadder()) {
    player_.setVerticalVelocity(0);
    blockPlayerMove_ = false;
  }

  // Move player to top/bottom of ladder
  if (player_.getYCoordinate() == playerStopVertical_ && player_.getVerticalVelocity() > 0) {
    player_.setVerticalVelocity(0);
    blockPlayerMove_ = false;
    player_.setYCoordinate(player_.getYCoordinate() + (player_.getHeight() / 2) + 3);
  } else if (player_.getYCoordinate() == playerStopVertical_ && player_.getVerticalVelocity() < 0) {
    player_.setVerticalVelocity(0);
    blockPlayerMove_ = false;
    player_.setYCoordinate(player_.getYCoordinate() + (player_.getHeight() / 2) - 3);
  }

  // Evolve all enemies
  for (Sprite& enemy : enemies_) {
    // if enemy is too close to side of screen, switch directions
    if (enemy.getXCoordinate() + enemy.getWidth() >=  width_ ||
        enemy.getXCoordinate() <= 0) {
      enemy.switchDir();
    }
    enemy.evolve();
  }


  // Evolve the game
  if (!paused_ && !gameOver_) {
    // Move player
    player_.evolve();

    // Check for win
    if (player_.hits(exit_)) {
      gameOver_ = true;
      wonGame_ = true;
      text_ = "Your score - " + to_string(playerScore_);
      cout << "Player won game." << endl;
      cout << "Score: " << to_string(playerScore_) << endl;
    }

    // Check for lose
    for (Sprite e : enemies_)
    {
      if (player_.hits(e)) {
        gameOver_ = true;
        wonGame_ = false;
        text_ = "Your score - " + to_string(playerScore_);
        cout << "Player lost game." << endl;
        cout << "Score: " << to_string(playerScore_) << endl;
      }
    }

    // Check for collectibles
    for (Sprite& c : collectibles_)
    {
      if (player_.hits(c)) {
        playerScore_++;
        cout << "Score++" << endl;
        text_ = "Your score - " + to_string(playerScore_);
        c.setXCoordinate(-100);
      }
    }
  }
}

void Game::stopPlayer() noexcept
{
  player_.setVerticalVelocity(0);
  player_.setHorizontalVelocity(0);
}

void Game::reset() noexcept
{
  player_.setYCoordinate(height_ - 35);
  player_.setXCoordinate(width_ / 2.0);
  stopPlayer();
  gameOver_ = false;
  wonGame_ = false;
  addCollectibles();
  spawnEnemies();
  paused_ = false;
  blockPlayerMove_ = false;
  playerScore_ = 0;
  text_ = "";
}

void Game::addCollectibles() noexcept
{
  collectibles_.clear();
  int platformStartHeight = height_ - (platformHeight / 2);
  int platformInterval = 63;


  for (int ii = 1; ii < 6; ii++)
  {
    collectibles_.push_back(Sprite(16, 16, 100, platformStartHeight - (ii * platformInterval) - 32, 8));
  }
}

const string Game::getScore() const noexcept
{
  return " " + to_string(playerScore_);
}

void Game::spawnEnemies() noexcept {
  enemies_.clear();

  int platformStartHeight = this->height_ - (platformHeight / 2);
  int platformInterval = 63;
  srand(time(NULL));

  // spawn one enemy per level except the first one
  for (int ii = 2; ii <= 6; ++ii) {
    int enemyY = platformStartHeight - (ii * platformInterval);
    int enemyX = rand() % this->width_;
    // make sure enemy is not too close to edge
    while (enemyX < 40 || enemyX > width_ - 40) {
      enemyX = rand() % this->width_;
    }
    // creates enemy, with random direction
    Sprite enemy(60, 60, enemyX, enemyY + 30, 9);
    int hv = -2;
    enemy.setHorizontalVelocity(hv);
    if (rand() % 2 == 0) {
      enemy.switchDir();
    }
    // adds enemy to game's list of enemies
    this->enemies_.push_back(enemy);
  }
}
