#include <gtest/gtest.h>
#include <sstream>
#include "lock_types_io.hpp"

namespace {

using namespace LockLib::LockTypes;
using namespace std;

TEST(LockTypeTest, io) {	
	stringstream stream;
	LockType type;

	stream << EX;
	stream >> type;
	EXPECT_EQ(EX, type);

	stream.clear();
	stream << PW;
	stream >> type;
	EXPECT_EQ(PW, type);

	stream.clear();
	stream << PR;
	stream >> type;
	EXPECT_EQ(PR, type);

	stream.clear();
	stream << CW;
	stream >> type;
	EXPECT_EQ(CW, type);

	stream.clear();
	stream << CR;
	stream >> type;
	EXPECT_EQ(CR, type);

	stream.clear();
	stream << NL;
	stream >> type;
	EXPECT_EQ(NL, type);
}

}
