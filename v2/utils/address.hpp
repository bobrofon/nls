#ifndef ADDRESS_HPP_
#define ADDRESS_HPP_

#include <string>

namespace nls {

typedef unsigned short port_t;

class Address {
public:
	inline Address(const std::string& _host, const port_t& _port);
	inline Address() = default;

	inline std::string host() const noexcept;
	inline void host(const std::string& _host) noexcept;
	inline void host(std::string&& _host) noexcept;

	inline port_t port() const noexcept;
	inline void port(const port_t& _port) noexcept;
	inline void port(port_t&& _port) noexcept;

private:
	std::string m_host;
	port_t m_port;
};

} /* namespace nls */

////////////////////////////////////////////////////////////////////////////////////////////////////

namespace nls {

inline Address::Address(const std::string& _host, const port_t& _port) : m_host(_host), m_port(_port) {}

inline std::string Address::host() const noexcept {
	return m_host;
}

inline void Address::host(const std::string& _host) noexcept {
	m_host = _host;
}

inline void Address::host(std::string&& _host) noexcept {
	m_host = _host;
}

inline port_t Address::port() const noexcept {
	return m_port;
}

inline void Address::port(const port_t& _port) noexcept {
	m_port = _port;
}

inline void Address::port(port_t&& _port) noexcept {
	m_port = _port;
}

} /* namespace nls */

#endif /* ADDRESS_HPP_ */
