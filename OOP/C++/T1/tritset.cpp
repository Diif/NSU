#include "tritset.h"

Trit operator&(Trit trit1, Trit trit2) {
  if (trit1 == False || trit2 == False) {
    return False;
  }
  if (trit1 == True && trit2 == True) {
    return True;
  }
  return Unknown;
}

Trit operator|(Trit trit1, Trit trit2) {
  if (trit1 == True || trit2 == True) {
    return True;
  }
  if (trit1 == False && trit2 == False) {
    return False;
  }
  return Unknown;
}

Trit operator~(Trit trit) {
  if (trit == True) {
    return False;
  }
  if (trit == False) {
    return True;
  }
  return Unknown;
}

ostream &operator<<(ostream &out, Trit trit) {
  if (trit == True) {
    return out << "T";
  }
  if (trit == False) {
    return out << "F";
  }
  return out << "U";
}

// private

uint TritSet::GetSize() { return array_size_; }

uint TritSet::GetUintCountFromTritsCount(const uint trits_count) {
  double uint_count = static_cast<double>(trits_count) / kTritsInUint;
  uint_count = ceil(uint_count);
  return static_cast<uint>(uint_count);
}

uint TritSet::GetUintIndFromTritInd(const uint trit_ind) {
  double uint_ind = trit_ind;
  uint_ind /= kTritsInUint;
  return static_cast<uint>(uint_ind);
}

void TritSet::Resize(const uint new_size_in_trits) {
  uint uint_count = GetUintCountFromTritsCount(new_size_in_trits);
  trits_array_.resize(uint_count, Trit::Unknown);
  array_size_ = uint_count * kTritsInUint;
}

inline uint TritSet::GetTritIndInUint(uint trit_ind) {
  return trit_ind % kTritsInUint;
}

// public
TritSet::TritSet(const uint size_in_trits) { Resize(size_in_trits); }

TritSet::TritSet(const TritSet &set) {
  trits_array_ = set.trits_array_;
  array_size_ = set.array_size_;
}

Trit TritSet::GetTritValue(const uint trit_ind) {
  if (array_size_ <= trit_ind) {
    return Unknown;
  }

  uint uint_ind = GetUintIndFromTritInd(trit_ind);
  uint uint_with_trit = trits_array_[uint_ind];
  uint max_trit_ind_in_uint = kTritsInUint - 1;
  uint last_two_are_ones = 3;
  uint shift = (max_trit_ind_in_uint * 2) -
               (GetTritIndInUint(trit_ind) * kTritBitesSize);
  uint_with_trit = uint_with_trit >> shift;
  uint_with_trit = uint_with_trit & last_two_are_ones;
  return static_cast<Trit>(uint_with_trit);
}

void TritSet::SetTritValue(uint trit_ind, Trit new_value) {
  if (array_size_ <= trit_ind) {
    throw invalid_argument(
        "Trit ind is out of vector size! Go out of private methods.");
  }

  uint uint_ind = GetUintIndFromTritInd(trit_ind);
  uint uint_to_change = trits_array_[uint_ind];
  uint trit_ind_in_uint = GetTritIndInUint(trit_ind);

  uint new_uint_to_put =
      PutTritToIndInUint(new_value, trit_ind_in_uint, uint_to_change);
  trits_array_[uint_ind] = new_uint_to_put;
}

uint TritSet::PutTritToIndInUint(uint trit, uint trit_ind_in_uint,
                                 uint uint_to_change) {
  uint new_value_in_trit_place = 0;  //  = 00...000
  new_value_in_trit_place =
      new_value_in_trit_place |
      (trit << (sizeof(uint) * CHAR_BIT) - 2);  //  XX00...000
  uint frst_two_are_ones = UINT_MAX
                           << (sizeof(uint) * CHAR_BIT) - 2;  //  1100...000
  uint zeroes_in_trit_place = UINT_MAX >> 2;                  //  =  00111...111
  for (uint i = 0; i < trit_ind_in_uint; i++) {
    new_value_in_trit_place = new_value_in_trit_place >> 2;
    zeroes_in_trit_place = zeroes_in_trit_place >> 2;
    zeroes_in_trit_place = zeroes_in_trit_place | frst_two_are_ones;
  }
  uint_to_change = uint_to_change & zeroes_in_trit_place;
  uint_to_change = uint_to_change | new_value_in_trit_place;
  return uint_to_change;
}

uint TritSet::GetUintIndWithLastTrit() {
  uint uint_count = GetSize() / kTritsInUint;
  uint last_filled_uint;
  for (last_filled_uint = uint_count - 1; last_filled_uint >= 0;
       last_filled_uint--) {
    if (trits_array_[last_filled_uint] != 0 || last_filled_uint == 0) {
      break;
    }
  }
  return last_filled_uint;
}

uint TritSet::GetLastSettedTritIndInUint(uint uint_with_trits) {
  Trit cur_trit = Unknown;
  uint cur_trit_ind;
  uint last_two_ones = 3;  //  00..11
  for (cur_trit_ind = kTritsInUint; cur_trit_ind >= 0 && cur_trit == Unknown;) {
    cur_trit_ind--;
    cur_trit = static_cast<Trit>(uint_with_trits & last_two_ones);
    uint_with_trits = uint_with_trits >> 2;
  }
  return cur_trit_ind;
}

uint TritSet::GetLastSettedTritInd() {
  uint last_uint_ind_with_trit = GetUintIndWithLastTrit();
  uint trit_ind_in_uint =
      GetLastSettedTritIndInUint(trits_array_[last_uint_ind_with_trit]);
  uint trit_ind = last_uint_ind_with_trit * kTritsInUint + trit_ind_in_uint;
  return trit_ind;
}

void TritSet::Shrink() {
  uint last_filled_uint = GetUintIndWithLastTrit();
  Resize((last_filled_uint + 1) * kTritsInUint);
}

void TritSet::TrimUintAfterTritInd(uint trit_ind) {
  uint trit_ind_in_uint = GetTritIndInUint(trit_ind);
  uint shift = (kTritsInUint - 1) - trit_ind_in_uint;
  uint zeroes_after_trit = UINT_MAX;
  for (uint i = 0; i < shift; i++) {
    zeroes_after_trit = zeroes_after_trit << 2;
  }
  uint uint_to_change_ind = GetUintIndFromTritInd(trit_ind);
  uint uint_to_change = trits_array_[uint_to_change_ind];
  uint_to_change = uint_to_change & zeroes_after_trit;
  trits_array_[uint_to_change_ind] = uint_to_change;
}

void TritSet::Trim(uint trit_ind) {
  uint last_uint_ind = GetUintIndFromTritInd(trit_ind);
  Resize((last_uint_ind + 1) * kTritsInUint);
  TrimUintAfterTritInd(trit_ind);
}

uint TritSet::GetCountOfTritsWithType(Trit type) {
  uint last_filled_uint_ind = GetUintIndWithLastTrit();
  uint last_trit_ind = (last_filled_uint_ind + 1) * kTritsInUint - 1;
  uint unknown_trits_after_last_trit = 0;
  uint trit_count = 0;
  for (uint i = 0; i <= last_trit_ind; i++) {
    Trit cur_trit = GetTritValue(i);
    if (cur_trit == type) {
      trit_count++;
    }
    if (cur_trit == Unknown) {
      unknown_trits_after_last_trit++;
    } else {
      unknown_trits_after_last_trit = 0;
    }
  }
  if (type == Unknown) {
    trit_count -= unknown_trits_after_last_trit;
  }
  return trit_count;
}

unordered_map<Trit, uint> TritSet::Cardinality() {
  unordered_map<Trit, uint> result;
  result[False] = GetCountOfTritsWithType(False);
  result[True] = GetCountOfTritsWithType(True);
  result[Unknown] = GetCountOfTritsWithType(Unknown);
  return result;
}

// operator override

ostream &operator<<(ostream &out, TritSet::ProxyTrit proxy_trit) {
  return out << proxy_trit.GetTritValue();
}

TritSet::ProxyTrit TritSet::operator[](const uint trit_ind) {
  uint uint_ind = GetUintIndFromTritInd(trit_ind);
  return ProxyTrit(*this, uint_ind, trit_ind);
}

TritSet TritSet::operator&(TritSet &set) {
  uint set1_size = GetSize();
  uint set2_size = set.GetSize();
  uint new_set_size = max(set1_size, set2_size);

  TritSet result_set(new_set_size);
  for (uint cur_trit_ind = 0; cur_trit_ind < new_set_size; cur_trit_ind++) {
    result_set[cur_trit_ind] = (*this)[cur_trit_ind] & set[cur_trit_ind];
  }
  return result_set;
}

TritSet TritSet::operator|(TritSet &set) {
  uint set1_size = GetSize();
  uint set2_size = set.GetSize();
  uint new_set_size = max(set1_size, set2_size);

  TritSet result_set(new_set_size);
  for (uint cur_trit_ind = 0; cur_trit_ind < new_set_size; cur_trit_ind++) {
    result_set[cur_trit_ind] = (*this)[cur_trit_ind] | set[cur_trit_ind];
  }
  return result_set;
}

TritSet TritSet::operator~() {
  uint new_set_size = GetSize();

  TritSet result_set(new_set_size);
  for (uint cur_trit_ind = 0; cur_trit_ind < new_set_size; cur_trit_ind++) {
    result_set[cur_trit_ind] = ~(*this)[cur_trit_ind];
  }
  return result_set;
}

// Proxy

TritSet::ProxyTrit::ProxyTrit(TritSet &set, uint ind_of_uint_with_trit,
                              uint trit_ind)
    : set(set), trit_ind(trit_ind) {
  trit_value = set.GetTritValue(trit_ind);
  cur_uint = ind_of_uint_with_trit;
}

Trit TritSet::ProxyTrit::GetTritValue() { return trit_value; }

void TritSet::ProxyTrit::operator=(Trit new_trit_value) {
  uint number_of_trits = trit_ind + 1;
  if (set.GetSize() < number_of_trits) {
    if (new_trit_value == True || new_trit_value == False) {
      set.Resize(number_of_trits);
      set.SetTritValue(trit_ind, new_trit_value);
    }
  } else {
    set.SetTritValue(trit_ind, new_trit_value);
  }
}

void TritSet::ProxyTrit::operator=(ProxyTrit new_trit) {
  uint number_of_trits = trit_ind + 1;
  Trit new_trit_value = new_trit.trit_value;
  if (set.GetSize() < number_of_trits) {
    if (new_trit_value == True || new_trit_value == False) {
      set.Resize(number_of_trits);
      set.SetTritValue(trit_ind, new_trit_value);
    }
  } else {
    set.SetTritValue(trit_ind, new_trit_value);
  }
}
