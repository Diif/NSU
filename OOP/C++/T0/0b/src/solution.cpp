#include "solution.h"

WordReader::WordReader() {
  cur_word_ = "";
  cur_line = "";
  total_words_ = 0;
  line_eof_reached_ = true;
  file_eof_reached_ = false;
}

WordReader::~WordReader() { file_.close(); }

void WordReader::OpenFile(std::string str) { file_.open(str); }

bool WordReader::WasFileEndFound() { return file_eof_reached_; }
bool WordReader::WasTextEndFound() {
  return line_eof_reached_ && file_eof_reached_;
}
bool WordReader::WasLineEndFound() { return line_eof_reached_; }

void WordReader::ReadWord() {
  if (line_eof_reached_ == true) {
    ReadLine();
  }
  if (line_eof_reached_ == false) {
    cur_word_ = "";
    std::regex rgx("\\s+");
    std::sregex_token_iterator iter(cur_line.begin(), cur_line.end(), rgx, -1);
    cur_word_ = (*iter);
    if (cur_word_.empty() == false) {
      iter++;
      cur_line += cur_word_.length();
      IncreaseTotalWordsCount();
    }
    std::sregex_token_iterator end;
    if (iter == end) {
      line_eof_reached_ = true;
    }
  }
}

std::string WordReader::GetCurrentWord() { return cur_word_; }

std::ifstream* WordReader::GetFilePointer() { return &file_; }

void WordReader::IncreaseTotalWordsCount() { total_words_++; }

int WordReader::GetTotalWordsCount() { return total_words_; }

void WordReader::ReadLine() {
  std::getline(file_, cur_line, '\n');
  line_eof_reached_ = false;
  line_stream_.str(std::string());
  line_stream_.clear();
  line_stream_ << cur_line;
  // std::cout << line_stream_.str() << std::endl;
  if (file_.eof()) {
    file_eof_reached_ = true;
  }
}
