#pragma once

#include "../../../../../modules/appendix/yaml-cpp/yaml.hpp"

namespace ui {
	bool determineSizing(const YAML::Node& node, std::string& type);
}
