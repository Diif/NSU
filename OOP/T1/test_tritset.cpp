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
  set.SetSize(17);
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
  unsigned int max = kTritsInUint * 2;
  for (size_t i = 0; i < max; i++) {
    set.SetTritValue(i, False);
    EXPECT_EQ(False, set.GetTritValue(i));
    set.SetTritValue(i, Unknown);
    EXPECT_EQ(Unknown, set.GetTritValue(i));
    set.SetTritValue(i, True);
    EXPECT_EQ(True, set.GetTritValue(i));
  }
  EXPECT_EQ(Unknown, set.GetTritValue(1000));
}
