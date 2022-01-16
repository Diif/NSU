#include "game_master.h"
GameMaster::GameMaster(Player& player1, Player& player2)
    : player1_(player1),
      player2_(player2),
      first_player_won_(false),
      second_player_won_(false) {}

GameMaster::~GameMaster() {
  delete &player1_;
  delete &player2_;
}

void GameMaster::PrepareForNewRound() {
  first_player_won_ = false;
  second_player_won_ = false;
  field_p1_.CleanMainField();
  field_p2_.CleanMainField();
  field_p1_.CleanShootField();
  field_p2_.CleanShootField();
  player1_.PrepareForNewRound();
  player2_.PrepareForNewRound();
}

void GameMaster::StartRound() {
  PlaceShips();
  int num_of_live_titles_p1 = 20;
  int num_of_live_titles_p2 = 20;
  while (num_of_live_titles_p1 && num_of_live_titles_p2) {
    if (num_of_live_titles_p1) {
      player1_.MakeTurn(field_p1_, field_p2_);

      if (player1_.IsSuccessfulShot()) {
        num_of_live_titles_p2--;
      }
    }
    if (num_of_live_titles_p2) {
      player2_.MakeTurn(field_p2_, field_p1_);

      if (player2_.IsSuccessfulShot()) {
        num_of_live_titles_p1--;
      }
    }
  }
  system("clear");
  if (num_of_live_titles_p1) {
    field_p1_.PrintBothBorder();
    first_player_won_ = true;
    second_player_won_ = false;
  } else if (num_of_live_titles_p2) {
    field_p2_.PrintBothBorder();
    first_player_won_ = false;
    second_player_won_ = true;
  } else {
    field_p1_.PrintBothBorder();
    field_p2_.PrintBothBorder();
    first_player_won_ = false;
    second_player_won_ = false;
  }
}

void GameMaster::PlaceShips() {
  Ship ship(Ship::BATTLESHIP);

  const int MAX_TORPEDO_BOATS = 4;
  const int MAX_DESTROYERS = 3;
  const int MAX_CRUISERS = 2;
  player1_.PlaceShip(ship, field_p1_);
  ship.RestoreAngle();
  player2_.PlaceShip(ship, field_p2_);
  ship.ChangeShip(Ship::CRUISER);
  for (int i = 0; i < MAX_CRUISERS; i++) {
    ship.RestoreAngle();
    player1_.PlaceShip(ship, field_p1_);
    ship.RestoreAngle();
    player2_.PlaceShip(ship, field_p2_);
  }
  ship.ChangeShip(Ship::DESTROYER);
  for (int i = 0; i < MAX_DESTROYERS; i++) {
    ship.RestoreAngle();
    player1_.PlaceShip(ship, field_p1_);
    ship.RestoreAngle();
    player2_.PlaceShip(ship, field_p2_);
  }
  ship.ChangeShip(Ship::TORPEDO_BOAT);
  for (int i = 0; i < MAX_TORPEDO_BOATS; i++) {
    ship.RestoreAngle();
    player1_.PlaceShip(ship, field_p1_);
    ship.RestoreAngle();
    player2_.PlaceShip(ship, field_p2_);
  }
}

bool GameMaster::DidFirstPlayerWin() { return first_player_won_; };
bool GameMaster::DidSecondPlayerWin() { return second_player_won_; };