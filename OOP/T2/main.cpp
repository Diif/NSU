#include <exception>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
// #include "gtest/gtest.h"

void TestF(std::sregex_token_iterator& iter) {
  std::sregex_token_iterator end;
  std::sregex_token_iterator start = iter;
  for (; iter != end; iter++) {
    std::cout << *iter << std::endl;
  }
  iter = start;
  for (; iter != end; iter++) {
    std::cout << *iter << std::endl;
  }
}

int main(int argc, char** argv) {
  // ::testing::InitGoogleTest(&argc, argv);
  // return RUN_ALL_TESTS();

  std::ifstream file("test.txt");
  std::string line;
  std::getline(file, line, '\n');
  std::regex re("\\s*([a-zA-Z]+\\d*)\\s*");
  std::smatch match;
  std::regex_search(line, match, re);
  size_t size = match.size();
  std::cout << "size: " << size << " line: " << line << std::endl;
  for (size_t i = 0; i < 3; i++) {
    std::cout << "Match " << i << ": " << match[i] << std::endl;
    std::regex_search(line, match, re);
  }

  // std::sregex_token_iterator end;
  // for (; iter != end; iter++) {
  //   std::cout << *iter << std::endl;
  // }

  return 0;
}
