#include "exceptions.h"

const char* BlockBeginningException::what() const noexcept {
  return "Can't find \"decs\" in the configuration file.";
}

const char* BlockEndException::what() const noexcept {
  return "Can't find \"csed\" in the configuration file.";
}

BlockSyntaxException::BlockSyntaxException(std::string const& code_line,
                                           int pos) {
  msg = "Syntax mistake at line ";
  msg += std::to_string(pos) + ":";
  msg += '\n';
  msg += "\t\t";
  msg += code_line;
}

const char* BlockSyntaxException::what() const noexcept { return msg.c_str(); }