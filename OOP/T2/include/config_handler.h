#ifndef CONFIG_HANDLER_H_
#define CONFIG_HANDLER_H_

#include <fstream>
#include <iostream>
#include <regex>

#include "exceptions.h"
#include "factories.h"
#include "workers.h"
#include "workflow_executor.h"

class ConfigHandler {
 private:
  std::ifstream config_file_;
  ReadFactory read_factory_;
  WriteFactory write_factory_;
  GrepFactory grep_factory_;
  SortFactory sort_factory_;
  ReplaceFactory replace_factory_;
  DumpFactory dump_factory_;
  void ProcessSequence(WorkflowExecutor& workflow_executor);
  void SequenceCheck(WorkflowExecutor& workflow_executor);
  void ProcessBlocks(WorkflowExecutor& workflow_executor);
  void BlockLineSyntaxCheck(std::string line, int pos);
  std::vector<std::string> Parse(std::string line, std::regex re);
  std::vector<std::string> Parse(std::string line);
  Worker* CreateWorker(std::vector<std::string>& args);

 public:
  ConfigHandler();
  ConfigHandler(std::string file_name);
  ~ConfigHandler();
  void Open(std::string file_name);
  void Close();
  WorkflowExecutor& ProcessConfigFile();
};

#endif  //  CONFIG_HANDLER_H_
