#include "option_handler.h"

option::ArgStatus Arg::Rounds(const option::Option& option, bool msg) {
  if (option.arg != 0 && strtol(option.arg, NULL, 10)) {
    return option::ARG_OK;
  }
  return option::ARG_ILLEGAL;
}
option::ArgStatus Arg::PlayerType(const option::Option& option, bool msg) {
  if (option.arg != 0 &&
      (strcmp(option.arg, "rand") == 0 || strcmp(option.arg, "smrt") == 0 ||
       strcmp(option.arg, "player") == 0)) {
    return option::ARG_OK;
  }
  return option::ARG_ILLEGAL;
}

option::ArgStatus Arg::Unknown(const option::Option& option, bool msg) {
  return option::ARG_ILLEGAL;
}

OptionHandler::OptionHandler(int argc, char** argv) {
  argc -= (argc > 0);
  argv += (argc > 0);  // skip program name argv[0] if present
  stats_ = new option::Stats{usage, argc, argv};
  options_ = new option::Option[stats_->options_max];
  buffer_ = new option::Option[stats_->options_max];
  parse_ = new option::Parser(usage, argc, argv, options_, buffer_);
}

OptionHandler::~OptionHandler() {
  delete[] options_;
  delete[] buffer_;
  delete stats_;
  delete parse_;
}

void OptionHandler::CheckParser() {
  if (parse_->error()) {
    throw(std::runtime_error("Invalid arguments!"));
  }
}

PlayerType OptionHandler::ConvertCharsToPlayerType(const char* arg) {
  if (strcmp(arg, "rand") == 0) {
    return PlayerType::RANDOM;
  }
  if (strcmp(arg, "smrt") == 0) {
    return PlayerType::SMART;
  }
  if (strcmp(arg, "player") == 0) {
    return PlayerType::PLAYER;
  }
  return PlayerType::RANDOM;
}

void OptionHandler::CheckHelpAndUnknownOptions() {
  if (options_[UNKNOWN]) {
    std::cout << "\t Can't recognize command. Try sea_battle.exe --help"
              << std::endl;
    exit(EXIT_SUCCESS);
  } else if (options_[HELP]) {
    option::printUsage(std::cout, usage);
    exit(EXIT_SUCCESS);
  }
}

GameSession& OptionHandler::GenerateSessionByOptions() {
  const int NUM_OF_ROUNDS = usage[1].type;
  const int PLAYER1 = usage[2].type;
  const int PLAYER2 = usage[3].type;
  int num_of_rounds = 1;
  PlayerType player1_type = PlayerType::RANDOM,
             player2_type = PlayerType::RANDOM;
  // if (num_of_options_ == 0) {
  //   return *(new GameSession{});
  // } else {
  auto ptr = &options_[PLUS];
  while (ptr) {
    if (ptr->type() == NUM_OF_ROUNDS) {
      num_of_rounds = strtol(ptr->arg, NULL, 10);
    }
    if (ptr->type() == PLAYER1) {
      player1_type = ConvertCharsToPlayerType(ptr->arg);
    }
    if (ptr->type() == PLAYER2) {
      player2_type = ConvertCharsToPlayerType(ptr->arg);
    }
    ptr = ptr->next();
  }
  return *(new GameSession{num_of_rounds, player1_type, player2_type});
}
// }

GameSession& OptionHandler::CreateGameSessionIfPossible() {
  CheckParser();
  CheckHelpAndUnknownOptions();
  GameSession& session = GenerateSessionByOptions();
  return session;
}
