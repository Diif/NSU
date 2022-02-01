#include "game_field.h"
// angle 0: **>
// angle 90: ^
//           *
//           *
GameField::GameField() {
  field_ = new char[field_size_ * field_size_];
  shoot_field_ = new char[field_size_ * field_size_];
  int rows = GetRowAndColumnSize();
  int clms = GetRowAndColumnSize();
  for (int i = 0; i < rows; i++) {
    int cur_row = i * rows;
    for (int j = 0; j < clms; j++) {
      shoot_field_[cur_row + j] = ' ';
      field_[cur_row + j] = ' ';
    }
  }
}

GameField::~GameField() {
  delete[] field_;
  delete[] shoot_field_;
}

inline int GameField::GetMaxCoordIndex() { return field_size_ - 1; }

inline int GameField::GetMinCoordIndex() { return 0; }

inline int GameField::GetRowAndColumnSize() { return field_size_; }

bool GameField::TryToPutShip(Ship &ship, Coordinates &coords,
                             bool is_shoot_field) {
  int was_put = 0;
  if (ship.GetAngle() == 0) {
    if (coords.GetX() + ship.GetSize() - 1 <= GetMaxCoordIndex() &&
        coords.GetX() >= GetMinCoordIndex() &&
        coords.GetY() <= GetMaxCoordIndex() &&
        coords.GetY() >= GetMinCoordIndex()) {
      if (NoShipsAround(ship, coords, is_shoot_field)) {
        was_put = 1;
        PutShip(ship, coords, is_shoot_field);
      }
    }
  } else if (ship.GetAngle() == 90) {
    if (coords.GetX() <= GetMaxCoordIndex() &&
        coords.GetX() >= GetMinCoordIndex() &&
        coords.GetY() - ship.GetSize() + 1 >= GetMinCoordIndex() &&
        coords.GetY() <= GetMaxCoordIndex()) {
      if (NoShipsAround(ship, coords, is_shoot_field)) {
        was_put = 1;
        PutShip(ship, coords, is_shoot_field);
      }
    }
  } else if (ship.GetAngle() == 180) {
    if (coords.GetX() - ship.GetSize() + 1 >= GetMinCoordIndex() &&
        coords.GetX() <= GetMaxCoordIndex() &&
        coords.GetY() <= GetMaxCoordIndex() &&
        coords.GetY() >= GetMinCoordIndex()) {
      if (NoShipsAround(ship, coords, is_shoot_field)) {
        was_put = 1;
        PutShip(ship, coords, is_shoot_field);
      }
    }
  } else if (ship.GetAngle() == 270) {
    if (coords.GetX() <= GetMaxCoordIndex() &&
        coords.GetX() >= GetMinCoordIndex() &&
        coords.GetY() + ship.GetSize() - 1 <= GetMaxCoordIndex() &&
        coords.GetY() >= GetMinCoordIndex()) {
      if (NoShipsAround(ship, coords, is_shoot_field)) {
        was_put = 1;
        PutShip(ship, coords, is_shoot_field);
      }
    }
  }

  return was_put;
}

void GameField::PutShip(Ship &ship, Coordinates &coords, bool is_shoot_field) {
  if (ship.GetAngle() == 0 || ship.GetAngle() == 180) {
    PutShipHorizontal(ship, coords, is_shoot_field);
  } else {
    PutShipVertical(ship, coords, is_shoot_field);
  }
}

void GameField::PutShipHorizontal(Ship &ship, Coordinates &coords,
                                  bool is_shoot_field) {
  char *field;
  if (is_shoot_field) {
    field = shoot_field_;
  } else {
    field = field_;
  }
  int len = ship.GetSize();
  int row = coords.GetY() * GetRowAndColumnSize();
  if (ship.GetAngle() == 0) {
    for (int i = coords.GetX(); len > 0; len--, i++) {
      field[row + i] = '*';
    }
  }
  if (ship.GetAngle() == 180) {
    for (int i = coords.GetX(); len > 0; len--, i--) {
      field[row + i] = '*';
    }
  }
}

void GameField::PutShipVertical(Ship &ship, Coordinates &coords,
                                bool is_shoot_field) {
  char *field;
  if (is_shoot_field) {
    field = shoot_field_;
  } else {
    field = field_;
  }
  int len = ship.GetSize();
  int column = coords.GetX();
  int row_len = GetRowAndColumnSize();
  if (ship.GetAngle() == 90) {
    for (int i = coords.GetY(); len > 0; len--, i--) {
      field[i * row_len + column] = '*';
    }
  }
  if (ship.GetAngle() == 270) {
    for (int i = coords.GetY(); len > 0; len--, i++) {
      field[i * row_len + column] = '*';
    }
  }
}

void GameField::TryToRemoveShip(Ship &ship, Coordinates &coords,
                                bool is_shoot_field) {
  if (ship.GetAngle() == 0) {
    if (coords.GetX() + ship.GetSize() - 1 <= GetMaxCoordIndex() &&
        coords.GetX() >= GetMinCoordIndex() &&
        coords.GetY() <= GetMaxCoordIndex() &&
        coords.GetY() >= GetMinCoordIndex()) {
      RemoveShip(ship, coords, is_shoot_field);
    }
  }
  if (ship.GetAngle() == 90) {
    if (coords.GetX() <= GetMaxCoordIndex() &&
        coords.GetX() >= GetMinCoordIndex() &&
        coords.GetY() - ship.GetSize() + 1 >= GetMinCoordIndex() &&
        coords.GetY() <= GetMaxCoordIndex()) {
      RemoveShip(ship, coords, is_shoot_field);
    }
  }
  if (ship.GetAngle() == 180) {
    if (coords.GetX() - ship.GetSize() + 1 >= GetMinCoordIndex() &&
        coords.GetX() <= GetMaxCoordIndex() &&
        coords.GetY() <= GetMaxCoordIndex() &&
        coords.GetY() >= GetMinCoordIndex()) {
      RemoveShip(ship, coords, is_shoot_field);
    }
  }
  if (ship.GetAngle() == 270) {
    if (coords.GetX() <= GetMaxCoordIndex() &&
        coords.GetX() >= GetMinCoordIndex() &&
        coords.GetY() + ship.GetSize() - 1 <= GetMaxCoordIndex() &&
        coords.GetY() >= GetMinCoordIndex()) {
      RemoveShip(ship, coords, is_shoot_field);
    }
  }
}

void GameField::RemoveShip(Ship &ship, Coordinates &coords,
                           bool is_shoot_field) {
  if (ship.GetAngle() == 0 || ship.GetAngle() == 180) {
    RemoveShipHorizontal(ship, coords, is_shoot_field);
  } else {
    RemoveShipVertical(ship, coords, is_shoot_field);
  }
}

void GameField::RemoveShipHorizontal(Ship &ship, Coordinates &coords,
                                     bool is_shoot_field) {
  char *field;
  if (is_shoot_field) {
    field = shoot_field_;
  } else {
    field = field_;
  }
  int len = ship.GetSize();
  int row = coords.GetY() * GetRowAndColumnSize();
  if (ship.GetAngle() == 0) {
    for (int i = coords.GetX(); len > 0; len--, i++) {
      field[row + i] = ' ';
    }
  }
  if (ship.GetAngle() == 180) {
    for (int i = coords.GetX(); len > 0; len--, i--) {
      field[row + i] = ' ';
    }
  }
}

void GameField::RemoveShipVertical(Ship &ship, Coordinates &coords,
                                   bool is_shoot_field) {
  char *field;
  if (is_shoot_field) {
    field = shoot_field_;
  } else {
    field = field_;
  }
  int len = ship.GetSize();
  int column = coords.GetX();
  int row_len = GetRowAndColumnSize();
  if (ship.GetAngle() == 90) {
    for (int i = coords.GetY(); len > 0; len--, i--) {
      field[i * row_len + column] = ' ';
    }
  }
  if (ship.GetAngle() == 270) {
    for (int i = coords.GetY(); len > 0; len--, i++) {
      field[i * row_len + column] = ' ';
    }
  }
}

bool GameField::NoShipsAround(Ship &ship, Coordinates &coords,
                              bool is_shoot_field) {
  bool no_ships = false;
  int angle = ship.GetAngle();
  if (angle == 0 || angle == 180) {
    no_ships = NoShipsAroundHorizontal(ship, coords, is_shoot_field);
  } else {
    no_ships = NoShipsAroundVertical(ship, coords, is_shoot_field);
  }
  return no_ships;
}

bool GameField::NoShipsAroundHorizontal(Ship &ship, Coordinates &coords,
                                        bool is_shoot_field) {
  int angle = ship.GetAngle();
  int row_len = GetRowAndColumnSize();
  int x_start;
  int x_end;
  int y_start;
  int y_end;
  char *field;
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
  if (is_shoot_field) {
    field = shoot_field_;
  } else {
    field = field_;
  }
  for (int y = y_start; y <= y_end; y++) {
    int row = y * row_len;
    for (int x = x_start; x <= x_end; x++) {
      if (field[row + x] == '*') {
        return false;
      }
    }
  }
  return true;
}

bool GameField::NoShipsAroundVertical(Ship &ship, Coordinates &coords,
                                      bool is_shoot_field) {
  int angle = ship.GetAngle();
  int row_len = GetRowAndColumnSize();
  int x_start;
  int x_end;
  int y_start;
  int y_end;
  char *field;
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
  if (is_shoot_field) {
    field = shoot_field_;
  } else {
    field = field_;
  }
  if (y_start < 0 || x_start < 0 || x_end < 0 || y_end < 0) {
    int sd = 4;
  }
  for (int y = y_start; y <= y_end; y++) {
    int row = y * row_len;
    for (int x = x_start; x <= x_end; x++) {
      if (field[row + x] == '*') {
        return false;
      }
    }
  }
  return true;
}

bool GameField::Shoot(Coordinates &coords, GameField &own_field,
                      GameField &enemy_field) {
  char enemy_title = enemy_field.GetSymbol(coords, false);
  if (enemy_title == '*') {
    enemy_field.PlaceSymbol(coords, 'X', false);
    own_field.PlaceSymbol(coords, 'X', true);
    return true;
  } else if (enemy_title == ' ') {
    enemy_field.PlaceSymbol(coords, 'O', false);
    own_field.PlaceSymbol(coords, 'O', true);
    return false;
  }
  return false;
}

void GameField::PlaceSymbol(Coordinates &coords, char symb,
                            bool is_shoot_field) {
  int rows = GetRowAndColumnSize();
  int x = coords.GetX();
  int y = coords.GetY() * rows;
  if (is_shoot_field) {
    shoot_field_[y + x] = symb;
  } else {
    field_[y + x] = symb;
  }
}

char GameField::GetSymbol(Coordinates &coords, bool is_shoot_field) {
  int rows = GetRowAndColumnSize();
  int x = coords.GetX();
  int y = coords.GetY() * rows;
  if (is_shoot_field) {
    return shoot_field_[y + x];
  } else {
    return field_[y + x];
  }
}

bool GameField::IsShootingTitleFree(Coordinates &coords) {
  char title = GetSymbol(coords, true);
  if (title == ' ') {
    return true;
  }
  return false;
}

bool GameField::NoSymbolsAroundInShootingField(Coordinates &coords, char symb) {
  int row_len = GetRowAndColumnSize();
  int x_start;
  int x_end;
  int y_start;
  int y_end;
  char *field;
  x_start = coords.GetX();
  x_end = x_start;
  y_start = coords.GetY();
  y_end = y_start;

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
  field = shoot_field_;
  for (int y = y_start; y <= y_end; y++) {
    int row = y * row_len;
    for (int x = x_start; x <= x_end; x++) {
      if (field[row + x] == symb) {
        return false;
        PrintBothBorder();
      }
    }
  }
  return true;
}

void GameField::CleanMainField() {
  int rows = GetRowAndColumnSize();
  int clms = rows;
  for (int i = 0; i < rows; i++) {
    int cur_row = i * rows;
    for (int j = 0; j < clms; j++) {
      field_[cur_row + j] = ' ';
    }
  }
}

void GameField::CleanShootField() {
  int rows = GetRowAndColumnSize();
  int clms = rows;
  for (int i = 0; i < rows; i++) {
    int cur_row = i * rows;
    for (int j = 0; j < clms; j++) {
      shoot_field_[cur_row + j] = ' ';
    }
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
  std::cout << "  ABCDEFGHIJ         ABCDEFGHIJ" << std::endl;
  for (int i = 0; i < rows; i++) {
    int cur_row = i * rows;
    std::cout << static_cast<char>('0' + i) << " ";
    for (int j = 0; j < clms; j++) {
      if (field_[cur_row + j] == 'X') {
        std::cout << "\033[31m" << field_[cur_row + j] << "\033[0m";
      } else {
        std::cout << field_[cur_row + j];
      }
    }
    std::cout << "        " << static_cast<char>('0' + i);
    for (int j = 0; j < clms; j++) {
      if (shoot_field_[cur_row + j] == 'X') {
        std::cout << "\033[31m" << shoot_field_[cur_row + j] << "\033[0m";
      } else {
        std::cout << shoot_field_[cur_row + j];
      }
    }
    std::cout << std::endl;
  }
}

void GameField::PrintFieldPlacingStage() {
  int rows = GetRowAndColumnSize();
  int clms = rows;
  std::cout << "  ABCDEFGHIJ" << std::endl;
  for (int i = 0; i < rows; i++) {
    int cur_row = i * rows;
    std::cout << static_cast<char>('0' + i) << " ";
    for (int j = 0; j < clms; j++) {
      if (shoot_field_[cur_row + j] == '*') {
        std::cout << shoot_field_[cur_row + j];  // buf field
      } else {
        std::cout << field_[cur_row + j];
      }
    }
    std::cout << std::endl;
  }
}
