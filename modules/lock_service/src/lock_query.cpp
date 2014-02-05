#include "lock_query.hpp"
#include "lock_lib/lock_logic/lock_type_set.hpp"
#include <vector>
#include <boost/asio.hpp>

using namespace std;
using namespace boost;
using namespace LockLib::LockTypes;
using namespace LockLib::LockLogic;
using namespace soci;

namespace LockService {

LockQuery::LockQuery(
		int _id,
		int _eid,
		map<string, LockType> _resources,
		shared_ptr<NetSynchronize> _sync,
		shared_ptr<session> _db)
		: m_db(_db),
		  m_sync(_sync),
		  m_resources(_resources),
		  m_eid(_eid),
		  m_id(_id) {}

LockQuery::~LockQuery() {}

void LockQuery::lock() {
	for (map<string, LockType>::iterator it = m_resources.begin(); it != m_resources.end(); ++it) {
		*m_db << "insert into waiting(client_id, name) values(:id, :name)",
			use(m_id, "id"),
			use(it->first, "name");

		for (;;) {
			try {
				transaction tr(*m_db);
				LockTypeSet mySet;
				*m_db << "select ex, pw, pr, cw, cr, nl from resources where eid = :eid and name = :name for update",
				use(m_eid, "eid"),
				use(it->first, "name"),
				into(mySet[EX]),
				into(mySet[PW]),
				into(mySet[PR]),
				into(mySet[CW]),
				into(mySet[CR]),
				into(mySet[NL]);

				bool update = m_db->got_data();

				LockTypeSet otherSet;
				*m_db << "select ifnull(sum(ex), 0), ifnull(sum(pw), 0), ifnull(sum(pr), 0), ifnull(sum(cw), 0), ifnull(sum(cr), 0), ifnull(sum(nl), 0) from resources where eid != :eid and name = :name for update",
				use(m_eid, "eid"),
				use(it->first, "name"),
				into(otherSet[EX]),
				into(otherSet[PW]),
				into(otherSet[PR]),
				into(otherSet[CW]),
				into(otherSet[CR]),
				into(otherSet[NL]);

				if (!m_db->got_data()) {
					continue;
				}

				mySet += it->second;
				if (LockTypeSet::compatible(mySet, otherSet)) {
					if (update) {
						*m_db << "update resources set ex = :ex, pw = :pw, pr = :pr, cw = :cw, cr = :cr, nl = :nl where eid = :eid and name = :name",
							use(m_eid, "eid"),
							use(it->first, "name"),
							use(mySet[EX], "ex"),
							use(mySet[PW], "pw"),
							use(mySet[PR], "pr"),
							use(mySet[CW], "cw"),
							use(mySet[CR], "cr"),
							use(mySet[NL], "nl");
					} else {
						*m_db << "insert into resources(eid, name, ex, pw, pr, cw, cr, nl) values(:eid, :name, :ex, :pw, :pr, :cw, :cr, :nl)",
							use(m_eid, "eid"),
							use(it->first, "name"),
							use(mySet[EX], "ex"),
							use(mySet[PW], "pw"),
							use(mySet[PR], "pr"),
							use(mySet[CW], "cw"),
							use(mySet[CR], "cr"),
							use(mySet[NL], "nl");
					}
					tr.commit();
					break;
				} else {
					tr.rollback();
					m_sync->wait();
				}
			} catch (...) {}
		}
		*m_db << "delete from waiting where client_id = :id and name = :name",
			use(m_id, "id"),
			use(it->first, "name");
	}
}

bool LockQuery::tryLock() {
	return false;
}

bool LockQuery::timedLock(time_t /*_time*/) {
	return false;
}

void LockQuery::unlock() {
	for (map<string, LockType>::iterator it = m_resources.begin(); it != m_resources.end(); ++it) {
		LockTypeSet mySet;
			*m_db << "select ex, pw, pr, cw, cr, nl from resources where eid = :eid and name = :name",
			use(m_eid, "eid"),
			use(it->first, "name"),
			into(mySet[EX]),
			into(mySet[PW]),
			into(mySet[PR]),
			into(mySet[CW]),
			into(mySet[CR]),
			into(mySet[NL]);

		mySet -= it->second;
		*m_db << "update resources set ex = :ex, pw = :pw, pr = :pr, cw = :cw, cr = :cr, nl = :nl where eid = :eid and name = :name",
			use(m_eid, "eid"),
			use(it->first, "name"),
			use(mySet[EX], "ex"),
			use(mySet[PW], "pw"),
			use(mySet[PR], "pr"),
			use(mySet[CW], "cw"),
			use(mySet[CR], "cr"),
			use(mySet[NL], "nl");

			vector<string> address(100);
			vector<int> port(100);
			*m_db << "select address, port from clients join waiting on clients.id = waiting.client_id where name = :name",
				use(it->first), into(address), into(port);
			for (size_t i = 0; i < address.size(); ++i) {
				asio::ip::tcp::endpoint endpoint;
				endpoint.address(asio::ip::address::from_string(address[i]));
				endpoint.port(port[i]);
				m_sync->notify(endpoint);
			}
	}
}

} /* namespace LockService */
