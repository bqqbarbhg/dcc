#include "settings.h"

namespace dcc {

std::unordered_map<std::string, SettingBase*> Settings::setting_map;

Settings settings;

}