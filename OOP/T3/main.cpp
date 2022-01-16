
#include "option_handler.h"
//

#include "game_field.h"
//
#include "player.h"

int main(int argc, char** argv) {
  OptionHandler option_handler{argc, argv};
  GameSession& session = option_handler.CreateGameSessionIfPossible();
  session.StartSession();
  session.PrintSessionResult();
  delete &session;
  dynIn::ResetTermios();
}
