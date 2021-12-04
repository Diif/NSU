#ifndef GAME_MASTER_H_
#define GAME_MASTER_H_

#include "player.h"

class GameMaster {
 private:
  Player& player1_;
  Player& player2_;
  
 public:
  GameMaster(/* args */) = default;
  ~GameMaster();
};

// GameMaster::GameMaster(/* args */) {}

// GameMaster::~GameMaster() {}

#endif  // GAME_MASTER_H_