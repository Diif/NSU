#include "config_handler.h"

#include "exceptions.h"
#include "workers.h"

ConfigHandler::ConfigHandler() {}

ConfigHandler::ConfigHandler(std::string file_name) {
  config_file_.open(file_name);
  if (!config_file_.good()) {
    throw std::invalid_argument("Can't open config file");
  }
}

ConfigHandler::~ConfigHandler() { config_file_.close(); }

void ConfigHandler::ProcessConfigFile() { ProcessBlocks(); }

void ConfigHandler::ProcessBlocks() {
  int line_number = 1;
  std::string line;
  std::regex re("\\s");
  std::vector<Worker*> blocks;

  std::getline(config_file_, line, '\n');
  BlockLineSyntaxCheck(line, line_number);
  if (!std::regex_match(line, std::regex("^\\s*desc\\s*$"))) {
    throw(BlockBeginningException());
  }

  for (; std::getline(config_file_, line, '\n'); line_number++) {
    BlockLineSyntaxCheck(line, line_number);
    std::sregex_token_iterator iter(line.begin(), line.end(), re, -1);
  }
}

Worker* ConfigHandler::CreateWorker(std::string line) {
  std::regex re("\\s+");
  std::sregex_token_iterator iter(line.begin(), line.end(), re, -1);
  std::sregex_token_iterator end;
  iter++;
  iter++;  // skip ID and =
  std::string worker_name = (*iter);
  std::string args;

  for (; iter != end; iter++) {
    args += (*iter);
  }

  if (worker_name == "readfile") {
    return
  }
  if (worker_name == "writefile") {
    return
  }
  if (worker_name == "grep") {
    return
  }
  if (worker_name == "sort") {
    return
  }
  if (worker_name == "replace") {
    return
  }
  if (worker_name == "dump") {
    return
  }
}

void ConfigHandler::ProcessSequence() {}

void ConfigHandler::BlockLineSyntaxCheck(std::string line, int pos) {
  std::regex re("^(\\s*\\d+\\s+=\\s+\\w+|\\s*desc\\s*|\\s*csed\\s*)");
  if (!std::regex_match(line, re)) {
    throw(BlockSyntaxException(line, pos));
  }
}
