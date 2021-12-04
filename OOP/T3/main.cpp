
#include "option_handler.h"

int main(int argc, char** argv) {
  OptionHandler option_handler(argc, argv);
  GameSession& session = option_handler.CreateGameSessionIfPossible();
  std::cout << "R " << session.num_of_rounds_ << "\nP1 " << session.player1_
            << "\nP2 " << session.player2_ << std::endl;
}
