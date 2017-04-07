#include <vector>
#include <iostream>
#include <stdexcept>
#include <cmath>

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

bool Sprite::hits(const Sprite& other) const noexcept
{
	return (abs(cx_ - other.cx_) * 2 < (width_ + other.width_)) &&
		(abs(cy_ - other.cy_) * 2 < (height_ + other.height_));
}

bool Sprite::getDirection() const noexcept
{
	return direction_;
}

void Sprite::flip() noexcept
{
	direction_ = !direction_;
}

void Sprite::setHorizontalVelocity(double hv) noexcept
{
	hv_ = hv;
}

void Sprite::setVerticalVelocity(double vv) noexcept
{
	vv_ = vv;
}

void Sprite::evolve() noexcept
{
	cx_ += hv_;
	cy_ -= vv_;
}
