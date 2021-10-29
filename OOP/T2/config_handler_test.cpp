#include "config_handler.h"

#include "gtest/gtest.h"

TEST(ConfigHandler, bad_input_file_name) {
  EXPECT_THROW(ConfigHandler tset("blalba.txt"), std::invalid_argument);
}

TEST(ConfigHandler, LineBlockSyntaxTest) {
  ConfigHandler handler;

  std::string test = "    desc    ";
  EXPECT_NO_THROW(handler.BlockLineSyntaxCheck(test, 0));

  std::string test = "    desc    a";
  EXPECT_THROW(handler.BlockLineSyntaxCheck(test, 0), BlockBeginningException);

  std::string test = "1 = wer afs";
  EXPECT_NO_THROW(handler.BlockLineSyntaxCheck(test, 0));

  std::string test = "    3f = 43";
  EXPECT_THROW(handler.BlockLineSyntaxCheck(test, 0), BlockBeginningException);
}
