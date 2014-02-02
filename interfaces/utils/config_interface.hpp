#ifndef CONFIG_INTERFACE_HPP_
#define CONFIG_INTERFACE_HPP_

#include <string>

class ConfigInterface {
public:
	virtual ~ConfigInterface() {}

	virtual int getInt(const std::string &_name) = 0;
	virtual std::string getStr(const std::string &_name) = 0;
};

ConfigInterface *Config();

#endif /* CONFIG_INTERFACE_HPP_ */
