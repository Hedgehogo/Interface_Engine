#pragma once

#include "../../../../Modules/yaml-cpp/yaml.hpp"

namespace ui {
	bool determinePositioning(const YAML::Node& node, std::string& type);
}
