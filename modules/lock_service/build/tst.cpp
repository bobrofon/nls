#include "../include/net_synchronize.hpp"
#include "../include/lock_client.hpp"
#include "../../../interfaces/utils/config_interface.hpp"
#include <iostream>

using namespace std;

int main() {
	LockService::NetSynchronize sync;

	cout << Config()->getStr("client.address") << std::endl;
	cout << sync.getEndpoint().address().to_string() << " " << sync.getEndpoint().port() << endl;
	sync.wait();
	cout << "done" << endl;

	LockService::LockClient client;
	cout << "ololo" << endl;

	return 0;
}
