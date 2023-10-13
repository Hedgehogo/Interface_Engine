#pragma once

#include "IE/modules/yaml-cpp/yaml.hpp"

namespace ie {
	bool determineSizing(const YAML::Node& node, std::string& type);
}