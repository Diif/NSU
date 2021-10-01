#include "gtest/gtest.h"
#include "tritset.h"

int main(int argc, char** argv) {
  // ::testing::InitGoogleTest(&argc, argv);
  // return RUN_ALL_TESTS();
  TritSet set1(10);
  TritSet set2(20);
  cout << &set1 << endl;
  cout << &set2 << endl;
  set1[1] = True;
  set2[3] = True;
  set1 = set1 | set2;
  cout << &set1 << endl;
}
