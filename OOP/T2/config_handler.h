#ifndef CONFIG_HANDLER_H_
#define CONFIG_HANDLER_H_

#include <fstream>
#include <iostream>
#include <regex>

#include "exceptions.h"
#include "workers.h"
class ConfigHandler {
 private:
  std::ifstream config_file_;

 public:
  ConfigHandler();
  ConfigHandler(std::string file_name);
  ~ConfigHandler();
  void ProcessConfigFile();
  void ProcessSequence();
  void ProcessBlocks();
  void BlockLineSyntaxCheck(std::string line, int pos);
  Worker* CreateWorker(std::string line);
};

#endif  //  CONFIG_HANDLER_H_
