#pragma once

#include "../../Positioning2/Positioning2.hpp"
#include "IE/modules/yaml-cpp/yaml-builder/yaml-builder.hpp"

namespace ie {
	bool determine_positioning2(const YAML::Node& node, std::string& type);
}