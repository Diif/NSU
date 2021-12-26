#include "ship.h"

Ship::Ship(int size) : size(size), angle(0) {}

Ship::~Ship() {}

int Ship::GetSize() { return size; }

int Ship::GetAngle() { return angle; }