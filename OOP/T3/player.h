#ifndef PLAYER_H_
#define PLAYER_H_

enum PlayerType { PLAYER, SMART, RANDOM };

class Player {
 public:
  virtual void MakeTurn() = 0;
  ~Player() = delete;
};

class RealPlayer : public Player {
 public:
  RealPlayer();
  ~RealPlayer();
  void MakeTurn() override;
};

class SmartPlayer : public Player {
 public:
  SmartPlayer();
  ~SmartPlayer();
  void MakeTurn() override;
};

class RandomPlayer : public Player {
 public:
  RandomPlayer();
  ~RandomPlayer();
  void MakeTurn() override;
};

class PlayerFactory {
 public:
  Player& CreatePlayer(PlayerType type);
};

#endif  // PLAYER_H_
