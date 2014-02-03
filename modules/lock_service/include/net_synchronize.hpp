#ifndef NET_SYNCHRONIZE_HPP_
#define NET_SYNCHRONIZE_HPP_

#include <boost/asio.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <ctime>
#include <boost/shared_ptr.hpp>

namespace LockService {

class NetSynchronize {
public:
	NetSynchronize();
	~NetSynchronize();

	boost::asio::ip::tcp::endpoint getEndpoint() const;
	void wait();
	bool timedWait(time_t _timeout);
	static void notify(const boost::asio::ip::tcp::endpoint &_endpoint);

private:
	void run();
	void startAccept();
	void handleAccept(
		const boost::system::error_code &_err,
		boost::shared_ptr<boost::asio::ip::tcp::socket> _socket);

	bool m_waked;
	boost::asio::io_service m_ioService;
	boost::asio::ip::tcp::acceptor m_acceptor;
	boost::thread_group m_threads;
	boost::mutex m_monitor;
	boost::condition_variable m_cond;
};

} /* namespace LockService */

#endif /* NET_SYNCHRONIZE_HPP_ */
