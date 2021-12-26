#include "coordinates.h"

Coordinates::Coordinates() {}

Coordinates::~Coordinates() {}

void Coordinates::SetCoordinates(char clmn, int row) {
  y = row;
  if ('A' <= clmn <= 'J') {
    x = clmn - 'A';
  }
}

void Coordinates::SetAbsCoordinates(int column, int row) {
  x = column;
  y = row;
}

int Coordinates::GetX() { return x; }
int Coordinates::GetY() { return y; }