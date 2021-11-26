#ifndef OPTION_SELECTOR_H_
#define OPTION_SELECTOR_H_

#include <iostream>
#include <new>

#include "game_session.h"
#include "optionparser.h"

enum OptionIndex { UNKNOWN, HELP, PLUS };

static const option::Descriptor usage[] = {
    {HELP, 0, "h", "help", option::Arg::None,
     "  --help,   -h \tPrint options and exit."},
    {PLUS, 0, "c", "count", option::Arg::None,
     "  --count,  -c [num] \tSet number of rounds.   \tDefault: 1."},
    {PLUS, 0, "f", "first", option::Arg::None,
     "  --first,  -f [rand|smrt|plr] \tSet type of 1st player. \tDefault: "
     "random."},
    {PLUS, 0, "s", "second", option::Arg::None,
     "  --second, -s [rand|smrt] \tSet type of 2nd player. \tDefault: random."},
    {UNKNOWN, 0, "", "", option::Arg::None,
     "\nExamples:\n"
     "  set_battle.exe -h\n"
     "  see_battle.exe \n"
     "  see_battle.exe -c 2 -f plr -s smart\n"},
    {0, 0, 0, 0, 0, 0}};

class OptionHandler {
 private:
  int num_of_options_;
  option::Stats stats_;
  option::Option *options_, *buffer_;
  option::Parser parse_;
  void CheckParser();
  void ChooseScript();
  GameSession& CreateDefaultGameSession();

 public:
  GameSession& CreateGameSessionIfPossible();
  OptionHandler(int argc, char** argv);
  OptionHandler() = delete;
  ~OptionHandler();
};

#endif  // OPTION_SELECTOR_H_