#pragma once

#include "../../../../Modules/yaml-cpp/yaml.hpp"

namespace ie {
	bool determinePositioning(const YAML::Node& node, std::string& type);
}
