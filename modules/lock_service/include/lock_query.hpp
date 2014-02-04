#ifndef LOCK_QUERY_HPP_
#define LOCK_QUERY_HPP_

#include "lock_service/lock_query_interface.hpp"
#include "lock_lib/lock_types/lock_types_def.hpp"
#include <boost/shared_ptr.hpp>
#include <map>
#include <string>
#include "net_synchronize.hpp"
#include <soci/soci.h>

namespace LockService {

class LockQuery : public LockQueryInterface {
public:
	LockQuery(
			int _eid,
			std::map<std::string, LockLib::LockTypes::LockType> _resources,
			boost::shared_ptr<NetSynchronize> _sync,
			boost::shared_ptr<soci::session> _db);
	virtual ~LockQuery();
	virtual void lock();
	virtual bool tryLock();
	virtual bool timedLock(time_t _time);
	virtual void unlock();

private:
	boost::shared_ptr<soci::session> m_db;
	boost::shared_ptr<NetSynchronize> m_sync;
	std::map<std::string, LockLib::LockTypes::LockType> m_resources;
	int m_eid;
};

} /* namespace LockService */

#endif /* LOCK_QUERY_HPP_ */
