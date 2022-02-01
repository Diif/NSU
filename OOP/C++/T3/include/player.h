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
  bool finding_state_;
  bool successful_shot_;
  bool default_way_ended_;
  bool one_size_was_checked;
  int count_enemy_boats_;
  int count_enemy_destroyers_;
  int count_enemy_cruisers_;
  int count_enemy_battleships_;
  int first_ship_hit_;
  int prev_shot_;
  int cur_shot_;
  int next_shot_;
  int next_default_title;
  int streak_;
  enum Direction { NONE = 0, TOP = 1, RIGHT = 2, BOT = 3, LEFT = 4 };
  Direction side_to_check_;
  Direction found_axis_;
  Coordinates buf_coords;

  void GoToFindingMode(GameField& own_field);
  void CheckShipExistenceAndUpdateFindingState();
  Direction GetNextDirection(Direction direction);
  Direction GetOppositeDirection(Direction direction);
  int GetNextTitleByDirection(Direction direction, int title);

  void UpdateShipsCount();
  int GetFreeTitleForRadomShot(GameField& own_field);
  SmartPlayer::Direction GetNextValidSide();
  int GetNextDefaultTitle();
  bool IsValidNextTitle(int new_title);
  bool UselessShot(Coordinates coords, GameField& own_field);

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
