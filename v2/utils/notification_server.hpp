#ifndef NOTIFICATION_SERVER_HPP_
#define NOTIFICATION_SERVER_HPP_

#include <vector>
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <chrono>
#include <utility>
#include "address.hpp"

namespace nls {

class NotificationServer {
public:
	explicit inline NotificationServer(const Address& _address);
	explicit inline NotificationServer(Address&& _address);

	inline Address address() const noexcept;
	inline void wait();
	inline bool timedWait(const std::chrono::milliseconds& _timeout);
	inline void clear();

	virtual void notify(const Address& _server) = 0;
	virtual void notifyAll(const std::vector<Address>& _servers) = 0;
	virtual ~NotificationServer();

protected:
	inline void notify();

private:
	Address m_address;
	std::atomic_flag m_wating = ATOMIC_FLAG_INIT;
	std::mutex m_monitor;
	std::condition_variable m_condition;
};

} /* namespace nls */

////////////////////////////////////////////////////////////////////////////////////////////////////

namespace nls {

inline NotificationServer::NotificationServer(const Address& _address) : m_address(_address) {
	m_wating.test_and_set();
}

inline NotificationServer::NotificationServer(Address&& _address) : m_address(std::forward<Address>(_address)) {
	m_wating.test_and_set();
}

inline Address NotificationServer::address() const noexcept {
	return m_address;
}

inline void NotificationServer::wait() {
	std::unique_lock<std::mutex> lock(m_monitor);
	m_condition.wait(lock, [this](){ return !m_wating.test_and_set(); });
}

inline bool NotificationServer::timedWait(const std::chrono::milliseconds& _timeout) {
	std::unique_lock<std::mutex> lock(m_monitor);
	m_condition.wait_for(lock, _timeout, [this](){ return !m_wating.test_and_set(); });
}

inline void NotificationServer::clear() {
	m_wating.test_and_set();
}


NotificationServer::~NotificationServer() {}

inline void NotificationServer::notify() {
	m_wating.clear();
	m_condition.notify_one();
}

} /* namespace nls */

#endif /* NOTIFICATION_SERVER_HPP_ */
