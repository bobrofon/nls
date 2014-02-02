#ifndef LOCK_QUERY_INTERFACE_HPP_
#define LOCK_QUERY_INTERFACE_HPP_

#include <ctime>

namespace LockService {

class LockQueryInterface {
public:
	virtual ~LockQueryInterface() {}
	virtual void lock() = 0;
	virtual bool tryLock() = 0;
	virtual bool timedLock(time_t _time) = 0;
	virtual void unlock() = 0;
};

} /* namespace LockService */

#endif /* LOCK_QUERY_INTERFACE_HPP_ */
