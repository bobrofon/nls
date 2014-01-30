#include <gtest/gtest.h>
#include "lock_types_def.hpp"

namespace {

using namespace LockLib::LockTypes;

TEST(LockType, validLockType) {
	EXPECT_TRUE(validLockType(EX));
	EXPECT_TRUE(validLockType(PW));
	EXPECT_TRUE(validLockType(PR));
	EXPECT_TRUE(validLockType(CW));
	EXPECT_TRUE(validLockType(CR));
	EXPECT_TRUE(validLockType(NL));
	EXPECT_FALSE(validLockType(COUNT));
	EXPECT_FALSE(validLockType(static_cast<LockType> (-1)));
}

TEST(LockType, typeToString) {
	EXPECT_STREQ("EX", typeToString(EX));
	EXPECT_STREQ("PW", typeToString(PW));
	EXPECT_STREQ("PR", typeToString(PR));
	EXPECT_STREQ("CW", typeToString(CW));
	EXPECT_STREQ("CR", typeToString(CR));
	EXPECT_STREQ("NL", typeToString(NL));
	EXPECT_STREQ("UNDEFINED", typeToString(COUNT));
	EXPECT_STREQ("UNDEFINED", typeToString(static_cast<LockType> (-1)));
}

TEST(LockType, stringToType) {
	EXPECT_EQ(EX, stringToType("EX"));
	EXPECT_EQ(PW, stringToType("PW"));
	EXPECT_EQ(PR, stringToType("PR"));
	EXPECT_EQ(CW, stringToType("CW"));
	EXPECT_EQ(CR, stringToType("CR"));
	EXPECT_EQ(NL, stringToType("NL"));
	EXPECT_FALSE(validLockType(stringToType("OLOLO")));
}

}
