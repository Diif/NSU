// #include <iostream>
// #include <tuple>

// template <typename Ch, typename Tr>
// std::basic_ostream<Ch, Tr>& operator<<(std::basic_ostream<Ch, Tr>& os,
//                                        std::tuple<> const& t) {
//   return os;
// }

// template <typename Ch, typename Tr, size_t last_tuple_num, typename... Args>
// std::basic_ostream<Ch, Tr>& tuple_print(std::basic_ostream<Ch, Tr>& os,
//                                         std::tuple<Args...> const& tuple) {
//   tuple_print<Ch, Tr, last_tuple_num - 1, Args...>(os, tuple);
//   return os << std::get<last_tuple_num - 1>(tuple);
// }

// template <typename Ch, typename Tr, size_t last_tuple_num == 0,
//           typename... Args>
// std::basic_ostream<Ch, Tr>& tuple_print(std::basic_ostream<Ch, Tr>& os,
//                                         std::tuple<Args...> const& tuple) {
//   return os << std::get<0>(tuple);
// }

// template <typename Ch, typename Tr, typename... Args>
// std::basic_ostream<Ch, Tr>& operator<<(std::basic_ostream<Ch, Tr>& os,
//                                        std::tuple<Args...> const& tuple) {
//   return tuple_print<Ch, Tr, sizeof...(Args), Args...>(os, tuple);
// }
// int main(int, char**) {
//   std::tuple<int, int, int, int> test(20, 30, 40, 60);
//   std::cout << test;
// }

#include <iostream>
#include <tuple>

template <typename Ch, typename Tr, size_t last_tuple_num, typename... Args>
struct Printer {
  static std::basic_ostream<Ch, Tr>& tuple_print(
      std::basic_ostream<Ch, Tr>& os, std::tuple<Args...> const& tuple) {
    Printer<Ch, Tr, last_tuple_num - 1, Args...>::tuple_print(os, tuple);
    return os << std::get<last_tuple_num - 1>(tuple);
  }
};

template <typename Ch, typename Tr, typename... Args>
struct Printer<Ch, Tr, 1, Args...> {
  static std::basic_ostream<Ch, Tr>& tuple_print(
      std::basic_ostream<Ch, Tr>& os, std::tuple<Args...> const& tuple) {
    return os << std::get<0>(tuple);
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
  std::tuple<int, int, int, int> test(20, 30, 40, 60);
  std::cout << test;
}
