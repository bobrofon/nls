#include "lock_client.hpp"
#include "utils/config_interface.hpp"
#include <boost/make_shared.hpp>

#include <soci/sqlite3/soci-sqlite3.h> // stub

using namespace soci;
using namespace boost;
using namespace LockLib::LockLogic;

namespace LockService {

LockClient::LockClient() {
	m_clientInfo = make_shared<ClientInfo>(0, m_sync.getEndpoint());

	m_clientInfo->setEndpoint(m_sync.getEndpoint());
	m_db.open(sqlite3, Config()->getStr("db.address"));
	registerClient();
}

LockClient::LockClient(int _eid) {
	m_clientInfo->setEndpoint(m_sync.getEndpoint());
	m_db.open(sqlite3, Config()->getStr("db.address"));
	registerClient(_eid);
}

LockClient::~LockClient() {
	m_db.close();
}

int LockClient::getEId() const {
	return m_clientInfo->getEId();
}

LockQueryInterface *LockClient::getLockQuery(const query_t &/*_query*/) {
	return NULL;
}

void LockClient::registerClient() {
	m_db << "insert into clients(address, port) values(:address, :port)",
		use(m_clientInfo->getEndpoint().address().to_string(), "address"), 
		use(static_cast<int> (m_clientInfo->getEndpoint().port()), "port");

	int id = 0;
	m_db << "select last_insert_rowid()", into(id);
	m_clientInfo = make_shared<ClientInfo>(id, id, m_clientInfo->getEndpoint());
	m_db << "update clients set eid = :eid where id = :id", use(m_clientInfo->getEId(), "eid"), use(m_clientInfo->getId(), "id");
}

void LockClient::registerClient(int /*_eid*/) {}

} /* namespace LockService */
