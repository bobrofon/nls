#include "lock_query.hpp"
#include "lock_lib/lock_logic/lock_type_set.hpp"

using namespace std;
using namespace boost;
using namespace LockLib::LockTypes;
using namespace LockLib::LockLogic;
using namespace soci;

namespace LockService {

LockQuery::LockQuery(
		int _eid,
		map<string, LockType> _resources,
		shared_ptr<NetSynchronize> _sync,
		shared_ptr<session> _db)
		: m_db(_db),
		  m_sync(_sync),
		  m_resources(_resources),
		  m_eid(_eid) {}

LockQuery::~LockQuery() {}

void LockQuery::lock() {
	for (map<string, LockType>::iterator it = m_resources.begin(); it != m_resources.end(); ++it) {
		//*m_db << "insert into waiting(client_id"
		for (;;) {
			transaction tr(*m_db);
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

			bool update = m_db->got_data();

			LockTypeSet otherSet;
			*m_db << "select ex, pw, pr, cw, cr, nl from resources where eid != :eid and name = :name",
			use(m_eid, "eid"),
			use(it->first, "name"),
			into(otherSet[EX]),
			into(otherSet[PW]),
			into(otherSet[PR]),
			into(otherSet[CW]),
			into(otherSet[CR]),
			into(otherSet[NL]);

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
		}
	}
}

bool LockQuery::tryLock() {
	return false;
}

bool LockQuery::timedLock(time_t /*_time*/) {
	return false;
}

void LockQuery::unlock() {

}

} /* namespace LockService */
