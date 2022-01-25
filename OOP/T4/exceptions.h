#include <exception>

class BadFile : public std::exception {
 public:
  const char* what() const noexcept override;
};

const char* BadFile::what() const noexcept {
  return "\nFile has bad state/falis (not eof)!";
}

class InvalidDataFormat : public std::exception {
 private:
  std::string msg;

 public:
  InvalidDataFormat(int row, int column, const char* type) {
    msg = "\n\tFile has has wrong format!\n\trow: ";
    msg += std::to_string(row);
    msg += '\n';
    msg += '\t';
    msg += "column: ";
    msg += std::to_string(column);
    msg += '\n';
    msg += '\t';
    msg += "incorrect format for: ";
    msg += type;
  }
  const char* what() const noexcept override;
};

const char* InvalidDataFormat::what() const noexcept { return msg.c_str(); }

class UnsupportedDataFormat : public std::exception {
 public:
  const char* what() const noexcept override;
};

const char* UnsupportedDataFormat::what() const noexcept {
  return "\n\tUnsupported type!\n\tTry: int, long long, float, double, char, "
         "string.";
}

class EscapeSymbolError : public std::exception {
 private:
  std::string msg;

 public:
  EscapeSymbolError(int row, int column) {
    msg = "\n\tEscape symbols must be used in pair!\n\trow: ";
    msg += std::to_string(row);
    msg += '\n';
    msg += '\t';
    msg += "column: ";
    msg += std::to_string(column);
  }
  const char* what() const noexcept override;
};

const char* EscapeSymbolError::what() const noexcept { return msg.c_str(); }

class InvalidCountOfArgs : public std::exception {
 private:
  std::string msg;

 public:
  InvalidCountOfArgs(int row, int column, int invalid_count, int valid_count) {
    msg = "\n\tFile must have ";
    msg += std::to_string(valid_count);
    msg += " columns per row, but have ";
    msg += std::to_string(invalid_count);
    msg += ".";
    msg += '\n';
    msg += '\t';
    msg += "row: ";
    msg += std::to_string(row);
  }
  const char* what() const noexcept override;
};

const char* InvalidCountOfArgs::what() const noexcept { return msg.c_str(); }
