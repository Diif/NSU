#include <exception>
#include <string>

class BlockBeginningException : public std::exception {
 public:
  const char* what() const noexcept override;
};

class BlockSyntaxException : public std::exception {
 private:
  std::string msg;

 public:
  BlockSyntaxException(std::string const& code_line, int pos);
  const char* what() const noexcept override;
};

class BlockEndException : public std::exception {
 public:
  const char* what() const noexcept override;
};
