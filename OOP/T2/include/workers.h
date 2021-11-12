#ifndef WORKERS_H_
#define WORKERS_H_

#include <algorithm>
#include <fstream>
#include <regex>
#include <string>
#include <vector>

#include "exceptions.h"
class Worker {
 protected:
  int count_of_in_args;
  int count_of_out_args;
  bool IsEmptyInputText(std::vector<std::string>& in_text_in_lines);

 public:
  virtual void Run(std::vector<std::string>& in_text_in_lines) = 0;
};

class ReadWorker : public Worker {
 private:
  std::string file_name_;

 public:
  ReadWorker(std::vector<std::string>& args);
  void Run(std::vector<std::string>& in_text_in_lines) override;
};

class WriteWorker : public Worker {
 private:
  std::string file_name_;

 public:
  WriteWorker(std::vector<std::string>& args);
  void Run(std::vector<std::string>& in_text_in_lines) override;
};

class GrepWorker : public Worker {
 private:
  std::string word_;

 public:
  GrepWorker(std::vector<std::string>& args);
  void Run(std::vector<std::string>& in_text_in_lines) override;
};

class SortWorker : public Worker {
 public:
  SortWorker(std::vector<std::string>& args);
  void Run(std::vector<std::string>& in_text_in_lines) override;
};

class ReplaceWorker : public Worker {
 private:
  std::string word_to_replace_;
  std::string word_to_place_;

 public:
  ReplaceWorker(std::vector<std::string>& args);
  void Run(std::vector<std::string>& in_text_in_lines) override;
};

class DumpWorker : public Worker {
 private:
  std::string file_name_;

 public:
  DumpWorker(std::vector<std::string>& args);
  void Run(std::vector<std::string>& in_text_in_lines) override;
};
#endif  //  WORKERS_H_