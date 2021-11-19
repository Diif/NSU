#include <iostream>

#include "option_handler.h"

int main(int argc, char** argv) {
  OptionHandler option_handler(argc, argv);
  option_handler.CreateGameSessionIfPossible();
}
