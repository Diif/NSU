
#include "option_handler.h"
//

#include "game_field.h"
//
#include "player.h"

int main(int argc, char** argv) {
  argc = 7;
  argv = (char**)malloc(sizeof(char*) * 7);
  char f1[] = "-c";
  char f1a[] = "10";
  char f2[] = "-f";
  char f2a[] = "smrt";
  char f3[] = "-s";
  char f3a[] = "smrt";
  argv[1] = f1;
  argv[2] = f1a;
  argv[3] = f2;
  argv[4] = f2a;
  argv[5] = f3;
  argv[6] = f3a;
  OptionHandler option_handler{argc, argv};
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
