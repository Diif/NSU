#ifndef GAME_FIELD_H
#define GAME_FIELD_H

#include "coordinates.h"
#include "iostream"
#include "ship.h"

class GameField {
 private:
  static const int field_size_ = 10;
  char *field_;
  char *field_enemy_view_;

 public:
  GameField();
  ~GameField();
  bool TryToPutShip(Ship &ship, Coordinates &coords);
  void TryToRemoveShip(Ship &ship, Coordinates &coords);
  void CleanField();
  void PrintMainField();  // нужно ли?
  void PrintMainFieldBorder();
  void PrintBothBorder();
  // private
  int GetMinCoordIndex();
  int GetMaxCoordIndex();
  int GetRowAndColumnSize();
  void PutShip(Ship &ship, Coordinates &coords);
  void PutShipHorizontal(Ship &ship, Coordinates &coords);
  void PutShipVertical(Ship &ship, Coordinates &coords);
  bool NoShipsAround(Ship &ship, Coordinates &coords);
  bool NoShipsAroundHorizontal(Ship &ship, Coordinates &coords);
  bool NoShipsAroundVertical(Ship &ship, Coordinates &coords);
  void RemoveShip(Ship &ship, Coordinates &coords);
  void RemoveShipHorizontal(Ship &ship, Coordinates &coords);
  void RemoveShipVertical(Ship &ship, Coordinates &coords);
};

#endif  // GAME_FIELD_H