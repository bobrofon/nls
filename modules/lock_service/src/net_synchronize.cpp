#include "net_synchronize.hpp"
#include <boost/bind.hpp>
#include <utils/config_interface.hpp>
#include "utils/debug.hpp"

using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;

namespace LockService {

NetSynchronize::NetSynchronize() : m_waked(false), m_ioService(), m_acceptor(m_ioService) {
	tcp::endpoint endpoint;
	endpoint.address(address::from_string(Config()->getStr("client.address")));
	endpoint.port(0);

	m_acceptor.open(endpoint.protocol());
	m_acceptor.set_option(tcp::acceptor::reuse_address(true));
	m_acceptor.bind(endpoint);
	m_acceptor.listen();

	m_threads.create_thread(bind(&NetSynchronize::run, this));
}

NetSynchronize::~NetSynchronize() {
	m_ioService.stop();
	m_threads.join_all();
}

boost::asio::ip::tcp::endpoint NetSynchronize::getEndpoint() const {
	return m_acceptor.local_endpoint();
}

void NetSynchronize::wait() {
	NLS_ASSERT(!m_ioService.stopped());

	mutex::scoped_lock lock(m_monitor);

	while (!m_waked) {
		m_cond.wait(lock);
	}

	m_waked = false;
}

bool NetSynchronize::timedWait(time_t /*_timeout*/) {
	return false;
}

void NetSynchronize::notify(const boost::asio::ip::tcp::endpoint &_endpoint) {
	io_service ioService;
	tcp::socket socket(ioService);
	socket.connect(_endpoint);
	socket.close();
}

void NetSynchronize::run() {
	startAccept();
	m_ioService.run();
}

void NetSynchronize::startAccept() {
	shared_ptr<tcp::socket> socket(new tcp::socket(m_acceptor.get_io_service()));
	m_acceptor.async_accept(*socket, bind(&NetSynchronize::handleAccept, this, placeholders::error, socket));
}

void NetSynchronize::handleAccept(const system::error_code &/*_err*/, shared_ptr<tcp::socket> _socket) {
	_socket->close();

	if (m_ioService.stopped()) {
		return ;
	}
	{
		mutex::scoped_lock lock(m_monitor);
		m_waked = true;
		m_cond.notify_all();
	}

	startAccept();
}

} /* namespace LockService */
