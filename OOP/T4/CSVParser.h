#include <cstddef>
#include <fstream>
#include <iterator>
#include <string>
#include <tuple>
#include <vector>

#include "exceptions.h"

namespace ParserHelper {
void TestInteger(std::string& str, int line, int column) {}
void TestChar(std::string& str, int line, int column) {}
void TestFloatingPoint(std::string& str, int line, int column) {}

template <typename T>
T ConvertString(std::string& str, int line, int column){};

template <>
std::string ConvertString<std::string>(std::string& str, int line, int column) {
  return str;
};
template <>
char ConvertString<char>(std::string& str, int line, int column){};
template <>
int ConvertString<int>(std::string& str, int line, int column){};
template <>
long long ConvertString<long long>(std::string& str, int line, int column){};
template <>
double ConvertString<double>(std::string& str, int line, int column){};
template <>
float ConvertString<float>(std::string& str, int line, int column){};

template <typename... Args, size_t... Indexes>
std::tuple<Args...> ParseVector(std::vector<std::string>& vector) {}
}  // namespace ParserHelper

template <typename... Args>
class CSVParser {
 private:
  char delim_;
  char new_line_symb_;
  char escape_symb_;
  int skip_lines_;
  std::tuple<Args...>* tuple_;
  std::ifstream& file_;
  std::string cur_line_;
  std::string cur_word_;
  void ReadNewTuple();
  void CheckFile();

 public:
  struct Iterator {
   public:
    using iterator_category = std::input_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = std::tuple<Args...>;
    using pointer = value_type*;
    using reference = value_type&;
    Iterator(pointer ptr) : ptr_(ptr) {}
    pointer operator->() { return ptr_; }
    reference operator*() { return *ptr_; }

   private:
    pointer ptr_;
  };
  CSVParser(std::ifstream& file, int skip_lines = 0, char delim = ',',
            char new_line_symb = '\n', char escape_symb = '\"');
  ~CSVParser();
};

template <typename... Args>
CSVParser<Args...>::CSVParser(std::ifstream& file, int skip_lines = 0,
                              char delim, char new_line_symb, char escape_symb)
    : file_(file) {
  skip_lines_ = skip_lines;
  delim_ = delim;
  new_line_symb_ = new_line_symb;
  escape_symb_ = escape_symb;
  tuple_ = new std::tuple<Args...>;
  CheckFile();
  ReadNewTuple();
}

template <typename... Args>
CSVParser<Args...>::~CSVParser() {
  file_.close();
  delete tuple_;
}

template <typename... Args>
void CSVParser<Args...>::ReadNewTuple() {}

template <typename... Args>
void CSVParser<Args...>::CheckFile() {
  if (file_.bad()) {
    throw(BadFile{});
  }
}