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

RealPlayer::RealPlayer() { successful_shot_ = false; }

RealPlayer::~RealPlayer() {}

SmartPlayer::SmartPlayer() { successful_shot_ = false; }

SmartPlayer::~SmartPlayer() {}

RandomPlayer::RandomPlayer() {
  successful_shot_ = false;
  std::srand(std::time(NULL));
}
RandomPlayer::~RandomPlayer() {}

void RealPlayer::PrepareForNewRound(){};

void RandomPlayer::PrepareForNewRound() { std::srand(std::time(NULL)); };

void SmartPlayer::PrepareForNewRound() { std::srand(std::time(NULL)); };

void RealPlayer::MakeTurn(GameField &own_field, GameField &enemy_field) {
  Coordinates coords;
  char prev_title;
  int x = 4, y = 4;
  coords.SetAbsCoordinates(x, y);
  char input = 0;
  bool was_miss = false, was_hit = false;
  prev_title = own_field.GetSymbol(coords, true);
  own_field.PlaceSymbol(coords, '+', true);

  own_field.PrintBothBorder();
  while (true) {
    input = dynIn::Input();
    if (input == 'w') {
      if (y > 0) {
        own_field.PlaceSymbol(coords, prev_title, true);
        y--;
        coords.SetAbsCoordinates(x, y);
        prev_title = own_field.GetSymbol(coords, true);
        own_field.PlaceSymbol(coords, '+', true);
        own_field.PrintBothBorder();
      }
    }
    if (input == 's') {
      if (y < 9) {
        own_field.PlaceSymbol(coords, prev_title, true);
        y++;
        coords.SetAbsCoordinates(x, y);
        prev_title = own_field.GetSymbol(coords, true);
        own_field.PlaceSymbol(coords, '+', true);
        own_field.PrintBothBorder();
      }
    }
    if (input == 'a') {
      if (x > 0) {
        own_field.PlaceSymbol(coords, prev_title, true);
        x--;
        coords.SetAbsCoordinates(x, y);
        prev_title = own_field.GetSymbol(coords, true);
        own_field.PlaceSymbol(coords, '+', true);
        own_field.PrintBothBorder();
      }
    }
    if (input == 'd') {
      if (x < 9) {
        own_field.PlaceSymbol(coords, prev_title, true);
        x++;
        coords.SetAbsCoordinates(x, y);
        prev_title = own_field.GetSymbol(coords, true);
        own_field.PlaceSymbol(coords, '+', true);
        own_field.PrintBothBorder();
      }
    }
    if (input == ' ') {
      // if (prev_title != 'O' && prev_title != 'X') {
      successful_shot_ = own_field.Shoot(coords, own_field, enemy_field);
      own_field.PrintBothBorder();
      break;
      // }
    }
  }
}

void RandomPlayer::MakeTurn(GameField &own_field, GameField &enemy_field) {
  bool was_shoot = false;
  int counter = 0;
  int title, x, y;
  Coordinates coords;
  title = rand() % 100;
  x = title % 10;
  y = static_cast<int>(title / 10);
  coords.SetAbsCoordinates(x, y);
  while (!was_shoot) {
    title = own_field.GetSymbol(coords, true);
    if (title == ' ') {
      successful_shot_ = own_field.Shoot(coords, own_field, enemy_field);
      break;
    }
    if (!was_shoot) {
      x++;
      if (x == 10) {
        y++;
        x = 0;
      }
      if (y == 10) {
        y = 0;
      }
    }
    coords.SetAbsCoordinates(x, y);
    counter++;
  }
}

void SmartPlayer::MakeTurn(GameField &own_field, GameField &enemy_field) {}

void RealPlayer::PlaceShip(Ship &ship, GameField &field) {
  Coordinates coords;
  int x = 4, y = 4;
  coords.SetAbsCoordinates(x, y);
  field.PutShip(ship, coords, true);
  char input = 0;
  field.PrintFieldPlacingStage();
  while (true) {
    input = dynIn::Input();
    if (input == 'w') {
      if (y > 0) {
        field.RemoveShip(ship, coords, true);
        y--;
        coords.SetAbsCoordinates(x, y);
        field.PutShip(ship, coords, true);
        field.PrintFieldPlacingStage();
      }
    }
    if (input == 's') {
      if (y < 9) {
        field.RemoveShip(ship, coords, true);
        y++;
        coords.SetAbsCoordinates(x, y);
        field.PutShip(ship, coords, true);
        field.PrintFieldPlacingStage();
      }
    }
    if (input == 'a') {
      if (x > 0) {
        field.RemoveShip(ship, coords, true);
        x--;
        coords.SetAbsCoordinates(x, y);
        field.PutShip(ship, coords, true);
        field.PrintFieldPlacingStage();
      }
    }
    if (input == 'd') {
      if (x < 9 - ship.GetSize() + 1) {
        field.RemoveShip(ship, coords, true);
        x++;
        coords.SetAbsCoordinates(x, y);
        field.PutShip(ship, coords, true);
        field.PrintFieldPlacingStage();
      }
    }
    if (input == ' ') {
      bool was_put = field.TryToPutShip(ship, coords);
      if (was_put) {
        break;
      }
    }
  }
  field.CleanShootField();
}

void RandomPlayer::PlaceShip(Ship &ship, GameField &field) {
  bool was_placed = false;
  int counter = 0;
  int title, x, y;
  Coordinates coords;
  title = rand() % 100;
  x = title % 10;
  y = static_cast<int>(title / 10);
  coords.SetAbsCoordinates(x, y);
  for (int i = rand() % 4; i > 0; i--) {
    ship.RotateClockwise();
  }

  while (!was_placed) {
    if (counter == 101) {
      counter = 0;
      ship.RotateClockwise();
    }
    was_placed = field.TryToPutShip(ship, coords);
    if (!was_placed) {
      x++;
      if (x == 10) {
        y++;
        x = 0;
      }
      if (y == 10) {
        y = 0;
      }
    }
    coords.SetAbsCoordinates(x, y);
    counter++;
  }
}

void SmartPlayer::PlaceShip(Ship &ship, GameField &field) {}

bool RealPlayer::IsSuccessfulShot() { return successful_shot_; }

bool RandomPlayer::IsSuccessfulShot() { return successful_shot_; }

bool SmartPlayer::IsSuccessfulShot() { return successful_shot_; }
