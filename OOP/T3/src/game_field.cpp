#include "game_field.h"
// angle 0: **>
// angle 90: ^
//           *
//           *
GameField::GameField() {
  field_ = new char[field_size_ * field_size_];
  field_enemy_view_ = new char[field_size_ * field_size_];
  int rows = GetRowAndColumnSize();
  int clms = GetRowAndColumnSize();
  for (int i = 0; i < rows; i++) {
    int cur_row = i * rows;
    for (int j = 0; j < clms; j++) {
      field_enemy_view_[cur_row + j] = '+';
      field_[cur_row + j] = '+';
    }
  }
}

GameField::~GameField() { delete[] field_; }

inline int GameField::GetMaxCoordIndex() { return field_size_ - 1; }

inline int GameField::GetMinCoordIndex() { return 0; }

inline int GameField::GetRowAndColumnSize() { return field_size_; }

bool GameField::TryToPutShip(Ship &ship, Coordinates &coords) {
  int was_put = 0;
  if (NoShipsAround(ship, coords)) {
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

bool GameField::NoShipsAround(Ship &ship, Coordinates &coords) {
  bool no_ships = false;
  int angle = ship.GetAngle();
  if (angle == 0 || angle == 180) {
    no_ships = NoShipsAroundHorizontal(ship, coords);
  } else {
    no_ships = NoShipsAroundVertical(ship, coords);
  }
  return no_ships;
}

bool GameField::NoShipsAroundHorizontal(Ship &ship, Coordinates &coords) {
  int angle = ship.GetAngle();
  int row_len = GetRowAndColumnSize();
  int x_start;
  int x_end;
  int y_start;
  int y_end;
  y_start = coords.GetY();
  y_end = y_start;
  if (angle == 0) {
    x_start = coords.GetX();
    x_end = x_start + ship.GetSize() - 1;
  } else if (angle == 180) {
    x_start = coords.GetX() - ship.GetSize() + 1;
    x_end = coords.GetX();
  }
  if (x_start > 0) {
    x_start--;
  }
  if (x_end < GetMaxCoordIndex()) {
    x_end++;
  }
  if (y_start > 0) {
    y_start--;
  }
  if (y_end < GetMaxCoordIndex()) {
    y_end++;
  }
  for (int y = y_start; y <= y_end; y++) {
    int row = y * row_len;
    for (int x = x_start; x <= x_end; x++) {
      if (field_[row + x] == '*') {
        return false;
      }
    }
  }
  return true;
}

bool GameField::NoShipsAroundVertical(Ship &ship, Coordinates &coords) {
  int angle = ship.GetAngle();
  int row_len = GetRowAndColumnSize();
  int x_start;
  int x_end;
  int y_start;
  int y_end;
  x_start = coords.GetX();
  x_end = x_start;
  if (angle == 90) {
    y_start = coords.GetY() - ship.GetSize() + 1;
    y_end = coords.GetY();
  } else if (angle == 270) {
    y_start = coords.GetY();
    y_end = y_start + ship.GetSize() - 1;
  }
  if (x_start > 0) {
    x_start--;
  }
  if (x_end < GetMaxCoordIndex()) {
    x_end++;
  }
  if (y_start > 0) {
    y_start--;
  }
  if (y_end < GetMaxCoordIndex()) {
    y_end++;
  }
  for (int y = y_start; y <= y_end; y++) {
    int row = y * row_len;
    for (int x = x_start; x <= x_end; x++) {
      if (field_[row + x] == '*') {
        return false;
      }
    }
  }
  return true;
}

void GameField::CleanField() {
  int rows = GetRowAndColumnSize();
  int clms = rows;
  for (int i = 0; i < rows; i++) {
    int cur_row = i * rows;
    for (int j = 0; j < clms; j++) {
      field_[cur_row + j] = ' ';
    }
  }
}

void GameField::PrintMainField() {
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

void GameField::PrintMainFieldBorder() {
  int rows = GetRowAndColumnSize();
  int clms = rows;
  std::cout << " ABCDEFGHIJ" << std::endl;
  for (int i = 0; i < rows; i++) {
    int cur_row = i * rows;
    std::cout << static_cast<char>('0' + i);
    for (int j = 0; j < clms; j++) {
      std::cout << field_[cur_row + j];
    }
    std::cout << std::endl;
  }
};
void GameField::PrintBothBorder() {
  int rows = GetRowAndColumnSize();
  int clms = rows;
  std::cout << " ABCDEFGHIJ         ABCDEFGHIJ" << std::endl;
  for (int i = 0; i < rows; i++) {
    int cur_row = i * rows;
    std::cout << static_cast<char>('0' + i);
    for (int j = 0; j < clms; j++) {
      std::cout << field_[cur_row + j];
    }
    std::cout << "        " << static_cast<char>('0' + i);
    for (int j = 0; j < clms; j++) {
      std::cout << field_enemy_view_[cur_row + j];
    }
    std::cout << std::endl;
  }
};
