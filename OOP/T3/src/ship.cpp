#include "ship.h"

Ship::Ship(int size) : size_(size), angle_(0) {}

Ship::~Ship() {}

int Ship::GetSize() { return size_; }

int Ship::GetAngle() { return angle_; }

void Ship::ChangeShip(ShipType type) { size_ = static_cast<int>(type); }