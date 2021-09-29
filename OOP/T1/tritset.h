#ifndef INCLUDE_TRITSET_H_
#define INCLUDE_TRITSET_H_
#include <cmath>
#include <iostream>
#include <vector>

using uint = unsigned int;
using namespace std;

enum Trit : uint { False = 1, Unknown = 0, True = 2 };

const uint kTritBitesSize = 2;
const uint kTritsInUint = sizeof(uint) * CHAR_BIT / kTritBitesSize;

class TritSet {
  class ProxyTrit {
   private:
    TritSet &set;
    uint cur_uint;
    uint trit_ind;

   public:
    ProxyTrit(TritSet &set, uint ind_of_uint_with_trit, uint trit_ind);
    void operator=(Trit new_trit_value);
  };

 private:
  vector<uint> trits_array_;
  uint array_size_ = 0;

 public:
  uint GetSize();
  uint GetUintCountFromTritsCount(const uint trits_count);
  uint GetTritIndInUint(uint trit_ind);
  uint GetUintIndFromTritInd(const uint trit_ind);  //  TODO move to private
  Trit GetTritValue(const uint trit_ind);
  explicit TritSet(const uint size);
  TritSet(const TritSet &set);
  void SetSize(const uint new_size_in_trits);
  void SetTritValue(uint trit_ind, Trit new_value);
  ProxyTrit operator[](const uint trit_ind);
  // ~TritSet();
};

#endif  //  INCLUDE_TRITSET_H_