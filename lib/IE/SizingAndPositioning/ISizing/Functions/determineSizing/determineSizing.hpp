#pragma once

#include "../../../../Modules/yaml-cpp/yaml.hpp"

namespace ie {
	bool determineSizing(const YAML::Node& node, std::string& type);
}
