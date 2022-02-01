#include <exception>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

#include "config_handler.h"

int main(int argc, char** argv) {
  std::string file_name{"test.txt"};
  if (argc == 2) {
    file_name = argv[1];
  }
  ConfigHandler config_handler(file_name);
  WorkflowExecutor& workflow_executor = config_handler.ProcessConfigFile();
  workflow_executor.Execute();
  return 0;
}
