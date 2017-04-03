#include <vector>
#include <iostream>
#include <stdexcept>

#include "Sprite.h"
#include "SpriteType.h"

using namespace std;
using namespace project;

Sprite::Sprite(SpriteType type, int width, int height, double startX,
	double startY, int idx) : type_(type), width_(width), height_(height),
	cx_(startX), cy_(startY), imageIndex_(idx) {}

int Sprite::getXCoordinate() const noexcept
{
  return int(cx_ - (width_ / 2));
}

int Sprite::getYCoordinate() const noexcept
{
  return int(cy_ - (height_ / 2));
}

int Sprite::getWidth() const noexcept
{
	return width_;
}

int Sprite::getHeight() const noexcept
{
	return height_;
}

int Sprite::getImageIndex() const noexcept
{
  return imageIndex_;
}

void Sprite::moveHorizontal(double delta) noexcept
{
	cx_ += delta * hv_;
}

bool Sprite::hits(const Sprite& other) const noexcept
{
	//TODO: make this work based not on radius
  double dx = other.cx_ - cx_;
  double dy = other.cy_ - cy_;
  double dist2 = dx * dx + dy * dy;
  // return (dist2 < (other.radius_ + radius_) * (other.radius_ + radius_));
	return false;
}

bool Sprite::getDirection() const noexcept
{
	return hv_ < 0.0;
}

void Sprite::flip() noexcept
{
	hv_ = -(hv_);
}
