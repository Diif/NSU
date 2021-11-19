#include "option_handler.h"

OptionHandler::OptionHandler(int argc, char** argv)
    : stats_(usage, argc, argv), num_of_options_{argc} {
  argc -= (argc > 0);
  argv += (argc > 0);  // skip program name argv[0] if present
  options_ = new option::Option[stats_.options_max];
  buffer_ = new option::Option[stats_.buffer_max];

  new (&parse_) option::Parser(usage, argc, argv, options_, buffer_);
}

OptionHandler::~OptionHandler() {
  delete[] options_;
  delete[] buffer_;
}

void OptionHandler::CheckParser() {
  if (parse_.error()) {
    throw(std::runtime_error("Unexpected parser error occurred!"));
  }
}

void OptionHandler::ChooseScript() {
  if (options_[UNKNOWN]) {
    std::cout << "\t Can't recognize command. Try sea_battle.exe --help"
              << std::endl;
    exit(EXIT_SUCCESS);
  } else if (options_[HELP]) {
    option::printUsage(std::cout, usage);
    exit(EXIT_SUCCESS);
  }
  if (num_of_options_ == 0) {
  }
}

GameSession& OptionHandler::CreateGameSessionIfPossible() {
  CheckParser();
  ChooseScript();
}