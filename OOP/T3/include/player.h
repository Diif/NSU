#ifndef PLAYER_H_
#define PLAYER_H_

#include <cstdlib>
#include <ctime>
#include <exception>

#include "coordinates.h"
#include "dynamic_input.h"
#include "game_field.h"
#include "ship.h"
enum PlayerType { PLAYER, SMART, RANDOM };

class Player {
 public:
  virtual void PrepareForNewRound() = 0;
  virtual void PlaceShip(Ship& ship, GameField& field) = 0;
  virtual void MakeTurn(GameField& own_field, GameField& enemy_field) = 0;
  virtual bool IsSuccessfulShot() = 0;
  virtual ~Player(){};
};

class RealPlayer : public Player {
 private:
  bool successful_shot_;

 public:
  RealPlayer();
  ~RealPlayer();
  void PrepareForNewRound() override;
  void PlaceShip(Ship& ship, GameField& field) override;
  void MakeTurn(GameField& own_field, GameField& enemy_field) override;
  bool IsSuccessfulShot() override;
};

class SmartPlayer : public Player {
 private:
  bool successful_shot_;

 public:
  SmartPlayer();
  ~SmartPlayer();
  void PrepareForNewRound() override;
  void PlaceShip(Ship& ship, GameField& field) override;
  void MakeTurn(GameField& own_field, GameField& enemy_field) override;
  bool IsSuccessfulShot() override;
};

class RandomPlayer : public Player {
 private:
  bool successful_shot_;

 public:
  RandomPlayer();
  ~RandomPlayer();
  void PrepareForNewRound() override;
  void PlaceShip(Ship& ship, GameField& field) override;
  void MakeTurn(GameField& own_field, GameField& enemy_field) override;
  bool IsSuccessfulShot() override;
};

class PlayerFactory {
 public:
  Player& CreatePlayer(PlayerType type);
};

#endif  // PLAYER_H_
