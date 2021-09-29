#include "tritset.h"
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

void TritSet::SetSize(const uint new_size_in_trits) {
  uint uint_count = GetUintCountFromTritsCount(new_size_in_trits);
  trits_array_.resize(uint_count, Trit::Unknown);
  array_size_ = uint_count * kTritsInUint;
}

inline uint TritSet::GetTritIndInUint(uint trit_ind) {
  return trit_ind % kTritsInUint;
}

// public
TritSet::TritSet(const uint size_in_trits) { SetSize(size_in_trits); }

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
    return;
  }

  uint uint_ind = GetUintIndFromTritInd(trit_ind);
  uint uint_to_change = trits_array_[uint_ind];
  uint trit_ind_in_uint = GetTritIndInUint(trit_ind);

  uint new_uint_to_put =
      PutTritToIndInUint(new_value, trit_ind_in_uint, uint_to_change);
  trits_array_[uint_ind] = new_uint_to_put;
}
// Proxy
uint PutTritToIndInUint(uint trit, uint trit_ind_in_uint, uint uint_to_change) {
  uint new_value_in_trit_place = 0;  //  = 00...000
  new_value_in_trit_place =
      new_value_in_trit_place |
      (trit << (sizeof(uint) * CHAR_BIT) - 2);  //  XX00...000
  uint frst_two_are_ones = UINT_MAX
                           << (sizeof(uint) * CHAR_BIT) - 2;  //  1100...000
  uint zeroes_in_trit_place = UINT_MAX >> 2;                  //  =  00111...111
  for (uint i = 0; i < trit_ind_in_uint; i += 2) {
    new_value_in_trit_place = new_value_in_trit_place >> 2;
    zeroes_in_trit_place = zeroes_in_trit_place >> 2;
    zeroes_in_trit_place = zeroes_in_trit_place | frst_two_are_ones;
  }
  uint_to_change = uint_to_change & zeroes_in_trit_place;
  uint_to_change = uint_to_change | new_value_in_trit_place;
  return uint_to_change;
}
TritSet::ProxyTrit::ProxyTrit(TritSet &set, uint ind_of_uint_with_trit,
                              uint trit_ind)
    : set(set), trit_ind(trit_ind) {
  cur_uint = ind_of_uint_with_trit;
}

TritSet::ProxyTrit TritSet::operator[](const uint trit_ind) {
  uint uint_ind = GetUintIndFromTritInd(trit_ind);
  return ProxyTrit(*this, uint_ind, trit_ind);
}

void TritSet::ProxyTrit::operator=(Trit new_trit_value) {
  uint number_of_trits = trit_ind + 1;
  if (set.GetSize() < number_of_trits) {
    if (new_trit_value == True || new_trit_value == False) {
      set.SetSize(number_of_trits);
    }
  } else {
  }
}
