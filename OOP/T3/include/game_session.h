#ifndef GAME_SESSION_H_
#define GAME_SESSION_H_
#include <string.h>

#include "game_master.h"
#include "player.h"

class GameSession {
 public:
  int num_of_rounds_;
  int player1_score_ = 0;
  int player2_score_ = 0;

  GameMaster *game_master_;
  //  public:
  GameSession() = delete;
  GameSession(int num_of_rounds, PlayerType player1, PlayerType player2);
  ~GameSession();
  void StartNewRound();
  void StartSession();
  void PrintSessionResult();
};

// GameSession::~GameSession() {}
#endif  //  GAME_SESSION_H_