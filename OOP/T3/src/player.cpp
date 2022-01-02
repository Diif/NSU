#include "player.h"

Player &PlayerFactory::CreatePlayer(PlayerType type) {
  if (type == PLAYER) {
    return *(new RealPlayer{});
  }
  if (type == SMART) {
    return *(new SmartPlayer{});
  }
  if (type == RANDOM) {
    return *(new RandomPlayer{});
  }
}

RealPlayer::RealPlayer() {}

RealPlayer::~RealPlayer() {}

SmartPlayer::SmartPlayer() {}

SmartPlayer::~SmartPlayer() {}

RandomPlayer::RandomPlayer() { std::srand(std::time(NULL)); }
RandomPlayer::~RandomPlayer() {}

void RealPlayer::PrepareForNewRound(){};

void RandomPlayer::PrepareForNewRound() { std::srand(std::time(NULL)); };

void SmartPlayer::PrepareForNewRound() { std::srand(std::time(NULL)); };

void RealPlayer::MakeTurn(){};

void RandomPlayer::MakeTurn(){};

void SmartPlayer::MakeTurn(){};

void RealPlayer::PlaceShip(Ship &ship, GameField &field) {
  Coordinates coords;
  int x = 4, y = 4;
  coords.SetAbsCoordinates(x, y);
  field.TryToPutShip(ship, coords);

  char input = 0;
  int placed = 0;
  field.PrintMainField();
  field.TryToRemoveShip(ship, coords);
  while (input != ' ' || !placed) {
    input = dynIn::Input();
    if (input == 'w') {
      if (y > 0) {
        if (placed) {
          field.TryToRemoveShip(ship, coords);
          placed = 0;
        }
        y--;
        coords.SetAbsCoordinates(x, y);
        if (field.TryToPutShip(ship, coords)) {
          system("clear");
          field.PrintMainField();
          placed = 1;
        }
      }
    }
    if (input == 's') {
      if (y < 9) {
        if (placed) {
          field.TryToRemoveShip(ship, coords);
          placed = 0;
        }
        y++;
        coords.SetAbsCoordinates(x, y);
        if (field.TryToPutShip(ship, coords)) {
          system("clear");
          field.PrintMainField();
          placed = 1;
        }
      }
    }
    if (input == 'a') {
      if (x > 0) {
        if (placed) {
          field.TryToRemoveShip(ship, coords);
          placed = 0;
        }
        x--;
        coords.SetAbsCoordinates(x, y);
        if (field.TryToPutShip(ship, coords)) {
          system("clear");
          field.PrintMainField();
          placed = 1;
        }
      }
    }
    if (input == 'd') {
      if (x < 9 - ship.GetSize() + 1) {
        if (placed) {
          field.TryToRemoveShip(ship, coords);
          placed = 0;
        }
        x++;
        coords.SetAbsCoordinates(x, y);
        if (field.TryToPutShip(ship, coords)) {
          system("clear");
          field.PrintMainField();
          placed = 1;
        }
      }
    }
  }
}

void RandomPlayer::PlaceShip(Ship &ship, GameField &field){};

void SmartPlayer::PlaceShip(Ship &ship, GameField &field){};

bool RealPlayer::IsSuccessfulShot() { return successful_shot_; };

bool RandomPlayer::IsSuccessfulShot() { return successful_shot_; };

bool SmartPlayer::IsSuccessfulShot() { return successful_shot_; };
