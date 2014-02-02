#ifndef GLOBAL_CONFIG_HPP_
#define GLOBAL_CONFIG_HPP_

#include <boost/property_tree/ptree.hpp>
#include <map>
#include "utils/config_interface.hpp"

class GlobalConfig : public ConfigInterface {
public:
	GlobalConfig(const std::string &_path);
	virtual ~GlobalConfig();

	virtual int getInt(const std::string &_name);
	virtual std::string getStr(const std::string &_name);

	static inline const char *defaultIniPath();

private:
	boost::property_tree::ptree m_config;
	std::map<std::string, int> m_defaultInt;
	std::map<std::string, std::string> m_defaultStr;
};

inline const char *defaultIniPath() {
	return "/etc/nls.ini";
}

#endif /* GLOBAL_CONFIG_HPP_ */
