#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <string>

struct lua_State;

class Configuration
{
public:
	Configuration(const std::string &file);
	~Configuration();
	bool getBoolean(const std::string &name) const;
	int getInteger(const std::string &name) const;
	double getReal(const std::string &name) const;
	std::string getString(const std::string &name) const;

private:
	Configuration(const Configuration &configuration);
	Configuration& operator=(const Configuration &configuration);
	lua_State *mState;
};

#endif
