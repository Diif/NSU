#ifndef GAME_FIELD_H
#define GAME_FIELD_H

#include "coordinates.h"
#include "iostream"
#include "ship.h"

class GameField {
 private:
  static const int field_size_ = 10;
  char *field_;
  char *shoot_field_;

 public:
  GameField();
  ~GameField();
  bool TryToPutShip(Ship &ship, Coordinates &coords, bool is_shoot_field);
  void TryToRemoveShip(Ship &ship, Coordinates &coords, bool is_shoot_field);
  bool Shoot(Coordinates &coords, GameField &own_field, GameField &enemy_field);
  void CleanMainField();
  void CleanShootField();
  void PrintMainFieldBorder();
  void PrintBothBorder();
  void PrintFieldPlacingStage();
  char GetSymbol(Coordinates &coords, bool is_shoot_field);
  void PlaceSymbol(Coordinates &coords, char symb, bool is_shoot_field);
  bool NoSymbolsAroundInShootingField(Coordinates &coords, char symb);
  bool IsShootingTitleFree(Coordinates &coords);

  // private
  int GetMinCoordIndex();
  int GetMaxCoordIndex();
  int GetRowAndColumnSize();
  void PutShip(Ship &ship, Coordinates &coords, bool is_shoot_field);
  void PutShipHorizontal(Ship &ship, Coordinates &coords, bool is_shoot_field);
  void PutShipVertical(Ship &ship, Coordinates &coords, bool is_shoot_field);
  bool NoShipsAround(Ship &ship, Coordinates &coords, bool is_shoot_field);
  bool NoShipsAroundHorizontal(Ship &ship, Coordinates &coords,
                               bool is_shoot_field);
  bool NoShipsAroundVertical(Ship &ship, Coordinates &coords,
                             bool is_shoot_field);
  void RemoveShip(Ship &ship, Coordinates &coords, bool is_shoot_field);
  void RemoveShipHorizontal(Ship &ship, Coordinates &coords,
                            bool is_shoot_field);
  void RemoveShipVertical(Ship &ship, Coordinates &coords, bool is_shoot_field);
};

#endif  // GAME_FIELD_H