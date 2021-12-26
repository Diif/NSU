#ifndef OPTION_SELECTOR_H_
#define OPTION_SELECTOR_H_

#include <string.h>

#include <iostream>
#include <new>

#include "game_session.h"
#include "optionparser.h"

enum OptionIndex { UNKNOWN, HELP, PLUS };

struct Arg : public option::Arg {
  static option::ArgStatus Rounds(const option::Option& option, bool msg);
  static option::ArgStatus PlayerType(const option::Option& option, bool msg);
};

static const option::Descriptor usage[] = {
    {HELP, 0, "h", "help", Arg::None,
     "  --help,   -h \tPrint options and exit."},
    {PLUS, 1, "c", "count", Arg::Rounds,
     "  --count,  -c [num] \tSet number of rounds.   \tDefault: 1."},
    {PLUS, 2, "f", "first", Arg::PlayerType,
     "  --first,  -f [rand|smrt|player] \tSet type of 1st player. \tDefault: "
     "random."},
    {PLUS, 3, "s", "second", Arg::PlayerType,
     "  --second, -s [rand|smrt] \tSet type of 2nd player. \tDefault: "
     "random."},
    {UNKNOWN, 0, "", "", option::Arg::None,
     "\nExamples:\n"
     "  set_battle.exe -h\n"
     "  see_battle.exe \n"
     "  see_battle.exe -c 2 -f player -s smrt\n"},
    {0, 0, 0, 0, 0, 0}};

class OptionHandler {
 private:
  int num_of_options_;
  option::Stats stats_;
  option::Option *options_, *buffer_;
  option::Parser parse_;

  void CheckParser();
  void CheckHelpAndUnknownOptions();
  PlayerType ConvertCharsToPlayerType(const char* arg);
  GameSession& GenerateSessionByOptions();
  GameSession& CreateDefaultGameSession();

 public:
  GameSession& CreateGameSessionIfPossible();
  OptionHandler(int argc, char** argv);
  OptionHandler() = delete;
  ~OptionHandler();
};

#endif  // OPTION_SELECTOR_H_