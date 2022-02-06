#ifndef CONFIG_HANDLER_H_
#define CONFIG_HANDLER_H_
#include <fstream>
#include <list>
#include <regex>
#include <string>

#include "Workflow.h"
#include "exceptions.h"

using namespace std;

class Config_handler {
 private:
  ifstream file_;

  void put_workers(Workflow* workflow) {
    string str;
    list<string> list_of_arguments;
    int index;
    getline(file_, str, '\n');
    if (str != "desc") {
      throw(no_desc_csed());
    }

    getline(file_, str, '\n');
    while (str != "csed") {
      regex reg("\\d+ = \\S+( \\S+)*");
      if (!regex_match(str, reg)) {
        throw(error_str());
      }

      regex re("\\s+");
      sregex_token_iterator iter(str.begin(), str.end(), re, -1);
      sregex_token_iterator end();
      index = stoi(*iter);
      iter++;
      while (iter != end()) {
        list_of_arguments.push_back(*iter);
        iter++;
      }
      getline(file_, str, '\n');
    }
  }

  void put_order_operations(Workflow* workflow) {}

 public:
  Config_handler(string file_name) {
    file_.open(file_name);
    if (file_.fail() == true) {
      throw(bad_file());
    }
  }

  Workflow& read_file() {
    Workflow* workflow = new Workflow{};
    put_workers(workflow);
    put_order_operations(workflow);
    return *workflow;
  }
};

#endif  // CONFIG_HANDLER_H_