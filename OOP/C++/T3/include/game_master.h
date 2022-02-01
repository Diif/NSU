#ifndef GAME_MASTER_H_
#define GAME_MASTER_H_

#include "game_field.h"
#include "player.h"
class GameMaster {
 private:
  bool first_player_won_;
  bool second_player_won_;
  Player& player1_;
  Player& player2_;
  GameField field_p1_;
  GameField field_p2_;

 public:
  GameMaster(Player& player1, Player& player2);
  ~GameMaster();
  void StartRound();
  bool DidFirstPlayerWin();
  bool DidSecondPlayerWin();
  // private
  void PrepareForNewRound();
  void PlaceShips();
};

// GameMaster::GameMaster(/* args */) {}

// GameMaster::~GameMaster() {}

#endif  // GAME_MASTER_H_