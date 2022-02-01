#include "exceptions.h"

const char* BlockBeginningException::what() const noexcept {
  return "Can't find \"desc\" in the configuration file.\n";
}

const char* BlockEndException::what() const noexcept {
  return "Can't find \"csed\" in the configuration file.\n";
}

const char* BlockArgumentsException::what() const noexcept {
  return "Invalide arguments in block section. Can't create worker.\n";
}

BlockSyntaxException::BlockSyntaxException(std::string const& code_line,
                                           int pos) {
  msg = "Syntax mistake at line ";
  msg += std::to_string(pos) + ":";
  msg += '\n';
  msg += "\t\t";
  msg += code_line;
  msg += '\n';
}

BlockInvalidWorkerNameException::BlockInvalidWorkerNameException(
    std::string const& invalid_name) {
  msg = "Invalid worker name: \n";
  msg += "\t\t";
  msg += invalid_name;
  msg += '\n';
}

const char* BlockInvalidWorkerNameException::what() const noexcept {
  return msg.c_str();
}

const char* BlockSyntaxException::what() const noexcept { return msg.c_str(); }

const char* SequenceBeginningException::what() const noexcept {
  return "\"readfile\" must be the first operation in sequence!\n";
}

const char* SequenceEndException::what() const noexcept {
  return "\"writefile\" must be the last operation in sequence!\n";
}

const char* SequenceStructureException::what() const noexcept {
  return "Incorrect sequence structure. I/O conflict between workers.";
}

const char* WorkerRunTimeException::what() const noexcept {
  return "Worker failed.";
}