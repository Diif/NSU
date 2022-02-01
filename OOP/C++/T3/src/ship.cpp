#include "ship.h"

Ship::Ship(int size) : size_(size), angle_(0) {}

Ship::~Ship() {}

int Ship::GetSize() { return size_; }

int Ship::GetAngle() { return angle_; }

void Ship::ChangeShip(ShipType type) { size_ = static_cast<int>(type); }

void Ship::RotateClockwise() {
  if (angle_ == 0) {
    angle_ = 270;
  } else {
    angle_ = angle_ - 90;
  }
}

void Ship::RotateCounterClockwise() { angle_ = (angle_ + 90) % 360; }

void Ship::RestoreAngle() { angle_ = 0; }
