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

void Coordinates::SetByTitle(int title) {
  x = title % 10;
  y = static_cast<int>(title / 10);
}

int Coordinates::GetTitleByCoords() { return y * 10 + x; }