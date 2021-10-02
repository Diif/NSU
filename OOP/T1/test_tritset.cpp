#include "gtest/gtest.h"
#include "tritset.h"
// for 4-byte uint, 64-bit OS

// move out of private to test

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

TEST(TritSetTest, GetSize) {
  TritSet set(10);
  EXPECT_EQ(16, set.GetSize());
  set.Resize(17);
  EXPECT_EQ(32, set.GetSize());
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
  EXPECT_EQ(True, set.GetTritValue(0));

  set.SetTritValue(0, Unknown);
  EXPECT_EQ(Unknown, set.GetTritValue(0));
  set.SetTritValue(0, False);
  EXPECT_EQ(False, set.GetTritValue(0));
  set.SetTritValue(0, True);
  EXPECT_EQ(True, set.GetTritValue(0));

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

TEST(TritSetTest, OverridedOperatorsEqAndTake) {
  TritSet set(10);
  EXPECT_EQ(Unknown, set.GetTritValue(0));
  set[0] = True;
  EXPECT_EQ(True, set.GetTritValue(0));
  set[0] = Unknown;
  EXPECT_EQ(Unknown, set.GetTritValue(0));
  set[0] = False;
  EXPECT_EQ(False, set.GetTritValue(0));
  set[1] = set[0];
  EXPECT_EQ(False, set.GetTritValue(1));
  set[1] = set[2];
  EXPECT_EQ(Unknown, set.GetTritValue(1));
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
  EXPECT_EQ(Unknown, set.GetTritValue(1));
  set[1] = False & True;
  EXPECT_EQ(False, set.GetTritValue(1));
  set[1] = True & True;
  EXPECT_EQ(True, set.GetTritValue(1));
  set[1] = Unknown & True;
  EXPECT_EQ(Unknown, set.GetTritValue(1));
  set[1] = False & Unknown;
  EXPECT_EQ(False, set.GetTritValue(1));
  set[1] = False | Unknown;
  EXPECT_EQ(Unknown, set.GetTritValue(1));
  set[1] = Unknown | True;
  EXPECT_EQ(True, set.GetTritValue(1));
  set[1] = ~set[1];
  EXPECT_EQ(False, set.GetTritValue(1));
  set[1] = ~set[1];
  EXPECT_EQ(True, set.GetTritValue(1));
  set[1] = set[1] & set[0];
  EXPECT_EQ(Unknown, set.GetTritValue(1));
  set[20] = True;
  set[10] = Unknown;
  set[1] = False;
  TritSet set2(10);
  EXPECT_EQ(Unknown, set2.GetTritValue(1));
  set2[1] = False;
  EXPECT_EQ(False, set2.GetTritValue(1));
  TritSet &set3 = set | set2;
  EXPECT_EQ(False, set3.GetTritValue(1));
  EXPECT_EQ(True, set3.GetTritValue(20));
  EXPECT_EQ(Unknown, set3.GetTritValue(10));
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
TEST(TritSetTest, GetTritsWithType) {
  TritSet set(1000);
  EXPECT_EQ(0, set.GetCountOfTritsWithType(Unknown));
  set[1000] = True;
  EXPECT_EQ(1000, set.GetCountOfTritsWithType(Unknown));
  EXPECT_EQ(1, set.GetCountOfTritsWithType(True));
  EXPECT_EQ(0, set.GetCountOfTritsWithType(False));
}