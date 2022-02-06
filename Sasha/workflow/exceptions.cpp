#include "exceptions.h"

const char* bad_file::what() const noexcept {
  return "file hasn`t opened or file has bad state";
}

const char* no_desc_csed::what() const noexcept { return "no desc or csed"; }

const char* error_str::what() const noexcept { return "error_str"; }