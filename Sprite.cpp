#include <vector>
#include <random>
#include <stdexcept>

#include "Sprite.h"
#include "SpriteType.h"

using namespace std;
using namespace project;

Sprite::Sprite(int width, int height, int startX, int startY, SpriteType type)
	: width_(width), height_(height), cx_(startX), cy_(startY), type_(type) {}

int Sprite::getXCoordinate() const noexcept {
  return int(cx_ - (width / 2));
}

int Sprite::getYCoordinate() const noexcept {
  return int(cy_ - (height / 2));
}

int Sprite::getImageIndex() const noexcept {
  return imageIndex_;
}

void Sprite::move(double delta) noexcept {
	// TODO: make the sprite move. Might want to break this up into left/right/up
}

bool Sprite::hits(const Sprite& other) const noexcept {
	//TODO: make this work based not on radius
  double dx = other.cx_ - cx_;
  double dy = other.cy_ - cy_;
  double dist2 = dx * dx + dy * dy;
  // return (dist2 < (other.radius_ + radius_) * (other.radius_ + radius_));
	return false;
}
