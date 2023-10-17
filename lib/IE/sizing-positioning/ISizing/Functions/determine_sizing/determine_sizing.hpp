#pragma once

#include "IE/modules/yaml-cpp/yaml.hpp"

namespace ie {
	bool determine_sizing(const YAML::Node& node, std::string& type);
}