#ifndef GAME_SESSION_H_
#define GAME_SESSION_H_
#include <string.h>

#include "game_master.h"
#include "player.h"

class GameSession {
 public:
  static const int field_size_ = 10;
  int num_of_rounds_;
  int player1_score_;
  int player2_score_;

  GameMaster *game_master;
  //  public:
  GameSession() = delete;
  GameSession(int num_of_rounds, PlayerType player1, PlayerType player2);
  ~GameSession() = default;
  void StartNewRound();
};

// GameSession::~GameSession() {}
#endif  //  GAME_SESSION_H_