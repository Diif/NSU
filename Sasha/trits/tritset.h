#ifndef TRITSET_H_
#define TRITSET_H_
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

const int size_int = sizeof(unsigned int) * 8;
const int size_trit = 2;
const int count_trit_in_int = size_int / size_trit;

enum Trit { Unknown = 0, False = 1, True = 2 };

Trit operator&(Trit a, Trit b);
Trit operator|(Trit a, Trit b);
Trit operator~(Trit a);

class Tritset {
 private:
  vector<unsigned int> arr;
  size_t count_False = 0;
  size_t count_True = 0;
  int beginning_size;
  int current_size;

  void resize_vector(int count_trit);
  void change_trit_by_index(int index, Trit trit);
  int get_last_set_int_index();
  int get_last_set_trit_index();

  friend class Proxy_trit;
  class Proxy_trit {
    vector<unsigned int>& arr_;
    int index_;
    Tritset& tritset_;
    Trit value;

    Trit get_value();
    void change_count_True_and_False(Trit trit);

   public:
    Proxy_trit(int index, vector<unsigned int>& arr, Tritset& tritset);
    Trit operator=(Trit trit);
    Trit operator=(Proxy_trit p_trit);
    operator Trit();
  };

 public:
  Tritset(int count_trit);
  int get_size_in_trit();
  static int convert_int_index_to_trit_index(int int_index);
  static int convert_trit_index_to_int_index(int trit_index);
  Proxy_trit operator[](int index);
  void shrink();
  size_t cardinality(Trit value);
  unordered_map<Trit, size_t> cardinality();
  void trim(size_t lastIndex);
  size_t length();
};

#endif  //  TRITSET_H_