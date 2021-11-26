#ifndef SCIPT_H_
#define SCIPT_H_

#include "game_session.h"

enum PlayerType { PLAYER, SMART, RANDOM };

class Script {
 private:
  int count_of_rounds;
  PlayerType fst_player;
  PlayerType snd_player;

 public:
  Script(int count_of_rounds, PlayerType fst_player, PlayerType snd_player);
  GameSession& Run();
  ~Script() = default;
};

Script::Script(int count_of_rounds, PlayerType fst_player,
               PlayerType snd_player)
    : count_of_rounds(count_of_rounds),
      fst_player(fst_player),
      snd_player(snd_player) {}

Script

#endif  // SCIPT_H_