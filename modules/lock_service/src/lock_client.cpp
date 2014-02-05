#include "lock_client.hpp"
#include "utils/config_interface.hpp"
#include <boost/make_shared.hpp>
#include "lock_query.hpp"

#include <soci/mysql/soci-mysql.h> // stub

using namespace soci;
using namespace boost;
using namespace LockLib::LockLogic;

namespace LockService {

LockClient::LockClient() {
	m_sync.reset(new NetSynchronize());
	m_clientInfo = make_shared<ClientInfo>(0, m_sync->getEndpoint());

	m_clientInfo->setEndpoint(m_sync->getEndpoint());
	m_db.reset(new session());
	m_db->open(mysql, Config()->getStr("db.address"));
	registerClient();
}

LockClient::LockClient(int _eid) {
	m_clientInfo->setEndpoint(m_sync->getEndpoint());
	m_db->open(mysql, Config()->getStr("db.address"));
	registerClient(_eid);
}

LockClient::~LockClient() {
	*m_db << "delete from clients where id = :id", use(m_clientInfo->getId());
	m_db->close();
}

int LockClient::getEId() const {
	return m_clientInfo->getEId();
}

LockQueryInterface *LockClient::getLockQuery(const query_t &_query) {
	return new LockQuery(m_clientInfo->getId(), m_clientInfo->getEId(), _query, m_sync, m_db);
}

void LockClient::registerClient() {
	*m_db << "insert into clients(address, port) values(:address, :port)",
		use(m_clientInfo->getEndpoint().address().to_string(), "address"), 
		use(static_cast<int> (m_clientInfo->getEndpoint().port()), "port");

	int id = 0;
	*m_db << "select id from clients where address = :address and port = :port",
		use(m_clientInfo->getEndpoint().address().to_string(), "address"),
		use(static_cast<int> (m_clientInfo->getEndpoint().port()), "port"),
		into(id);
	m_clientInfo = make_shared<ClientInfo>(id, id, m_clientInfo->getEndpoint());
	*m_db << "update clients set eid = :eid where id = :id",
		use(m_clientInfo->getEId(), "eid"),
		use(m_clientInfo->getId(), "id");
}

void LockClient::registerClient(int _eid) {
	*m_db << "insert into clients(eid, address, port) values(:eid :address, :port)",
		use(_eid, "eid"),
		use(m_clientInfo->getEndpoint().address().to_string(), "address"), 
		use(static_cast<int> (m_clientInfo->getEndpoint().port()), "port");

	int id = 0;
	use(m_clientInfo->getEndpoint().address().to_string(), "address"),
	use(static_cast<int> (m_clientInfo->getEndpoint().port()), "port"),
	into(id);
	m_clientInfo = make_shared<ClientInfo>(id, _eid, m_clientInfo->getEndpoint());
}

LockClientInterface *newLockClient() {
	return new LockClient();
}

LockClientInterface *newLockClient(int _eid) {
	return new LockClient(_eid);
}

} /* namespace LockService */
