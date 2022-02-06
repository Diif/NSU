#include <fstream>
#include <iostream>
#include <string>

#include "Workflow.h"
#include "config_handler.h"

using namespace std;

int main(int argc, char** argv) {
  string file_name;
  if (argc == 2) {
    file_name = argv[1];
  }

  Config_handler config_handler(file_name);
  Workflow& workflow = config_handler.read_file();
  workflow.work();
}
