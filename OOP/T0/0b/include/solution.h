#ifndef INCLUDE_SOLUTION_H_
#define INCLUDE_SOLUTION_H_
#include <map>
#include <string>
class WordReader {
 private:
  bool is_EOF_;
  std::string cur_word_;

 public:
  WordReader();
  std::string GetCurrentWord();
  void ReadWord();
  bool WasEndFound();
};
#endif  //  INCLUDE_SOLUTION_H_