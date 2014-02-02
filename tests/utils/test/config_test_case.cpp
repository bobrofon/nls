#include <gtest/gtest.h>
#include "utils/config_interface.hpp"

TEST(Config, all) {
	EXPECT_EQ(1, Config()->getInt("test.one"));
	EXPECT_EQ("two", Config()->getStr("test.two"));
}
