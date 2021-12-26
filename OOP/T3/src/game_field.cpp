#include "game_field.h"
// angle 0: **>
// angle 90: ^
//           *
//           *
GameField::GameField(int field_size) : size_(field_size) {
  field_ = new char[field_size * field_size];
  int rows = GetRowAndColumnSize();
  int clms = GetRowAndColumnSize();
  for (int i = 0; i < rows; i++) {
    int cur_row = i * rows;
    for (int j = 0; j < clms; j++) {
      field_[cur_row + j] = '-';
    }
  }
}

GameField::~GameField() { delete[] field_; }

inline int GameField::GetMaxCoordIndex() { return size_ - 1; }

inline int GameField::GetMinCoordIndex() { return 0; }

inline int GameField::GetRowAndColumnSize() { return size_; }

int GameField::TryToPutShip(Ship &ship, Coordinates &coords) {
  int was_put = 0;
  if (ship.GetAngle() == 0) {
    if (coords.GetX() + ship.GetSize() - 1 <= GetMaxCoordIndex() &&
        coords.GetX() >= GetMinCoordIndex() &&
        coords.GetY() <= GetMaxCoordIndex() &&
        coords.GetY() >= GetMinCoordIndex()) {
      was_put = 1;
      PutShip(ship, coords);
    }
  } else if (ship.GetAngle() == 90) {
    if (coords.GetX() <= GetMaxCoordIndex() &&
        coords.GetX() >= GetMinCoordIndex() &&
        coords.GetY() + ship.GetSize() - 1 <= GetMaxCoordIndex() &&
        coords.GetY() >= GetMinCoordIndex()) {
      was_put = 1;
      PutShip(ship, coords);
    }
  } else if (ship.GetAngle() == 180) {
    if (coords.GetX() - ship.GetSize() + 1 <= GetMaxCoordIndex() &&
        coords.GetX() >= GetMinCoordIndex() &&
        coords.GetY() <= GetMaxCoordIndex() &&
        coords.GetY() >= GetMinCoordIndex()) {
      was_put = 1;
      PutShip(ship, coords);
    }
  } else if (ship.GetAngle() == 270) {
    if (coords.GetX() <= GetMaxCoordIndex() &&
        coords.GetX() >= GetMinCoordIndex() &&
        coords.GetY() - ship.GetSize() + 1 <= GetMaxCoordIndex() &&
        coords.GetY() >= GetMinCoordIndex()) {
      was_put = 1;
      PutShip(ship, coords);
    }
  }
  return was_put;
}

void GameField::PutShip(Ship &ship, Coordinates &coords) {
  if (ship.GetAngle() == 0 || ship.GetAngle() == 180) {
    PutShipHorizontal(ship, coords);
  } else {
    PutShipVertical(ship, coords);
  }
}

void GameField::PutShipHorizontal(Ship &ship, Coordinates &coords) {
  int len = ship.GetSize();
  int row = coords.GetY() * GetRowAndColumnSize();
  if (ship.GetAngle() == 0) {
    for (int i = coords.GetX(); len > 0; len--, i++) {
      field_[row + i] = '*';
    }
  }
  if (ship.GetAngle() == 180) {
    for (int i = coords.GetX(); len > 0; len--, i++) {
      field_[row - i] = '*';
    }
  }
}

void GameField::PutShipVertical(Ship &ship, Coordinates &coords) {
  int len = ship.GetSize();
  int column = coords.GetX();
  int row_len = GetRowAndColumnSize();
  if (ship.GetAngle() == 90) {
    for (int i = coords.GetY(); len > 0; len--, i--) {
      field_[i * row_len + column] = '*';
    }
  }
  if (ship.GetAngle() == 270) {
    for (int i = coords.GetY(); len > 0; len--, i++) {
      field_[i * row_len + i] = '*';
    }
  }
}

void GameField::TryToRemoveShip(Ship &ship, Coordinates &coords) {
  if (ship.GetAngle() == 0) {
    if (coords.GetX() + ship.GetSize() - 1 <= GetMaxCoordIndex() &&
        coords.GetX() >= GetMinCoordIndex() &&
        coords.GetY() <= GetMaxCoordIndex() &&
        coords.GetY() >= GetMinCoordIndex()) {
      RemoveShip(ship, coords);
    }
  }
  if (ship.GetAngle() == 90) {
    if (coords.GetX() <= GetMaxCoordIndex() &&
        coords.GetX() >= GetMinCoordIndex() &&
        coords.GetY() + ship.GetSize() - 1 <= GetMaxCoordIndex() &&
        coords.GetY() >= GetMinCoordIndex()) {
      RemoveShip(ship, coords);
    }
  }
  if (ship.GetAngle() == 180) {
    if (coords.GetX() - ship.GetSize() + 1 <= GetMaxCoordIndex() &&
        coords.GetX() >= GetMinCoordIndex() &&
        coords.GetY() <= GetMaxCoordIndex() &&
        coords.GetY() >= GetMinCoordIndex()) {
      RemoveShip(ship, coords);
    }
  }
  if (ship.GetAngle() == 270) {
    if (coords.GetX() <= GetMaxCoordIndex() &&
        coords.GetX() >= GetMinCoordIndex() &&
        coords.GetY() - ship.GetSize() + 1 <= GetMaxCoordIndex() &&
        coords.GetY() >= GetMinCoordIndex()) {
      RemoveShip(ship, coords);
    }
  }
}

void GameField::RemoveShip(Ship &ship, Coordinates &coords) {
  if (ship.GetAngle() == 0 || ship.GetAngle() == 180) {
    RemoveShipHorizontal(ship, coords);
  } else {
    RemoveShipVertical(ship, coords);
  }
}

void GameField::RemoveShipHorizontal(Ship &ship, Coordinates &coords) {
  int len = ship.GetSize();
  int row = coords.GetY() * GetRowAndColumnSize();
  if (ship.GetAngle() == 0) {
    for (int i = coords.GetX(); len > 0; len--, i++) {
      field_[row + i] = ' ';
    }
  }
  if (ship.GetAngle() == 180) {
    for (int i = coords.GetX(); len > 0; len--, i++) {
      field_[row - i] = ' ';
    }
  }
}

void GameField::RemoveShipVertical(Ship &ship, Coordinates &coords) {
  int len = ship.GetSize();
  int column = coords.GetX();
  int row_len = GetRowAndColumnSize();
  if (ship.GetAngle() == 90) {
    for (int i = coords.GetY(); len > 0; len--, i--) {
      field_[i * row_len + column] = ' ';
    }
  }
  if (ship.GetAngle() == 270) {
    for (int i = coords.GetY(); len > 0; len--, i++) {
      field_[i * row_len + i] = ' ';
    }
  }
}

void GameField::PrintField() {
  int rows = GetRowAndColumnSize();
  int clms = rows;
  for (int i = 0; i < rows; i++) {
    int cur_row = i * rows;
    for (int j = 0; j < clms; j++) {
      std::cout << field_[cur_row + j];
    }
    std::cout << std::endl;
  }
}