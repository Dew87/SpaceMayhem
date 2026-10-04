#include "Configuration.hpp"
#include "lua.hpp"
#include <iostream>

using namespace std;

Configuration::Configuration(const string &file) : mState(luaL_newstate())
{
	if (0 == mState)
	{
		cerr << "Could not create lua state" << endl;
	}
	if (0 != luaL_dofile(mState, file.c_str()))
	{
		cerr << lua_tostring(mState, lua_gettop(mState)) << endl;
	}
}

Configuration::~Configuration()
{
	lua_close(mState);
}

bool Configuration::getBoolean(const string &name) const
{
	bool boolean = false;
	lua_getglobal(mState, name.c_str());
	if (lua_isboolean(mState, lua_gettop(mState)))
	{
		boolean = (bool)lua_toboolean(mState, lua_gettop(mState));
	}
	else
	{
		cerr << name << " is not a valid boolean variable" << endl;
	}
	lua_pop(mState, 1);
	return boolean;
}

int Configuration::getInteger(const string &name) const
{
	int integer = 0;
	lua_getglobal(mState, name.c_str());
	if (lua_isnumber(mState, lua_gettop(mState)))
	{
		integer = (int)lua_tonumber(mState, lua_gettop(mState));
	}
	else
	{
		cerr << name << " is not a valid integer variable" << endl;
	}
	lua_pop(mState, 1);
	return integer;
}

double Configuration::getReal(const string &name) const
{
	double real = 0.0;
	lua_getglobal(mState, name.c_str());
	if (lua_isnumber(mState, lua_gettop(mState)))
	{
		real = (double)lua_tonumber(mState, lua_gettop(mState));
	}
	else
	{
		cerr << name << " is not a valid real variable" << endl;
	}
	lua_pop(mState, 1);
	return real;
}

string Configuration::getString(const string &name) const
{
	std::string string = "";
	lua_getglobal(mState, name.c_str());
	if (lua_isstring(mState, lua_gettop(mState)))
	{
		string = lua_tostring(mState, lua_gettop(mState));
	}
	else
	{
		cerr << name << " is not a valid string variable" << endl;
	}
	lua_pop(mState, 1);
	return string;
}
