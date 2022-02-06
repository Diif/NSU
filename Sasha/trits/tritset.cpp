#include "tritset.h"

Trit operator&(Trit a, Trit b) {
  if (a == False | b == False)
    return False;
  else if (a == True & b == True)
    return True;
  return Unknown;
}

Trit operator|(Trit a, Trit b) {
  if (a == True | b == True)
    return True;
  else if (a == False & b == False)
    return False;
  return Unknown;
}

Trit operator~(Trit a) {
  if (a == False) return True;
  if (a == True) return False;
  return Unknown;
}

int Tritset::convert_int_index_to_trit_index(int int_index) {
  return int_index * count_trit_in_int;
}

int Tritset::convert_trit_index_to_int_index(int trit_index) {
  return trit_index / count_trit_in_int;
}

void Tritset::resize_vector(int count_trit) {
  int count_int = convert_trit_index_to_int_index(count_trit - 1) + 1;
  arr.resize(count_int, 0);
  current_size = count_int * count_trit_in_int;
}

void Tritset::change_trit_by_index(int index, Trit trit) {
  unsigned int changed_int;
  unsigned int buf = ~0;
  int int_index = convert_trit_index_to_int_index(index);
  changed_int = arr[int_index];
  buf = buf << (size_int - 2);
  buf = buf >> (2 * index);
  changed_int = changed_int & (~buf);
  buf = static_cast<unsigned int>(trit);
  buf = buf << (size_int - 2);
  buf = buf >> (2 * index);
  changed_int = changed_int | buf;
  arr[int_index] = changed_int;
}

Tritset::Proxy_trit::Proxy_trit(int index, vector<unsigned int>& arr,
                                Tritset& tritset)
    : index_(index), arr_(arr), tritset_(tritset) {
  value = get_value();
}

Trit Tritset::Proxy_trit::get_value() {
  unsigned int value;
  int int_index = convert_trit_index_to_int_index(index_);
  if ((index_ + 1) > tritset_.current_size) {
    return Unknown;
  }
  unsigned int int_in_arr_ = arr_[int_index];
  value = int_in_arr_ << (index_ % count_trit_in_int) * 2;
  value = value >> (count_trit_in_int - 1) * 2;
  return static_cast<Trit>(value);
}

void Tritset::Proxy_trit::change_count_True_and_False(Trit trit) {
  switch (trit) {
    case True:
      tritset_.count_True++;
      break;
    case False:
      tritset_.count_False++;
      break;
    default:
      break;
  }
  switch (value) {
    case True:
      tritset_.count_True--;
      break;
    case False:
      tritset_.count_False--;
      break;
    default:
      break;
  }
}

Trit Tritset::Proxy_trit::operator=(Trit trit) {
  if (convert_trit_index_to_int_index(index_) > arr_.size() - 1) {
    if (trit != Unknown) {
      change_count_True_and_False(trit);
      tritset_.resize_vector(index_);
      tritset_.change_trit_by_index(index_, trit);
    }
  } else {
    change_count_True_and_False(trit);
    tritset_.change_trit_by_index(index_, trit);
  }
  value = get_value();
  return value;
}

Trit Tritset::Proxy_trit::operator=(Tritset::Proxy_trit p_trit) {
  return *this = static_cast<Trit>(p_trit);
}

Tritset::Proxy_trit::operator Trit() { return value; }

Tritset::Tritset(int count_trit) {
  resize_vector(count_trit);
  beginning_size = count_trit;
}

int Tritset::get_size_in_trit() { return current_size; }

Tritset::Proxy_trit Tritset::operator[](int index) {
  Proxy_trit p_trit(index, arr, *this);
  return p_trit;
}

int Tritset::get_last_set_int_index() {
  int last_int_index = convert_trit_index_to_int_index(current_size - 1);
  for (int i = last_int_index; i >= 0; i--) {
    if (arr[i] != 0) return i;
  }
  return -1;
}

int Tritset::get_last_set_trit_index() {
  int trit_index =
      convert_int_index_to_trit_index(get_last_set_int_index()) + 15;
  for (int i = trit_index; i >= trit_index - 15; i--) {
    if ((*this)[i] != Unknown) return i;
  }
  return 0;
}

void Tritset::shrink() {
  int last_int_index = get_last_set_int_index();
  int index = convert_int_index_to_trit_index(last_int_index);
  if (index > -1)
    resize_vector(index + 1);
  else
    resize_vector(beginning_size);
}

size_t Tritset::cardinality(Trit value) {
  switch (value) {
    case True:
      return count_True;
      break;
    case False:
      return count_False;
      break;
    case Unknown: {
      int count_all =
          (convert_trit_index_to_int_index(get_last_set_trit_index()) + 1) *
          count_trit_in_int;
      int count_True_and_False = count_True + count_False;
      int count_Unknown = count_all - count_True_and_False;
      return count_Unknown;
    } break;
    default:
      return 0;
      break;
  }
}

unordered_map<Trit, size_t> Tritset::cardinality() {
  unordered_map<Trit, size_t> map;
  map[True] = cardinality(True);
  map[False] = cardinality(False);
  map[Unknown] = cardinality(Unknown);
  return map;
}

void Tritset::trim(size_t lastIndex) {
  if (lastIndex + 1 <= get_size_in_trit()) {
    resize_vector(lastIndex + 1);
    int last_trit_index_in_int;
    last_trit_index_in_int =
        count_trit_in_int * convert_trit_index_to_int_index(lastIndex) + 15;
    for (int i = lastIndex + 1; i <= last_trit_index_in_int; i++) {
      (*this)[i] = Unknown;
    }
  }
}

size_t Tritset::length() { return get_last_set_trit_index() + 1; }