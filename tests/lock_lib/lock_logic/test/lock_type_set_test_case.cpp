#include <gtest/gtest.h>
#include "lock_lib/lock_logic/lock_type_set.hpp"

using namespace LockLib::LockLogic;
using namespace LockLib::LockTypes;

TEST(LockTypeSet, construct) {
	const LockTypeSet constSet(PR);
	EXPECT_EQ(0, constSet[EX]);
	EXPECT_EQ(0, constSet[PW]);
	EXPECT_EQ(1, constSet[PR]);
	EXPECT_EQ(0, constSet[CW]);
	EXPECT_EQ(0, constSet[CR]);
	EXPECT_EQ(0, constSet[NL]);

	LockTypeSet set;
	set = NL;
	EXPECT_EQ(0, set[EX]);
	EXPECT_EQ(0, set[PW]);
	EXPECT_EQ(0, set[PR]);
	EXPECT_EQ(0, set[CW]);
	EXPECT_EQ(0, set[CR]);
	EXPECT_EQ(1, set[NL]);

	set[NL] = 0;
	set[CR] = 5;
	
	EXPECT_EQ(0, set[EX]);
	EXPECT_EQ(0, set[PW]);
	EXPECT_EQ(0, set[PR]);
	EXPECT_EQ(0, set[CW]);
	EXPECT_EQ(5, set[CR]);
	EXPECT_EQ(0, set[NL]);	
}

TEST(LockTypeSet, operators) {
	LockTypeSet set1;
	set1[EX] = 1;
	set1[PW] = 2;
	set1[PR] = 3;
	set1[CW] = 4;
	set1[CR] = 5;
	set1[NL] = 6;

	LockTypeSet set2;
	set2[EX] = 0;
	set2[PW] = 1;
	set2[PR] = 0;
	set2[CW] = 2;
	set2[CR] = 0;
	set2[NL] = 3;

	LockTypeSet set3 = set1 + set2;
	EXPECT_EQ(1, set3[EX]);
	EXPECT_EQ(3, set3[PW]);
	EXPECT_EQ(3, set3[PR]);
	EXPECT_EQ(6, set3[CW]);
	EXPECT_EQ(5, set3[CR]);
	EXPECT_EQ(9, set3[NL]);

	set3 = set1 - set2;
	EXPECT_EQ(1, set3[EX]);
	EXPECT_EQ(1, set3[PW]);
	EXPECT_EQ(3, set3[PR]);
	EXPECT_EQ(2, set3[CW]);
	EXPECT_EQ(5, set3[CR]);
	EXPECT_EQ(3, set3[NL]);
}

TEST(LockTypeSet, empty_clear) {
	LockTypeSet set;
	set[EX] = 1;
	set[PW] = 2;
	set[PR] = 3;
	set[CW] = 4;
	set[CR] = 5;
	set[NL] = 6;

	EXPECT_FALSE(set.empty());
	set.clear();
	EXPECT_TRUE(set.empty());
}

TEST(LockTypeSet, compatible) {
	LockTypeSet set1;
	set1 += CR;
	set1 += CW;

	LockTypeSet set2;
	set2 += CW;
	set2 += PR;

	EXPECT_FALSE(LockTypeSet::compatible(set1, set2));
	set1 -= CW;
	EXPECT_TRUE(LockTypeSet::compatible(set1, set2));
}
