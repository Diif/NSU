#ifndef PLAYER_H_
#define PLAYER_H_

#include <cstdlib>
#include <ctime>

#include "coordinates.h"
#include "dynamic_input.h"
#include "game_field.h"
#include "ship.h"
enum PlayerType { PLAYER, SMART, RANDOM };

class Player {
 public:
  virtual void PrepareForNewRound() = 0;
  virtual void PlaceShip(Ship& ship, GameField& field) = 0;
  virtual void MakeTurn() = 0;
  virtual bool IsSuccessfulShot() = 0;
  virtual ~Player(){};
};

class RealPlayer : public Player {
 private:
  bool successful_shot_ = false;

 public:
  RealPlayer();
  ~RealPlayer();
  void PrepareForNewRound() override;
  void PlaceShip(Ship& ship, GameField& field) override;
  void MakeTurn() override;
  bool IsSuccessfulShot() override;
};

class SmartPlayer : public Player {
 private:
  bool successful_shot_ = false;

 public:
  SmartPlayer();
  ~SmartPlayer();
  void PrepareForNewRound() override;
  void PlaceShip(Ship& ship, GameField& field) override;
  void MakeTurn() override;
  bool IsSuccessfulShot() override;
};

class RandomPlayer : public Player {
 private:
  bool successful_shot_ = false;

 public:
  RandomPlayer();
  ~RandomPlayer();
  void PrepareForNewRound() override;
  void PlaceShip(Ship& ship, GameField& field) override;
  void MakeTurn() override;
  bool IsSuccessfulShot() override;
};

class PlayerFactory {
 public:
  Player& CreatePlayer(PlayerType type);
};

#endif  // PLAYER_H_
