#ifndef LOCK_CLIENT_INTERFACE_HPP_
#define LOCK_CLIENT_INTERFACE_HPP_

#include <string>
#include <map>
#include "lock_query_interface.hpp"
#include "lock_lib/lock_types/lock_types_def.hpp"

namespace LockService {

typedef std::map<std::string, LockLib::LockTypes::LockType> query_t;

class LockClientInterface {
public:
	virtual ~LockClientInterface() {}
	virtual int getEId() const = 0;
	virtual LockQueryInterface *getLockQuery(const query_t &_query) = 0;
};

LockClientInterface *newLockClient();
LockClientInterface *newLockClient(int _eid);

} /* namespace LockService */

#endif /* LOCK_CLIENT_INTERFACE_HPP_ */
