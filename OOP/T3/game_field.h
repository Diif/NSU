#ifndef GAME_FIELD_H
#define GAME_FIELD_H

#include "ship.h"

class GameField {
 private:
  char *field_;

 public:
  GameField(int field_size);
  ~GameField();
  void TryToPutShip();
};

#endif  // GAME_FIELD_H