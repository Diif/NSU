#include <cstddef>
#include <fstream>
#include <iterator>
#include <string>
#include <tuple>
#include <vector>

#include "exceptions.h"

namespace ParserHelper {
void TestInteger(std::string& str, int row, int column) {}
void TestChar(std::string& str, int row, int column) {}
void TestFloatingPoint(std::string& str, int row, int column) {}

template <typename T>
T ConvertString(std::string& str, int row, int column) {
  throw(UnsupportedDataFormat{});
}

template <>
std::string ConvertString<std::string>(std::string& str, int row, int column) {
  return str;
}
template <>
char ConvertString<char>(std::string& str, int row, int column) {
  if (str.size() > 1) {
    throw(InvalidDataFormat{row, column, "char"});
  }
  return str[0];
}
template <>
int ConvertString<int>(std::string& str, int row, int column) {
  int size = str.size();
  for (size_t i = 0; i < size; i++) {
    if (!std::isdigit(str[i])) {
      throw(InvalidDataFormat{row, column, "int"});
    }
  }
  return std::stoi(str);
}
template <>
long long ConvertString<long long>(std::string& str, int row, int column) {
  int size = str.size();
  for (size_t i = 0; i < size; i++) {
    if (!std::isdigit(str[i])) {
      throw(InvalidDataFormat{row, column, "long long"});
    }
  }
  return std::stoll(str);
}
template <>
double ConvertString<double>(std::string& str, int row, int column) {
  int size = str.size();
  bool point_found = false;
  bool digit_after_point_found = false;
  for (size_t i = 0; i < size; i++) {
    if (!std::isdigit(str[i]) && str[i] != '.') {
      throw(InvalidDataFormat{row, column, "double"});
    }
    if (str[i] == '.' && point_found) {
      throw(InvalidDataFormat{row, column, "double"});
    } else if (str[i] == '.') {
      point_found = true;
    }
    if (std::isdigit(str[i]) && point_found) {
      digit_after_point_found = true;
    }
  }
  if (point_found && !digit_after_point_found) {
    throw(InvalidDataFormat{row, column, "double"});
  }
  return std::stod(str);
}

template <>
float ConvertString<float>(std::string& str, int row, int column) {
  int size = str.size();
  bool point_found = false;
  bool digit_after_point_found = false;
  for (size_t i = 0; i < size; i++) {
    if (!std::isdigit(str[i]) && str[i] != '.') {
      throw(InvalidDataFormat{row, column, "float"});
    }
    if (str[i] == '.' && point_found) {
      throw(InvalidDataFormat{row, column, "float"});
    } else if (str[i] == '.') {
      point_found = true;
    }
    if (std::isdigit(str[i]) && point_found) {
      digit_after_point_found = true;
    }
  }
  if (point_found && !digit_after_point_found) {
    throw(InvalidDataFormat{row, column, "float"});
  }
  return std::stof(str);
}

template <typename... Args, size_t... Indexes>
std::tuple<Args...> ConvertVectorToTuple(std::vector<std::string>& vector,
                                         std::index_sequence<Indexes...>,
                                         int row) {
  return std::make_tuple(
      ConvertString<Args>(vector[Indexes], row, Indexes + 1)...);
}
}  // namespace ParserHelper

template <typename... Args>
class CSVParser {
 private:
  char delim_;
  char new_line_symb_;
  char escape_symb_;
  int skip_lines_;
  int cur_row_;
  int cur_column_;
  static constexpr const int arg_count_ = sizeof...(Args);

  std::ifstream& file_;

  std::string cur_line_;
  std::string cur_word_;

  void CheckFile();

 public:
  //////////
  std::vector<std::string> cur_line_by_words_;  // TODO move to private
  void ReadNewTuple();
  std::tuple<Args...> tuple_;
  //////////
  struct Iterator {
   public:
    using iterator_category = std::input_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = std::tuple<Args...>;
    using pointer = value_type*;
    using reference = value_type&;
    Iterator(pointer ptr, CSVParser& parser, bool MakeEnd)
        : ptr_(ptr), parser_(parser) {
      if (MakeEnd) {
        end_ = true;
      } else {
        end_ = false;
        if (parser_.file_.eof()) {
          end_ = true;
        } else {
          parser_.ReadNewTuple();
        }
      }
    }
    pointer operator->() { return ptr_; }
    const reference operator*() { return *ptr_; }
    Iterator& operator++() {
      if (parser_.file_.eof()) {
        end_ = true;
      } else {
        parser_.ReadNewTuple();
      }
      return *this;
    }
    Iterator operator++(int) {
      auto tmp = *this;
      ++(*this);
      return tmp;
    }
    friend bool operator==(const Iterator& a, const Iterator& b) {
      if (a.end_ == true && a.end_ == b.end_) {
        return true;
      }
      if (a.end_ == true && b.end_ == false) {
        return false;
      }
      if (a.end_ == false && b.end_ == true) {
        return false;
      }
      return a.ptr_ == b.ptr_;
    }
    friend bool operator!=(const Iterator& a, const Iterator& b) {
      return !(a == b);
    }

   private:
    pointer ptr_;
    CSVParser& parser_;
    bool end_;
  };
  Iterator begin() { return Iterator(&tuple_, *this, false); }
  Iterator end() {
    Iterator iter(&tuple_, *this, true);
    return iter;
  }
  CSVParser(std::ifstream& file, int skip_lines = 0, char delim = ',',
            char new_line_symb = '\n', char escape_symb = '\"');
  ~CSVParser();
};

template <typename... Args>
CSVParser<Args...>::CSVParser(std::ifstream& file, int skip_lines, char delim,
                              char new_line_symb, char escape_symb)
    : file_(file) {
  skip_lines_ = skip_lines;
  delim_ = delim;
  new_line_symb_ = new_line_symb;
  escape_symb_ = escape_symb;
  cur_column_ = 1;
  CheckFile();
  for (size_t i = 0; i < skip_lines_; i++) {
    std::getline(file_, cur_line_, new_line_symb_);
  }
  cur_row_ = skip_lines_ + 1;
}

template <typename... Args>
CSVParser<Args...>::~CSVParser() {
  file_.close();
}

template <typename... Args>
void CSVParser<Args...>::ReadNewTuple() {
  cur_line_.clear();
  cur_word_.clear();
  cur_line_by_words_.clear();
  cur_column_ = 1;
  int char_index = 0;
  std::getline(file_, cur_line_, new_line_symb_);
  while (cur_line_[char_index] != '\0') {
    // delim case
    if (cur_line_[char_index] == delim_) {
      cur_line_by_words_.push_back(cur_word_);
      cur_column_++;
      cur_word_.clear();
      char_index++;
      continue;
    }
    // escape_case
    if (cur_line_[char_index] == escape_symb_ &&
        (char_index == 0 || cur_line_[char_index - 1] == delim_)) {
      char_index++;
      bool escape_symb_was_closed = false;
      while (!escape_symb_was_closed) {
        if (cur_line_[char_index] == '\0') {
          if (file_.eof()) {
            throw(EscapeSymbolError{cur_row_, cur_column_});
          } else {
            cur_word_ += new_line_symb_;
            std::getline(file_, cur_line_, new_line_symb_);
            cur_row_++;
            char_index = 0;
            continue;
          }
        }
        if (cur_line_[char_index] == escape_symb_) {
          if (cur_line_[char_index + 1] == '\0' ||
              cur_line_[char_index + 1] == delim_) {
            escape_symb_was_closed = true;
            break;
          }
        }
        cur_word_ += cur_line_[char_index];
        char_index++;
      }
      char_index++;
      continue;
    }
    // default case
    cur_word_ += cur_line_[char_index];
    char_index++;
  }
  cur_line_by_words_.push_back(cur_word_);
  if (cur_column_ != arg_count_) {
    throw(InvalidCountOfArgs{cur_row_, cur_column_, cur_column_, arg_count_});
  }
  tuple_ = ParserHelper::ConvertVectorToTuple<Args...>(
      cur_line_by_words_, std::make_index_sequence<arg_count_>{}, cur_row_);
  cur_row_++;
}

template <typename... Args>
void CSVParser<Args...>::CheckFile() {
  if (file_.bad() || file_.fail()) {
    throw(BadFile{});
  }
}