#pragma once

#include "../../../../Modules/yaml-cpp/yaml.hpp"

namespace ui {
	bool determineSizing(const YAML::Node& node, std::string& type);
}
