#ifndef OOP_T0_0B_INCLUDE_SOLUTION_H_
#define OOP_T0_0B_INCLUDE_SOLUTION_H_
#include <fstream>
#include <map>
#include <sstream>
#include <string>

// DELETE
#include <iostream>

class WordReader {
 private:
  std::string cur_word_;
  std::string cur_line;
  std::ifstream file_;
  std::stringstream line_stream_;
  int total_words_;
  bool line_eof_reached_;
  bool file_eof_reached_;

 public:
  WordReader();
  ~WordReader();
  void OpenFile(std::string str);
  std::string GetCurrentWord();
  std::ifstream* GetFilePointer();
  void ReadLine();
  void ReadWord();
  void IncreaseTotalWordsCount();
  int GetTotalWordsCount();
  bool WasFileEndFound();
  bool WasTextEndFound();
  bool WasLineEndFound();
};
#endif  //  OOP_T0_0B_INCLUDE_SOLUTION_H_
