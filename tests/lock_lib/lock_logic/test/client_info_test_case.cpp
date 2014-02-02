#include <gtest/gtest.h>
#include "lock_lib/lock_logic/client_info.hpp"

using namespace LockLib::LockLogic;

TEST(ClientInfo, all) {
	ClientInfo client1(1, 2, endpoint_t());
	ClientInfo client2(3, endpoint_t());

	EXPECT_EQ(3, client2.getEId());
	EXPECT_EQ(3, client2.getId());

	client1.setEId(client2.getEId());
	client1.setEndpoint(client2.getEndpoint());
	EXPECT_EQ(3, client1.getEId());
	EXPECT_EQ(1, client1.getId());

	client1 = client2;
	EXPECT_EQ(3, client1.getEId());
	EXPECT_EQ(3, client1.getId());
}
