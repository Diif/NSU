#include <iostream>
#include <tuple>

#include "CSVParser.h"

template <typename Ch, typename Tr, size_t last_tuple_num, typename... Args>
struct Printer {
  static std::basic_ostream<Ch, Tr>& tuple_print(
      std::basic_ostream<Ch, Tr>& os, std::tuple<Args...> const& tuple) {
    Printer<Ch, Tr, last_tuple_num - 1, Args...>::tuple_print(os, tuple);
    return os << std::get<last_tuple_num - 1>(tuple) << '|';
  }
};

template <typename Ch, typename Tr, typename... Args>
struct Printer<Ch, Tr, 1, Args...> {
  static std::basic_ostream<Ch, Tr>& tuple_print(
      std::basic_ostream<Ch, Tr>& os, std::tuple<Args...> const& tuple) {
    return os << std::get<0>(tuple) << '|';
  }
};

template <typename Ch, typename Tr>
std::basic_ostream<Ch, Tr>& operator<<(std::basic_ostream<Ch, Tr>& os,
                                       std::tuple<> const& t) {
  return os;
}

template <typename Ch, typename Tr, typename... Args>
std::basic_ostream<Ch, Tr>& operator<<(std::basic_ostream<Ch, Tr>& os,
                                       std::tuple<Args...> const& tuple) {
  return Printer<Ch, Tr, sizeof...(Args), Args...>::tuple_print(os, tuple);
}

int main(int, char**) {
  std::ifstream file6("test6.txt");
  CSVParser<std::string, std::string> parser6(file6, 0, 'd', 'n', 'e');

  for (std::tuple<std::string, std::string> member : parser6) {
    std::cout << member << '\n';
  }

  // std::ifstream file5("test5.txt");
  // CSVParser<int, std::string> parser2(file5, 2);

  // for (std::tuple<int, std::string> member : parser2) {
  //   std::cout << member << '\n';
  // }

  // std::ifstream file("test4.txt");
  // CSVParser<int, double, std::string> parser(file, 0, ',', '!');

  // for (std::tuple<int, double, std::string> member : parser) {
  //   std::cout << member << '\n';
  // }

  return 0;
}
