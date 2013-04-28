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

	T val, init, std;
};

class Settings
{
public:
	Settings()
		: trigraph("trigraph", false, true)
	{
	}

	static std::unordered_map<std::string, SettingBase*> setting_map;
	Setting<bool> trigraph;
};
extern Settings settings;

}

#endif