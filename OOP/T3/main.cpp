
#include "option_handler.h"
//

#include "game_field.h"
//
#include "player.h"

int main(int argc, char** argv) {
  OptionHandler option_handler(argc, argv);
  GameSession& session = option_handler.CreateGameSessionIfPossible();
  session.StartSession();
  session.PrintSessionResult();
  delete &session;

  /* GameField field{};

   Ship ship(3);
   RealPlayer p{};
   p.PlaceShip(ship, field);
   ship.ChangeShip(Ship::BATTLESHIP);
   p.PlaceShip(ship, field);*/
  dynIn::ResetTermios();
}
