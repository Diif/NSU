#include <exception>

class BadFile : public std::exception {
 public:
  const char* what() const noexcept override;
};

const char* BadFile::what() const noexcept { return "File has bad state!"; }

class DataWrongFormat : public std::exception {
 private:
  int line_;
  int column_;
  std::string type_;

 public:
  DataWrongFormat(int line, int column, const char* type) {
    line_ = line;
    column_ = column;
    type = "";
    type_ += type;
  }
  const char* what() const noexcept override;
};

const char* DataWrongFormat::what() const noexcept {
  std::string msg = "\tFile has has wrong format!\n\tline: ";
  msg += std::to_string(line_);
  msg += '\n';
  msg += '\t';
  msg += "column: ";
  msg += std::to_string(column_);
  msg += '\n';
  msg += '\t';
  msg += "incorrect format for: ";
  msg += type_;
  return msg.c_str();
}
