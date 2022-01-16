#include "player.h"

Player &PlayerFactory::CreatePlayer(PlayerType type) {
  if (type == PLAYER) {
    return *(new RealPlayer{});
  }
  if (type == SMART) {
    return *(new SmartPlayer{});
  }
  return *(new RandomPlayer{});
}

RealPlayer::RealPlayer() { successful_shot_ = false; }

RealPlayer::~RealPlayer() {}

void RealPlayer::PrepareForNewRound(){};

bool RealPlayer::IsSuccessfulShot() { return successful_shot_; }

void RealPlayer::MakeTurn(GameField &own_field, GameField &enemy_field) {
  Coordinates coords;
  char prev_title;
  int x = 4, y = 4;
  coords.SetAbsCoordinates(x, y);
  char input = 0;
  bool was_miss = false, was_hit = false;
  prev_title = own_field.GetSymbol(coords, true);
  own_field.PlaceSymbol(coords, '+', true);
  system("clear");
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
        system("clear");
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
        system("clear");
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
        system("clear");
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
        system("clear");
        own_field.PrintBothBorder();
      }
    }
    if (input == ' ') {
      if (prev_title != 'O' && prev_title != 'X') {
        successful_shot_ = own_field.Shoot(coords, own_field, enemy_field);
        system("clear");
        own_field.PrintBothBorder();
        break;
      }
    }
  }
}

void RealPlayer::PlaceShip(Ship &ship, GameField &field) {
  Coordinates coords;
  int x = 4, y = 4;
  coords.SetAbsCoordinates(x, y);
  field.TryToPutShip(ship, coords, true);
  char input = 0;
  system("clear");
  field.PrintFieldPlacingStage();
  while (true) {
    input = dynIn::Input();
    if (input == 'w') {
      if (y > 0) {
        field.RemoveShip(ship, coords, true);
        y--;
        coords.SetAbsCoordinates(x, y);

        if (!field.TryToPutShip(ship, coords, true)) {
          y++;
          coords.SetAbsCoordinates(x, y);
          field.TryToPutShip(ship, coords, true);
        }
        system("clear");
        field.PrintFieldPlacingStage();
      }
    }
    if (input == 's') {
      if (y < 9) {
        field.RemoveShip(ship, coords, true);
        y++;
        coords.SetAbsCoordinates(x, y);
        if (!field.TryToPutShip(ship, coords, true)) {
          y--;
          coords.SetAbsCoordinates(x, y);
          field.TryToPutShip(ship, coords, true);
        }
        system("clear");
        field.PrintFieldPlacingStage();
      }
    }
    if (input == 'a') {
      if (x > 0) {
        field.RemoveShip(ship, coords, true);
        x--;
        coords.SetAbsCoordinates(x, y);
        if (!field.TryToPutShip(ship, coords, true)) {
          x++;
          coords.SetAbsCoordinates(x, y);
          field.TryToPutShip(ship, coords, true);
        }
        system("clear");
        field.PrintFieldPlacingStage();
      }
    }
    if (input == 'd') {
      if (x < 9) {
        field.RemoveShip(ship, coords, true);
        x++;
        coords.SetAbsCoordinates(x, y);
        if (!field.TryToPutShip(ship, coords, true)) {
          x--;
          coords.SetAbsCoordinates(x, y);
          field.TryToPutShip(ship, coords, true);
        }
        system("clear");
        field.PrintFieldPlacingStage();
      }
    }
    if (input == 'e') {
      field.RemoveShip(ship, coords, true);
      ship.RotateClockwise();
      bool valid_rotation = field.TryToPutShip(ship, coords, true);
      if (!valid_rotation) {
        ship.RotateCounterClockwise();
        field.PutShip(ship, coords, true);
      }
      system("clear");
      field.PrintFieldPlacingStage();
      std::cout << "Angle" << ship.GetAngle() << std::endl;
    }
    if (input == 'q') {
      field.RemoveShip(ship, coords, true);
      ship.RotateCounterClockwise();
      bool valid_rotation = field.TryToPutShip(ship, coords, true);
      if (!valid_rotation) {
        ship.RotateClockwise();
        field.PutShip(ship, coords, true);
      }
      system("clear");
      field.PrintFieldPlacingStage();
      std::cout << "Angle" << ship.GetAngle() << std::endl;
    }
    if (input == ' ') {
      field.RemoveShip(ship, coords, true);
      bool was_put = field.TryToPutShip(ship, coords, false);
      if (was_put) {
        break;
      } else {
        field.TryToPutShip(ship, coords, true);
      }
    }
  }
  field.CleanShootField();
}

SmartPlayer::SmartPlayer() { PrepareForNewRound(); }

SmartPlayer::~SmartPlayer() {}

void SmartPlayer::PrepareForNewRound() {
  std::srand(std::time(NULL));
  successful_shot_ = false;
  finding_state_ = false;
  default_way_ended_ = false;
  one_size_was_checked = false;
  count_enemy_boats_ = 4;
  count_enemy_destroyers_ = 3;
  count_enemy_cruisers_ = 2;
  count_enemy_battleships_ = 1;
  first_ship_hit_ = -1;
  cur_shot_ = 3;
  next_shot_ = 3;
  prev_shot_ = 3;
  next_default_title = 3;
  found_axis_ = NONE;
  side_to_check_ = NONE;
  streak_ = 0;
}

bool SmartPlayer::IsSuccessfulShot() { return successful_shot_; }

void SmartPlayer::PlaceShip(Ship &ship, GameField &field) {
  if (ship.GetSize() == Ship::BATTLESHIP) {
    buf_coords.SetAbsCoordinates(0, 9);
    field.PutShip(ship, buf_coords, false);
  }
  if (ship.GetSize() == Ship::CRUISER) {
    buf_coords.SetAbsCoordinates(5, 9);
    if (!field.TryToPutShip(ship, buf_coords, false)) {
      buf_coords.SetAbsCoordinates(3, 0);
      field.PutShip(ship, buf_coords, false);
    }
  }
  if (ship.GetSize() == Ship::DESTROYER) {
    buf_coords.SetAbsCoordinates(0, 0);
    if (!field.TryToPutShip(ship, buf_coords, false)) {
      buf_coords.SetAbsCoordinates(7, 0);
      if (!field.TryToPutShip(ship, buf_coords, false)) {
        ship.RotateCounterClockwise();
        buf_coords.SetAbsCoordinates(0, 3);
        field.PutShip(ship, buf_coords, false);
      }
    }
  }
  if (ship.GetSize() == Ship::TORPEDO_BOAT) {
    bool was_placed = false;
    buf_coords.SetByTitle(rand() % 100);
    while (!was_placed) {
      was_placed = field.TryToPutShip(ship, buf_coords, false);
      if (!was_placed) {
        buf_coords.SetByTitle(rand() % 100);
      }
    }
  }
}

void SmartPlayer::MakeTurn(GameField &own_field, GameField &enemy_field) {
  buf_coords.SetByTitle(next_shot_);
  successful_shot_ = own_field.Shoot(buf_coords, own_field, enemy_field);
  cur_shot_ = next_shot_;

  if (successful_shot_ || finding_state_) {
    GoToFindingMode(own_field);
    if (!finding_state_) {
      UpdateShipsCount();
      found_axis_ = NONE;
      side_to_check_ = NONE;
      one_size_was_checked = false;
      streak_ = 0;
    }
  }
  if (!default_way_ended_ && !finding_state_) {
    next_default_title = GetNextDefaultTitle();
    buf_coords.SetByTitle(next_default_title);
    next_shot_ = next_default_title;
    while (UselessShot(buf_coords, own_field)) {
      if (default_way_ended_) {
        next_shot_ = GetFreeTitleForRadomShot(own_field);
        break;
      }
      next_default_title = GetNextDefaultTitle();
      buf_coords.SetByTitle(next_default_title);
      next_shot_ = next_default_title;
    }
  } else if (!finding_state_) {
    next_shot_ = GetFreeTitleForRadomShot(own_field);
  }

  prev_shot_ = cur_shot_;
  // SelectNewTitleAndUpdateData();
}

void SmartPlayer::GoToFindingMode(GameField &own_field) {
  if (successful_shot_) {
    if (!finding_state_) {
      finding_state_ = true;
      first_ship_hit_ = cur_shot_;
    }
    streak_++;
    CheckShipExistenceAndUpdateFindingState();
  }
  if (finding_state_) {
    if (successful_shot_) {
      if (found_axis_ == NONE && side_to_check_ == NONE) {
        side_to_check_ = GetNextValidSide();
        next_shot_ = GetNextTitleByDirection(side_to_check_, cur_shot_);
        buf_coords.SetByTitle(next_shot_);
        while (side_to_check_ != NONE &&
               !own_field.IsShootingTitleFree(buf_coords)) {
          side_to_check_ = GetNextValidSide();
          next_shot_ = GetNextTitleByDirection(side_to_check_, cur_shot_);
          buf_coords.SetByTitle(next_shot_);
        }
        if (side_to_check_ == NONE) {
          finding_state_ = false;
        }

      } else {  // found_axis != NONE OR side_to_check != NONE
        found_axis_ = side_to_check_;
        next_shot_ = GetNextTitleByDirection(found_axis_, cur_shot_);
        buf_coords.SetByTitle(next_shot_);
        if ((!IsValidNextTitle(next_shot_) ||
             !own_field.IsShootingTitleFree(buf_coords)) &&
            one_size_was_checked) {
          finding_state_ = false;
        } else if (!IsValidNextTitle(next_shot_) ||
                   !own_field.IsShootingTitleFree(buf_coords)) {
          one_size_was_checked = true;
          cur_shot_ = first_ship_hit_;
          side_to_check_ = GetOppositeDirection(found_axis_);
          found_axis_ = side_to_check_;
          next_shot_ = GetNextTitleByDirection(found_axis_, cur_shot_);
          buf_coords.SetByTitle(next_shot_);
          if (!IsValidNextTitle(next_shot_) ||
              !own_field.IsShootingTitleFree(buf_coords)) {
            finding_state_ = false;
          }
        }
      }
    } else {  // !successful_shot_
      if (found_axis_ == NONE) {
        cur_shot_ = prev_shot_;
        side_to_check_ = GetNextValidSide();
        if (side_to_check_ == NONE) {
          finding_state_ = false;
          return;
        }
        next_shot_ = GetNextTitleByDirection(side_to_check_, cur_shot_);
      } else if (!one_size_was_checked) {
        one_size_was_checked = true;
        cur_shot_ = first_ship_hit_;
        side_to_check_ = GetOppositeDirection(found_axis_);
        found_axis_ = side_to_check_;
        next_shot_ = GetNextTitleByDirection(found_axis_, cur_shot_);
        if (!IsValidNextTitle(next_shot_)) {
          finding_state_ = false;
        }
      } else {
        finding_state_ = false;
      }
    }
  }
}

SmartPlayer::Direction SmartPlayer::GetOppositeDirection(Direction direction) {
  switch (direction) {
    case TOP:
      return BOT;
    case BOT:
      return TOP;
    case RIGHT:
      return LEFT;
    case LEFT:
      return RIGHT;

    default:
      return NONE;
  }
}

void SmartPlayer::UpdateShipsCount() {
  switch (streak_) {
    case Ship::TORPEDO_BOAT:
      count_enemy_boats_--;
      break;
    case Ship::CRUISER:
      count_enemy_cruisers_--;
      break;
    case Ship::DESTROYER:
      count_enemy_destroyers_--;
      break;

    default:
      count_enemy_battleships_--;
      break;
  }
}

int SmartPlayer::GetFreeTitleForRadomShot(GameField &own_field) {
  int title;
  int counter = 0;
  title = rand() % 100;
  buf_coords.SetByTitle(title);
  while (UselessShot(buf_coords, own_field)) {
    counter++;
    title = (title + 1) % 100;
    buf_coords.SetByTitle(title);
    if (counter == 102) {
      break;
    }
  }
  return title;
}

int SmartPlayer::GetNextDefaultTitle() {
  switch (next_default_title) {
    case 30:
      return 7;
    case 70:
      return 29;

    case 92:
      return 69;
    case 96:
      return 1;
    case 10:
      return 5;
    case 50:
      return 9;
    case 90:
      return 49;
    case 94:
      return 89;
    case 98:
      default_way_ended_ = true;
      return 0;

    default:
      buf_coords.SetByTitle(next_default_title);
      int x = buf_coords.GetX();
      int y = buf_coords.GetY();
      x--;
      y++;
      buf_coords.SetAbsCoordinates(x, y);
      return buf_coords.GetTitleByCoords();
  }
}

bool SmartPlayer::IsValidNextTitle(int new_title) {
  Coordinates old_coords, new_coords;
  if (new_title < 0 || new_title > 99) {
    return false;
  }
  old_coords.SetByTitle(cur_shot_);
  new_coords.SetByTitle(new_title);
  if ((old_coords.GetX() != new_coords.GetX()) &&
      (old_coords.GetY() != new_coords.GetY())) {
    return false;
  }
  return true;
}

bool SmartPlayer::UselessShot(Coordinates coords, GameField &own_field) {
  if (own_field.IsShootingTitleFree(coords) &&
      own_field.NoSymbolsAroundInShootingField(coords, 'X')) {
    return false;
  }
  return true;
}

int SmartPlayer::GetNextTitleByDirection(Direction direction, int title) {
  int result = title;
  switch (direction) {
    case TOP:
      result -= 10;
      break;
    case BOT:
      result += 10;
      break;
    case RIGHT:
      result += 1;
      break;
    case LEFT:
      result -= 1;
      break;

    default:
      break;
  }
  return result;
}

SmartPlayer::Direction SmartPlayer::GetNextValidSide() {
  int hypothetical_shoot;
  Direction hypothetical_direction = side_to_check_;
  for (bool is_correct_side = false; !is_correct_side;) {
    hypothetical_direction = GetNextDirection(hypothetical_direction);
    hypothetical_shoot = cur_shot_;
    hypothetical_shoot =
        GetNextTitleByDirection(hypothetical_direction, hypothetical_shoot);
    is_correct_side = IsValidNextTitle(hypothetical_shoot);
  }
  return hypothetical_direction;
}

SmartPlayer::Direction SmartPlayer::GetNextDirection(Direction direction) {
  return static_cast<Direction>((direction + 1) % 5);
}

void SmartPlayer::CheckShipExistenceAndUpdateFindingState() {
  switch (streak_) {
    case 1:
      if (count_enemy_battleships_ | count_enemy_cruisers_ |
          count_enemy_destroyers_) {
        finding_state_ = true;
      } else {
        finding_state_ = false;
      }
      break;
    case 2:
      if (count_enemy_battleships_ | count_enemy_cruisers_) {
        finding_state_ = true;
      } else {
        finding_state_ = false;
      }
      break;
    case 3:
      if (count_enemy_battleships_) {
        finding_state_ = true;
      } else {
        finding_state_ = false;
      }
      break;

    default:
      finding_state_ = false;
      break;
  }
}

RandomPlayer::RandomPlayer() {
  successful_shot_ = false;
  std::srand(std::time(NULL));
}
RandomPlayer::~RandomPlayer() {}

void RandomPlayer::PrepareForNewRound() { std::srand(std::time(NULL)); };

void RandomPlayer::MakeTurn(GameField &own_field, GameField &enemy_field) {
  bool was_shoot = false;
  int title;
  Coordinates coords;
  title = rand() % 100;
  coords.SetByTitle(title);
  while (!was_shoot) {
    if (own_field.IsShootingTitleFree(coords)) {
      successful_shot_ = own_field.Shoot(coords, own_field, enemy_field);
      break;
    }
    if (!was_shoot) {
      title = (title + 1) % 100;
    }
    coords.SetByTitle(title);
  }
}

void RandomPlayer::PlaceShip(Ship &ship, GameField &field) {
  bool was_placed = false;
  int counter = 0;
  int title;
  Coordinates coords;
  title = rand() % 100;
  coords.SetByTitle(title);
  for (int i = rand() % 4; i > 0; i--) {
    ship.RotateClockwise();
  }

  while (!was_placed) {
    if (counter == 101) {
      counter = 0;
      ship.RotateClockwise();
    }
    was_placed = field.TryToPutShip(ship, coords, false);
    if (!was_placed) {
      title = (title + 1) % 100;
    }
    coords.SetByTitle(title);
    counter++;
  }
}

bool RandomPlayer::IsSuccessfulShot() { return successful_shot_; }
