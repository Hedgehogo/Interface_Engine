#pragma once

#include "IE/modules/yaml-cpp/yaml.hpp"

namespace ie {
	bool determinePositioning(const YAML::Node& node, std::string& type);
}