#include <iostream>
#include <nls/lock_client_interface.hpp>
#include <boost/shared_ptr.hpp>
#include <unistd.h>
using namespace std;

int main() {
for (int  i = 0; i < 3; ++i) {
	cout << "start" << endl;
	boost::shared_ptr<LockService::LockClientInterface> client(LockService::newLockClient());
	cout << "I am " << client->getEId() << endl;

	map<string, LockLib::LockTypes::LockType> query;
	query["res_1"] = LockLib::LockTypes::EX;

	boost::shared_ptr<LockService::LockQueryInterface> q(client->getLockQuery(query));

for (int k = 0; k < 10; ++k) {
	q->lock();

	//cout << "sleep 3" << endl;
	//sleep(3);

	q->unlock();

	cout << "done" << endl;
}
}
	return 0;
}
