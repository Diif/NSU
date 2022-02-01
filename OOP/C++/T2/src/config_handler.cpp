#include "config_handler.h"

ConfigHandler::ConfigHandler() {}

ConfigHandler::ConfigHandler(std::string file_name) { Open(file_name); }

ConfigHandler::~ConfigHandler() { Close(); }

void ConfigHandler::Open(std::string file_name) {
  config_file_.open(file_name);
  if (!config_file_.good()) {
    throw std::invalid_argument("Can't open config file");
  }
}

inline void ConfigHandler::Close() { config_file_.close(); }

WorkflowExecutor& ConfigHandler::ProcessConfigFile() {
  WorkflowExecutor& workflow_executor = *new WorkflowExecutor;

  ProcessBlocks(workflow_executor);
  ProcessSequence(workflow_executor);
  return workflow_executor;
}

void ConfigHandler::ProcessBlocks(WorkflowExecutor& workflow_executor) {
  int line_number = 1;
  std::string line;
  std::vector<std::string> words;
  std::regex re{"\\s+"};

  std::getline(config_file_, line, '\n');
  BlockLineSyntaxCheck(line, line_number);
  if (!std::regex_match(line, std::regex("^\\s*desc\\s*$"))) {
    throw(BlockBeginningException());
  }

  for (; std::getline(config_file_, line, '\n'); line_number++) {
    int id;
    BlockLineSyntaxCheck(line, line_number);
    words = Parse(line, re);
    std::vector<std::string>::iterator iter = words.begin();
    std::vector<std::string>::iterator end = words.end();

    if (iter != end && *iter == "csed") {
      break;
    }

    if (config_file_.eof()) {
      throw(BlockEndException());
    }
    id = std::stoi(words[0]);
    if (!workflow_executor.IsIdFree(id)) {
      throw(BlockSyntaxException(line, line_number));
    }
    words.erase(words.begin());  // erase ID
    words.erase(words.begin());  // erase =
    Worker* worker = CreateWorker(words);
    workflow_executor.PutWorker(id, worker);
  }
}

void ConfigHandler::ProcessSequence(WorkflowExecutor& workflow_executor) {
  std::string line;
  std::getline(config_file_, line, '\n');
  std::vector<std::string> sequence = Parse(line);
  std::vector<std::string>::iterator iter = sequence.begin();
  std::vector<std::string>::iterator end = sequence.end();
  while (iter != end) {
    if ((*iter) == "->") {
      iter++;
      continue;
    }
    workflow_executor.PushOperation(  // TODO catch 1fa -> 3 -> 5 -> 2
        std::stoi(*iter));            //  throws exception if it is not int
    iter++;
  }
}

Worker* ConfigHandler::CreateWorker(std::vector<std::string>& args) {
  std::string worker_class = args[0];
  int old_size = args.size();

  if (worker_class == "readfile") {
    args.erase(args.begin());  //  erase worker_class
    return read_factory_.CreateWorker(args);
  }
  if (worker_class == "writefile") {
    args.erase(args.begin());  //  erase worker_class
    return write_factory_.CreateWorker(args);
  }
  if (worker_class == "grep") {
    args.erase(args.begin());  //  erase worker_class
    return grep_factory_.CreateWorker(args);
  }
  if (worker_class == "sort") {
    args.erase(args.begin());  //  erase worker_class
    return sort_factory_.CreateWorker(args);
  }
  if (worker_class == "replace") {
    args.erase(args.begin());  //  erase worker_class
    return replace_factory_.CreateWorker(args);
  }
  if (worker_class == "dump") {
    args.erase(args.begin());  //  erase worker_class
    return dump_factory_.CreateWorker(args);
  }
  if (old_size == args.size()) {
    throw(BlockInvalidWorkerNameException(args[0]));
  } else {
    args.insert(args.begin(),
                worker_class);  //  return worker_class to old place in vector
  }
  return nullptr;
}

void ConfigHandler::BlockLineSyntaxCheck(std::string line, int pos) {
  std::regex re(
      "(^(\\s*\\d+\\s+=\\s+(\\S+\\s*)+)$|^(\\s*desc\\s*)$|^(\\s*csed\\s*)$)");
  if (!std::regex_match(line, re)) {
    throw(BlockSyntaxException(line, pos));
  }
}

std::vector<std::string> ConfigHandler::Parse(std::string line, std::regex re) {
  std::vector<std::string> str_vec;
  std::sregex_token_iterator iter(line.begin(), line.end(), re, -1);
  std::sregex_token_iterator end;
  while (iter != end) {
    str_vec.push_back(*iter);
    iter++;
  }
  return str_vec;
}

std::vector<std::string> ConfigHandler::Parse(std::string line) {
  std::regex re("\\s+");
  std::vector<std::string> str_vec;
  std::sregex_token_iterator iter(line.begin(), line.end(), re, -1);
  std::sregex_token_iterator end;
  while (iter != end) {
    str_vec.push_back(*iter);
    iter++;
  }
  return str_vec;
}
