#include "tritset.h"

#include "gtest/gtest.h"

TEST(tritset_test, operator_and) {
  EXPECT_EQ(False, False & Unknown);
  EXPECT_EQ(True, True & True);
  EXPECT_EQ(Unknown, Unknown & True);
}

TEST(tritset_test, operator_or) {
  EXPECT_EQ(Unknown, False | Unknown);
  EXPECT_EQ(True, True | False);
  EXPECT_EQ(False, False | False);
}

TEST(tritset_test, operator_not) {
  EXPECT_EQ(Unknown, ~Unknown);
  EXPECT_EQ(True, ~False);
  EXPECT_EQ(False, ~True);
}

TEST(tritset_test, Tritset) {
  Tritset tritset1(100);
  int real_size_in_trit =
      (Tritset::convert_trit_index_to_int_index(100 - 1) + 1) *
      count_trit_in_int;
  EXPECT_EQ(real_size_in_trit, tritset1.get_size_in_trit());

  Tritset tritset2(16);
  real_size_in_trit = (Tritset::convert_trit_index_to_int_index(16 - 1) + 1) *
                      count_trit_in_int;
  EXPECT_EQ(real_size_in_trit, tritset2.get_size_in_trit());
  Tritset tritset3(31);
  real_size_in_trit = (Tritset::convert_trit_index_to_int_index(31 - 1) + 1) *
                      count_trit_in_int;
  EXPECT_EQ(real_size_in_trit, tritset3.get_size_in_trit());
}

TEST(triset_test, operator_index) {
  Tritset tritset(100);
  EXPECT_EQ(Unknown, static_cast<Trit>(tritset[0]));
  EXPECT_EQ(Unknown, static_cast<Trit>(tritset[15]));
  EXPECT_EQ(Unknown, static_cast<Trit>(tritset[16]));
}

TEST(tritset_test, operator_eq) {
  Tritset tritset(100);
  tritset[0] = True;
  EXPECT_EQ(True, static_cast<Trit>(tritset[0]));
  tritset[100] = False;
  EXPECT_EQ(False, static_cast<Trit>(tritset[100]));
  tritset[100] = tritset[0];
  EXPECT_EQ(True, static_cast<Trit>(tritset[100]));
  tritset[16] = tritset[100];
  EXPECT_EQ(True, static_cast<Trit>(tritset[16]));
  Trit trit = Unknown;
  trit = tritset[16];
  EXPECT_EQ(True, trit);
  tritset[15] = trit = False;
  EXPECT_EQ(False, static_cast<Trit>(tritset[15]));
}

TEST(tritset_test, resize_vector) {
  Tritset tritset(1000);
  int size;
  tritset[1009] = True;
  size = tritset.get_size_in_trit();
  int real_size_in_trit =
      (Tritset::convert_trit_index_to_int_index(1009 - 1) + 1) *
      count_trit_in_int;
  EXPECT_EQ(real_size_in_trit, size);

  Tritset tritset2(1000);
  int size_before = tritset2.get_size_in_trit();
  tritset2[1009] = tritset2[10000];
  int size_after = tritset2.get_size_in_trit();
  EXPECT_EQ(size_before, size_after);

  Tritset tritset3(1000);
  size_before = tritset3.get_size_in_trit();
  tritset3[1009] = Unknown;
  size_after = tritset3.get_size_in_trit();
  EXPECT_EQ(size_before, size_after);

  Tritset tritset4(100);
  tritset4[1000] = False;
  tritset4[10001] = tritset4[1000];
  real_size_in_trit =
      (Tritset::convert_trit_index_to_int_index(10001 - 1) + 1) *
      count_trit_in_int;
  size_after = tritset4.get_size_in_trit();
  EXPECT_EQ(real_size_in_trit, size_after);
}

TEST(tritset_test, shrink) {
  Tritset tritset(1000);
  int size =
      (Tritset::convert_trit_index_to_int_index(100) + 1) * count_trit_in_int;
  tritset[100] = True;
  tritset.shrink();
  int size_in_trit_after = tritset.get_size_in_trit();
  EXPECT_EQ(size, size_in_trit_after);

  Tritset tritset2(1000);
  int size_in_trit_before = tritset2.get_size_in_trit();
  tritset2.shrink();
  size_in_trit_after = tritset2.get_size_in_trit();
  EXPECT_EQ(size_in_trit_before, size_in_trit_after);

  Tritset tritset3(1000);
  size_in_trit_before = tritset3.get_size_in_trit();
  tritset3[100] = True;
  tritset3.shrink();
  tritset3[100] = Unknown;
  tritset3.shrink();
  size_in_trit_after = tritset3.get_size_in_trit();
  EXPECT_EQ(size_in_trit_before, size_in_trit_after);
}

TEST(tritset_test, cardinality) {
  Tritset tritset(100);
  tritset[100] = True;
  tritset[110] = False;
  tritset[1] = True;
  tritset[100] = False;
  EXPECT_EQ(1, tritset.cardinality(True));
  EXPECT_EQ(2, tritset.cardinality(False));
  EXPECT_EQ(109, tritset.cardinality(Unknown));
}

TEST(tritset_test, trim) {
  Tritset tritset(100);
  tritset[20] = True;
  tritset.trim(5);
  int size =
      (Tritset::convert_trit_index_to_int_index(5) + 1) * count_trit_in_int;
  EXPECT_EQ(size, tritset.get_size_in_trit());

  size = (Tritset::convert_trit_index_to_int_index(5) + 1) * count_trit_in_int;
  tritset.trim(50);
  EXPECT_EQ(size, tritset.get_size_in_trit());

  tritset[100] = True;
  size =
      (Tritset::convert_trit_index_to_int_index(100) + 1) * count_trit_in_int;
  EXPECT_EQ(size, tritset.get_size_in_trit());
}

TEST(tritset_test, lenght) {
  Tritset tritset(100);
  tritset[20] = True;
  size_t lenght = tritset.length();
  EXPECT_EQ(21, lenght);

  tritset[1000] = True;
  lenght = tritset.length();
  EXPECT_EQ(1001, lenght);
}
