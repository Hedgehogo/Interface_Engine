#pragma once

#include "../../Positioning2/Positioning2.hpp"
#include "IE/modules/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ie {
	bool determinePositioning2(const YAML::Node& node, std::string& type);
}