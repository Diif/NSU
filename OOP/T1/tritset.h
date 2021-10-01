#ifndef INCLUDE_TRITSET_H_
#define INCLUDE_TRITSET_H_
#include <climits>
#include <cmath>
#include <iostream>
#include <vector>

using uint = unsigned int;
using namespace std;

enum Trit : uint { False = 1, Unknown = 0, True = 2 };
Trit operator&(Trit trit1, Trit trit2);
Trit operator~(Trit trit);
Trit operator|(Trit trit1, Trit trit2);

const uint kTritBitesSize = 2;
const uint kTritsInUint = sizeof(uint) * CHAR_BIT / kTritBitesSize;

class TritSet {
  class ProxyTrit {
   private:
    TritSet &set;
    uint cur_uint;
    Trit trit_value;
    uint trit_ind;

   public:
    ProxyTrit(TritSet &set, uint ind_of_uint_with_trit, uint trit_ind);
    ProxyTrit(Trit trit);
    operator Trit() { return trit_value; };
    void operator=(Trit new_trit_value);
    void operator=(ProxyTrit new_trit);
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
  uint FindUintIndWithLastTrit();
  uint GetCountOfTritsWithType(Trit type);
  explicit TritSet(const uint size);
  TritSet(const TritSet &set);
  void Resize(const uint new_size_in_trits);
  void SetTritValue(uint trit_ind, Trit new_value);
  uint PutTritToIndInUint(uint trit, uint trit_ind_in_uint,
                          uint uint_to_change);
  void Shrink();
  TritSet &operator&(TritSet &set);
  TritSet &operator|(TritSet &set);
  TritSet &operator~();
  ProxyTrit operator[](const uint trit_ind);
  // ~TritSet();
};

Trit operator&(Trit trit1, Trit trit2);

#endif  //  INCLUDE_TRITSET_H_