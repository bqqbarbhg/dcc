#ifndef _DCC_SETTINGS_H
#define _DCC_SETTINGS_H

#include <string>
#include <unordered_map>
#include <iostream>

namespace dcc {

class SettingBase
{
	virtual void set_init() = 0;
	virtual void set_std() = 0;
	virtual void set_value(std::istream& i) = 0;
};

template <typename T>
class Setting : public SettingBase
{
public:
	Setting(const char* flag, T init, T std)
		: init(init), std(std), val(init)
	{
		Settings::setting_map[flag] = this;
	}

	virtual void set_init() { val = init; }
	virtual void set_std() { val = std; }
	virtual void set_value(std::istream& i) { i >> val; }

	operator T() const { return val; }
	Setting<T> &operator=(const T& t) { val = t; return *this; }

	T val, init, std;
};

class Settings
{
public:
	Settings()
		: trigraph("trigraph", false, true)
		, unicode("unicode", false, false)
	{
	}

	static std::unordered_map<std::string, SettingBase*> setting_map;

	// Replace trigraph sequences ($2.2.1.1)
	Setting<bool> trigraph;

	// Support UTF-8 identifiers
	Setting<bool> unicode;
};
extern Settings settings;

}

#endif