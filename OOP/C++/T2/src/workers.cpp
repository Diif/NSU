
#include "workers.h"

// base class

bool Worker::IsEmptyInputText(std::vector<std::string> &in_text_in_lines) {
  if (!in_text_in_lines.size()) {
    return true;
  }
  return false;
}

// base class

ReadWorker::ReadWorker(std::vector<std::string> &args) {
  count_of_in_args = 1;
  if (args.size() != count_of_in_args) {
    throw(BlockArgumentsException());
  }
  file_name_ = args[0];
}

WriteWorker::WriteWorker(std::vector<std::string> &args) {
  count_of_in_args = 1;
  if (args.size() != count_of_in_args) {
    throw(BlockArgumentsException());
  }
  file_name_ = args[0];
}

GrepWorker::GrepWorker(std::vector<std::string> &args) {
  count_of_in_args = 1;
  if (args.size() != count_of_in_args) {
    throw(BlockArgumentsException());
  }
  word_ = args[0];
}

SortWorker::SortWorker(std::vector<std::string> &args) {
  count_of_in_args = 0;
  if (args.size() != count_of_in_args) {
    throw(BlockArgumentsException());
  }
}

ReplaceWorker::ReplaceWorker(std::vector<std::string> &args) {
  count_of_in_args = 2;
  if (args.size() != count_of_in_args) {
    throw(BlockArgumentsException());
  }
  word_to_replace_ = args[0];
  word_to_place_ = args[1];
}

DumpWorker::DumpWorker(std::vector<std::string> &args) {
  count_of_in_args = 1;
  if (args.size() != count_of_in_args) {
    throw(BlockArgumentsException());
  }
  file_name_ = args[0];
}

void ReadWorker::Run(std::vector<std::string> &in_text_in_lines) {
  if (!IsEmptyInputText(in_text_in_lines)) {
    throw(SequenceStructureException());
  }
  std::ifstream file;
  file.open(file_name_);
  if (!file.good()) {
    throw(WorkerRunTimeException());
  }
  std::string line;
  while (std::getline(file, line, '\n')) {
    in_text_in_lines.push_back(line);
  }
  file.close();
}

void WriteWorker::Run(std::vector<std::string> &in_text_in_lines) {
  if (IsEmptyInputText(in_text_in_lines)) {
    throw(SequenceStructureException());
  }
  std::ofstream file;
  file.open(file_name_);
  if (!file.good()) {
    throw(WorkerRunTimeException());
  }
  int size = in_text_in_lines.size();
  std::string line;
  for (size_t i = 0; i < size; i++) {
    file << in_text_in_lines[i] << '\n';
  }
  in_text_in_lines.clear();
  file.close();
}

void DumpWorker::Run(std::vector<std::string> &in_text_in_lines) {
  if (IsEmptyInputText(in_text_in_lines)) {
    throw(SequenceStructureException());
  }
  std::ofstream file;
  file.open(file_name_);
  if (!file.good()) {
    throw(WorkerRunTimeException());
  }
  int size = in_text_in_lines.size();
  std::string line;
  for (size_t i = 0; i < size; i++) {
    file << in_text_in_lines[i] << '\n';
  }
  file.close();
}

void SortWorker::Run(std::vector<std::string> &in_text_in_lines) {
  if (IsEmptyInputText(in_text_in_lines)) {
    if (IsEmptyInputText(in_text_in_lines)) {
      throw(SequenceStructureException());
    }
  }
  std::sort(in_text_in_lines.begin(), in_text_in_lines.end());
}

void GrepWorker::Run(std::vector<std::string> &in_text_in_lines) {
  if (IsEmptyInputText(in_text_in_lines)) {
    throw(SequenceStructureException());
  }
  std::regex re(".*" + word_ + ".*");
  auto end = in_text_in_lines.end();
  for (auto iter = in_text_in_lines.begin(); iter != end;) {
    if (!std::regex_match((*iter), re)) {
      in_text_in_lines.erase(iter);
      end = in_text_in_lines.end();
      continue;
    }
    iter++;
  }
  if (IsEmptyInputText(in_text_in_lines)) {
    in_text_in_lines.push_back("");
  }
}

void ReplaceWorker::Run(std::vector<std::string> &in_text_in_lines) {
  if (IsEmptyInputText(in_text_in_lines)) {
    throw(SequenceStructureException());
  }
  std::regex re(word_to_replace_);
  auto end = in_text_in_lines.end();
  for (auto iter = in_text_in_lines.begin(); iter != end; iter++) {
    (*iter) = std::regex_replace((*iter), re, word_to_place_);
  }
}
