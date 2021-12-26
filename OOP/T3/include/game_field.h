#ifndef GAME_FIELD_H
#define GAME_FIELD_H

#include "coordinates.h"
#include "iostream"
#include "ship.h"

class GameField {
 private:
  int size_;
  char *field_;

 public:
  GameField(int field_size);
  ~GameField();
  int TryToPutShip(Ship &ship, Coordinates &coords);
  void TryToRemoveShip(Ship &ship, Coordinates &coords);
  void PrintField();
  // private
  int GetMinCoordIndex();
  int GetMaxCoordIndex();
  int GetRowAndColumnSize();
  void PutShip(Ship &ship, Coordinates &coords);
  void PutShipHorizontal(Ship &ship, Coordinates &coords);
  void PutShipVertical(Ship &ship, Coordinates &coords);
  void RemoveShip(Ship &ship, Coordinates &coords);
  void RemoveShipHorizontal(Ship &ship, Coordinates &coords);
  void RemoveShipVertical(Ship &ship, Coordinates &coords);
};

#endif  // GAME_FIELD_H