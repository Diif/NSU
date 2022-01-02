#include "game_session.h"

GameSession::GameSession(int num_of_rounds, PlayerType player1,
                         PlayerType player2)
    : num_of_rounds_(num_of_rounds) {
  PlayerFactory factory;
  Player& p1 = factory.CreatePlayer(player1);
  Player& p2 = factory.CreatePlayer(player2);
  game_master_ = new GameMaster(p1, p2);
}

GameSession::~GameSession() { delete game_master_; }

void GameSession::StartSession() {
  int cur_round = 1;
  while (cur_round <= num_of_rounds_) {
    StartNewRound();
    bool result = game_master_->DidFirstPlayerWin();
    if (result) {
      player1_score_++;
    } else {
      player2_score_++;
    }
    cur_round++;
  }
}

void GameSession::StartNewRound() {
  game_master_->PrepareForNewRound();
  game_master_->StartRound();
}

void GameSession::PrintSessionResult() {
  if (player1_score_ > player2_score_) {
    std::cout << "The first player won!";
  }
  if (player1_score_ < player2_score_) {
    std::cout << "The second player won!";
  }
  if (player1_score_ == player2_score_) {
    std::cout << "Draw!";
  }
}
