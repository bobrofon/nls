#ifndef CLIENT_INFO_HPP_
#define CLIENT_INFO_HPP_

#include <boost/asio/ip/tcp.hpp>

namespace LockLib {
namespace LockLogic {

typedef unsigned int client_id_t;
typedef boost::asio::ip::tcp::endpoint endpoint_t;

class ClientInfo {
public:
	ClientInfo(const client_id_t _clientId, const client_id_t _clientEId, const endpoint_t &_endpoint);
	ClientInfo(const client_id_t _clientId, const endpoint_t &_endpoint);
	ClientInfo(const ClientInfo &_src);
	ClientInfo &operator=(const ClientInfo &_src);
	~ClientInfo();

	inline client_id_t getId() const;
	inline client_id_t getEId() const;
	inline endpoint_t getEndpoint() const;

	inline void setEId(const client_id_t _eid);
	inline void setEndpoint(const endpoint_t &_endpoint);

private:
	client_id_t clientId;  // real id
	client_id_t clientEId; // effective id
	endpoint_t endpoint;
};

} /* namespace LockLogic */
} /* namespace LockLib */

namespace LockLib {
namespace LockLogic {

ClientInfo::ClientInfo(const client_id_t _clientId, const client_id_t _clientEId, const endpoint_t &_endpoint)
	: clientId(_clientId), clientEId(_clientEId), endpoint(_endpoint) {}

ClientInfo::ClientInfo(const client_id_t _clientId, const endpoint_t &_endpoint)
	: clientId(_clientId), clientEId(_clientId), endpoint(_endpoint) {}

ClientInfo::ClientInfo(const ClientInfo &_src)
	: clientId(_src.clientId), clientEId(_src.clientEId), endpoint(_src.endpoint) {}

ClientInfo &ClientInfo::operator=(const ClientInfo &_src) {
	clientId = _src.clientId;
	clientEId = _src.clientEId;
	endpoint = _src.endpoint;

	return *this;
}

ClientInfo::~ClientInfo() {}

inline client_id_t ClientInfo::getId() const {
	return clientId;
}

inline client_id_t ClientInfo::getEId() const {
	return clientEId;
}

inline endpoint_t ClientInfo::getEndpoint() const {
	return endpoint;
}

inline void ClientInfo::setEId(const client_id_t _eid) {
	clientEId = _eid;
}

inline void ClientInfo::setEndpoint(const endpoint_t &_endpoint) {
	endpoint = _endpoint;
}

} /* namespace LockLogic */
} /* namespace LockLib */

#endif /* CLIENT_INFO_HPP_ */
