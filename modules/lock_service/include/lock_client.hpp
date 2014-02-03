#ifndef LOCK_CLIENT_HPP_
#define LOCK_CLIENT_HPP_

#include <soci/soci.h>
#include <boost/shared_ptr.hpp>
#include <lock_lib/lock_logic/client_info.hpp>
#include "lock_service/lock_client_interface.hpp"
#include "net_synchronize.hpp"

namespace LockService {

class LockClient : public LockClientInterface {
public:
	LockClient();
	LockClient(int _eid);
	virtual ~LockClient();

	virtual int getEId() const;
	virtual LockQueryInterface *getLockQuery(const query_t &_query);

private:
	void registerClient();
	void registerClient(int _eid);

	NetSynchronize m_sync;
	soci::session m_db;
	boost::shared_ptr<LockLib::LockLogic::ClientInfo> m_clientInfo;
};

} /* namespace LockService */

#endif /* LOCK_CLIENT_HPP_ */
