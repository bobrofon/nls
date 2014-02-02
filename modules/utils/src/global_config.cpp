#include "global_config.hpp"
#include <boost/filesystem.hpp>
#include <boost/property_tree/ini_parser.hpp>

GlobalConfig::GlobalConfig(const std::string &_path) {
	if (boost::filesystem::exists(_path)) {
		boost::property_tree::ini_parser::read_ini(_path, m_config);
	}
}

GlobalConfig::~GlobalConfig() {}

int GlobalConfig::getInt(const std::string &_name) {
	return m_config.get<int>(_name, m_defaultInt[_name]);
}

std::string GlobalConfig::getStr(const std::string &_name) {
	return m_config.get<std::string>(_name, m_defaultStr[_name]);
}

ConfigInterface *Config() {
	static ConfigInterface *config = new GlobalConfig(defaultIniPath());

	return config;
}
