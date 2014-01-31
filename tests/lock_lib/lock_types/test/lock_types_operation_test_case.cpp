#include <gtest/gtest.h>
#include "lock_types_operation.hpp"

namespace {

using namespace LockLib::LockTypes;

TEST(LockTypeTest, compatible) {
	EXPECT_TRUE(compatible(EX, NL));
	EXPECT_TRUE(compatible(PW, CR));
	EXPECT_TRUE(compatible(PW, NL));
	EXPECT_TRUE(compatible(PR, PR));
	EXPECT_TRUE(compatible(PR, CR));
	EXPECT_TRUE(compatible(PR, NL));
	EXPECT_TRUE(compatible(CW, CW));
	EXPECT_TRUE(compatible(CW, CR));
	EXPECT_TRUE(compatible(CW, NL));
	EXPECT_TRUE(compatible(CR, PW));
	EXPECT_TRUE(compatible(CR, PR));
	EXPECT_TRUE(compatible(CR, CW));
	EXPECT_TRUE(compatible(CR, CR));
	EXPECT_TRUE(compatible(CR, NL));
	EXPECT_TRUE(compatible(NL, EX));
	EXPECT_TRUE(compatible(NL, PW));
	EXPECT_TRUE(compatible(NL, PR));
	EXPECT_TRUE(compatible(NL, CW));
	EXPECT_TRUE(compatible(NL, CR));
	EXPECT_TRUE(compatible(NL, NL));

	EXPECT_FALSE(compatible(EX, EX));
	EXPECT_FALSE(compatible(EX, PW));
	EXPECT_FALSE(compatible(EX, PR));
	EXPECT_FALSE(compatible(EX, CW));
	EXPECT_FALSE(compatible(EX, CR));
	EXPECT_FALSE(compatible(PW, EX));
	EXPECT_FALSE(compatible(PW, PW));
	EXPECT_FALSE(compatible(PW, PR));
	EXPECT_FALSE(compatible(PW, CW));
	EXPECT_FALSE(compatible(PR, EX));
	EXPECT_FALSE(compatible(PR, PW));
	EXPECT_FALSE(compatible(PR, CW));
	EXPECT_FALSE(compatible(CW, EX));
	EXPECT_FALSE(compatible(CW, PW));
	EXPECT_FALSE(compatible(CW, PR));
	EXPECT_FALSE(compatible(CR, EX));
}

TEST(LockTypeTest, typeSum) {
	EXPECT_EQ(EX, EX+EX);
	EXPECT_EQ(EX, EX+PW);
	EXPECT_EQ(EX, EX+PR);
	EXPECT_EQ(EX, EX+CW);
	EXPECT_EQ(EX, EX+CR);
	EXPECT_EQ(EX, EX+NL);
	EXPECT_EQ(EX, PW+EX);
	EXPECT_EQ(PW, PW+PW);
	EXPECT_EQ(PW, PW+PR);
	EXPECT_EQ(PW, PW+CW);
	EXPECT_EQ(PW, PW+CR);
	EXPECT_EQ(PW, PW+NL);
	EXPECT_EQ(EX, PR+EX);
	EXPECT_EQ(PW, PR+PW);
	EXPECT_EQ(PR, PR+PR);
	EXPECT_EQ(PW, PR+CW);
	EXPECT_EQ(PR, PR+CR);
	EXPECT_EQ(PR, PR+NL);
	EXPECT_EQ(EX, CW+EX);
	EXPECT_EQ(PW, CW+PW);
	EXPECT_EQ(PW, CW+PR);
	EXPECT_EQ(CW, CW+CW);
	EXPECT_EQ(CW, CW+CR);
	EXPECT_EQ(CW, CW+NL);
	EXPECT_EQ(EX, CR+EX);
	EXPECT_EQ(PW, CR+PW);
	EXPECT_EQ(PR, CR+PR);
	EXPECT_EQ(CW, CR+CW);
	EXPECT_EQ(CR, CR+CR);
	EXPECT_EQ(CR, CR+NL);
	EXPECT_EQ(EX, NL+EX);
	EXPECT_EQ(PW, NL+PW);
	EXPECT_EQ(PR, NL+PR);
	EXPECT_EQ(CW, NL+CW);
	EXPECT_EQ(CR, NL+CR);
	EXPECT_EQ(NL, NL+NL);
}

TEST(LockTypeTest, increment) {
	EXPECT_EQ(PW, EX++);
	EXPECT_EQ(PR, PW++);
	EXPECT_EQ(CW, PR++);
	EXPECT_EQ(CR, CW++);
	EXPECT_EQ(NL, CR++);
	EXPECT_EQ(COUNT, NL++);
	EXPECT_EQ(COUNT, COUNT++);
}

}
