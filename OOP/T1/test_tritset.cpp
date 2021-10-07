#include "gtest/gtest.h"
#include "tritset.h"
// for 4-byte uint, 64-bit OS

// move out of private to test
/*
TEST(TritSetTest, TritCountToUintCount) {
  TritSet set(10);
  EXPECT_EQ(0, set.GetUintCountFromTritsCount(0));
  EXPECT_EQ(1, set.GetUintCountFromTritsCount(1));
  EXPECT_EQ(1, set.GetUintCountFromTritsCount(2));
  EXPECT_EQ(1, set.GetUintCountFromTritsCount(16));
  EXPECT_EQ(2, set.GetUintCountFromTritsCount(17));
  EXPECT_EQ(2, set.GetUintCountFromTritsCount(31));
  EXPECT_EQ(2, set.GetUintCountFromTritsCount(32));
}

TEST(TritSetTest, TritIndToUintInd) {
  TritSet set(10);

  EXPECT_EQ(0, set.GetUintIndFromTritInd(0));
  EXPECT_EQ(1, set.GetUintIndFromTritInd(16));
  EXPECT_EQ(0, set.GetUintIndFromTritInd(15));
  EXPECT_EQ(0, set.GetUintIndFromTritInd(1));
}
TEST(TritSetTest, GetStartTritValue) {
  TritSet set(10);
  unsigned int max = kTritsInUint * 2;
  for (size_t i = 0; i < max; i++) {
    EXPECT_EQ(Unknown, set.GetTritValue(i));
  }
  EXPECT_EQ(Unknown, set.GetTritValue(max));
  EXPECT_EQ(Unknown, set.GetTritValue(max + 1));
  EXPECT_EQ(Unknown, set.GetTritValue(1000));
}

TEST(TritSetTest, SetAndGetTritValue) {
  TritSet set(10);
  unsigned int max = kTritsInUint;
  for (uint i = 0; i < max; i++) {
    set.SetTritValue(i, False);
    EXPECT_EQ(False, set.GetTritValue(i));
    set.SetTritValue(i, Unknown);
    EXPECT_EQ(Unknown, set.GetTritValue(i));
    set.SetTritValue(i, True);
    EXPECT_EQ(True, set.GetTritValue(i));
  }
  EXPECT_THROW(set.SetTritValue(10000, Unknown), std::invalid_argument);
  EXPECT_EQ(Unknown, set.GetTritValue(1000));
  EXPECT_EQ(True, set.GetTritValue(15));
  EXPECT_EQ(True, set.GetTritValue(7));
  EXPECT_EQ(True, set[0].GetTritValue());

  set.SetTritValue(0, Unknown);
  EXPECT_EQ(Unknown, set[0].GetTritValue());
  set.SetTritValue(0, False);
  EXPECT_EQ(False, set[0].GetTritValue());
  set.SetTritValue(0, True);
  EXPECT_EQ(True, set[0].GetTritValue());

  set.SetTritValue(15, Unknown);
  EXPECT_EQ(Unknown, set.GetTritValue(15));
  set.SetTritValue(15, False);
  EXPECT_EQ(False, set.GetTritValue(15));
  set.SetTritValue(15, True);
  EXPECT_EQ(True, set.GetTritValue(15));

  set.SetTritValue(7, Unknown);
  EXPECT_EQ(Unknown, set.GetTritValue(7));
  set.SetTritValue(7, False);
  EXPECT_EQ(False, set.GetTritValue(7));
  set.SetTritValue(7, True);
  EXPECT_EQ(True, set.GetTritValue(7));

  EXPECT_EQ(Unknown, set.GetTritValue(1002));
  EXPECT_THROW(set.SetTritValue(1002, True), std::invalid_argument);
}

TEST(TritSetTest, TrimUintAfterTritInd) {
  TritSet set(1000);
  set[1004] = False;
  set[1005] = True;
  set[1006] = True;
  set[1007] = True;
  set.TrimUintAfterTritInd(1004);
  EXPECT_EQ(False, set.GetTritValue(1004));
  EXPECT_EQ(Unknown, set.GetTritValue(1005));
  EXPECT_EQ(Unknown, set.GetTritValue(1006));
  EXPECT_EQ(Unknown, set.GetTritValue(1007));
  set[0] = True;
  set[15] = True;
  set[7] = True;
  set.TrimUintAfterTritInd(0);
  EXPECT_EQ(True, set[0].GetTritValue());
  EXPECT_EQ(Unknown, set.GetTritValue(15));
  EXPECT_EQ(Unknown, set.GetTritValue(7));
}
TEST(TritSetTest, GetUintIndWithLastTrit) {
  TritSet set(1000);
  EXPECT_EQ(0, set.GetUintIndWithLastTrit());
  set[0] = False;
  EXPECT_EQ(0, set.GetUintIndWithLastTrit());
  set[15] = False;
  EXPECT_EQ(0, set.GetUintIndWithLastTrit());
  set[1007] = False;
  EXPECT_EQ(62, set.GetUintIndWithLastTrit());
}
*/
TEST(TritSetTest, GetSize) {
  TritSet set(10);
  EXPECT_EQ(16, set.GetSize());
  set.Resize(17);
  EXPECT_EQ(32, set.GetSize());
}

TEST(TritSetTest, OverridedOperatorsEqAndTake) {
  TritSet set(10);
  EXPECT_EQ(Unknown, set[0].GetTritValue());
  set[0] = True;
  EXPECT_EQ(True, set[0].GetTritValue());
  set[0] = Unknown;
  EXPECT_EQ(Unknown, set[0].GetTritValue());
  set[0] = False;
  EXPECT_EQ(False, set[0].GetTritValue());
  set[1] = set[0];
  EXPECT_EQ(False, set[1].GetTritValue());
  set[1] = set[2];
  EXPECT_EQ(Unknown, set[1].GetTritValue());
  uint size_int_trits = set.GetSize();
  set[10000] = Unknown;
  EXPECT_EQ(size_int_trits, set.GetSize());
  set[10000] = set[3];
  EXPECT_EQ(size_int_trits, set.GetSize());
  set[100] = False;
  EXPECT_LT(size_int_trits, set.GetSize());
  size_int_trits = set.GetSize();
  set[100000] = set[100];
  EXPECT_LT(size_int_trits, set.GetSize());
}

TEST(TritSetTest, OverridedOperatorLogic) {
  TritSet set(10);
  EXPECT_EQ(Unknown, set[1].GetTritValue());
  set[1] = False & True;
  EXPECT_EQ(False, set[1].GetTritValue());
  set[1] = True & True;
  EXPECT_EQ(True, set[1].GetTritValue());
  set[1] = Unknown & True;
  EXPECT_EQ(Unknown, set[1].GetTritValue());
  set[1] = False & Unknown;
  EXPECT_EQ(False, set[1].GetTritValue());
  set[1] = False | Unknown;
  EXPECT_EQ(Unknown, set[1].GetTritValue());
  set[1] = Unknown | True;
  EXPECT_EQ(True, set[1].GetTritValue());
  set[1] = ~set[1];
  EXPECT_EQ(False, set[1].GetTritValue());
  set[1] = ~set[1];
  EXPECT_EQ(True, set[1].GetTritValue());
  set[1] = set[1] & set[0];
  EXPECT_EQ(Unknown, set[1].GetTritValue());
  set[20] = True;
  set[10] = Unknown;
  set[1] = False;
  TritSet set2(10);
  EXPECT_EQ(Unknown, set2[1].GetTritValue());
  set2[1] = False;
  EXPECT_EQ(False, set2[1].GetTritValue());
  TritSet set3 = set | set2;
  EXPECT_EQ(False, set3[1].GetTritValue());
  EXPECT_EQ(True, set3[20].GetTritValue());
  EXPECT_EQ(Unknown, set3[10].GetTritValue());
  EXPECT_EQ(32, set3.GetSize());
}

TEST(TritSetTest, ShrinkTest) {
  TritSet set(1000);
  EXPECT_EQ(1008, set.GetSize());
  set.Shrink();
  EXPECT_EQ(16, set.GetSize());
  set[1000] = True;
  EXPECT_EQ(1008, set.GetSize());
  set.Shrink();
  EXPECT_EQ(1008, set.GetSize());
}
TEST(TritSetTest, GetCountOfTritsWithType) {
  TritSet set(1000);
  EXPECT_EQ(0, set.GetCountOfTritsWithType(Unknown));
  set[1000] = True;
  EXPECT_EQ(1000, set.GetCountOfTritsWithType(Unknown));
  EXPECT_EQ(1, set.GetCountOfTritsWithType(True));
  EXPECT_EQ(0, set.GetCountOfTritsWithType(False));
  set[1000] = Unknown;
  unordered_map<Trit, uint> test = set.Cardinality();
  EXPECT_EQ(0, set.GetCountOfTritsWithType(False));
  EXPECT_EQ(0, set.GetCountOfTritsWithType(True));
  EXPECT_EQ(0, set.GetCountOfTritsWithType(Unknown));
  set[0] = True;
  set[500] = True;
  set[1007] = True;
  EXPECT_EQ(0, set.GetCountOfTritsWithType(False));
  EXPECT_EQ(3, set.GetCountOfTritsWithType(True));
  EXPECT_EQ(1005, set.GetCountOfTritsWithType(Unknown));
  set[500] = False;
  EXPECT_EQ(1, set.GetCountOfTritsWithType(False));
  EXPECT_EQ(2, set.GetCountOfTritsWithType(True));
  EXPECT_EQ(1005, set.GetCountOfTritsWithType(Unknown));
}

TEST(TritSetTest, GetLastSettedTritInd) {
  TritSet set(1000);
  set[15] = False;
  EXPECT_EQ(15, set.GetLastSettedTritInd());
  set[499] = True;
  EXPECT_EQ(499, set.GetLastSettedTritInd());
  set[0] = True;
  EXPECT_EQ(499, set.GetLastSettedTritInd());
  set[499] = False;
  EXPECT_EQ(499, set.GetLastSettedTritInd());
  set[500] = False;
  EXPECT_EQ(500, set.GetLastSettedTritInd());
  set[501] = True;
  EXPECT_EQ(501, set.GetLastSettedTritInd());
  set[501] = Unknown;
  EXPECT_EQ(500, set.GetLastSettedTritInd());
}
TEST(TritSetTest, Trim) {
  TritSet set(1000);
  uint size = set.GetSize();
  set[1004] = False;
  set[1005] = True;
  set[1006] = True;
  set[1007] = True;
  set.Trim(1004);
  EXPECT_EQ(False, set[1004].GetTritValue());
  EXPECT_EQ(Unknown, set[1005].GetTritValue());
  EXPECT_EQ(Unknown, set[1006].GetTritValue());
  EXPECT_EQ(Unknown, set[1007].GetTritValue());
  EXPECT_EQ(size, set.GetSize());
  set[15] = False;
  set.Trim(15);
  EXPECT_EQ(False, set[15].GetTritValue());
  EXPECT_EQ(set.GetSize(), 16);
}

TEST(TritSetTest, Cardinality) {
  TritSet set(1000);
  unordered_map<Trit, uint> test = set.Cardinality();
  EXPECT_EQ(0, test[False]);
  EXPECT_EQ(0, test[True]);
  EXPECT_EQ(0, test[Unknown]);
  set[0] = True;
  set[500] = True;
  set[1007] = True;
  test = set.Cardinality();
  EXPECT_EQ(0, test[False]);
  EXPECT_EQ(3, test[True]);
  EXPECT_EQ(1005, test[Unknown]);
  set[500] = False;
  test = set.Cardinality();
  EXPECT_EQ(1, test[False]);
  EXPECT_EQ(2, test[True]);
  EXPECT_EQ(1005, test[Unknown]);
}

TEST(TritSetTest, ostreamOperator) {
  TritSet set(1000);
  set[0] = False;
  set[2] = True;
  cout << set[0] << set[1] << set[2] << endl;
}