
#include "option_handler.h"
//
#include "game_field.h"
//

int main(int argc, char** argv) {
  // OptionHandler option_handler(argc, argv);
  // GameSession& session = option_handler.CreateGameSessionIfPossible();
  GameField field{10};
  Ship ship(3);
  Coordinates coords;
  // int x, y;
  // std::cin >> x >> y;
  int x = 5, y = 5;
  coords.SetAbsCoordinates(x, y);
  field.TryToPutShip(ship, coords);
  field.PrintField();
  field.TryToRemoveShip(ship, coords);
  field.PrintField();
}
