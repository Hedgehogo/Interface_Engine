#pragma once

#include "../../Positioning2/Positioning2.hpp"
#include "../../../../Modules/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ie {
	bool determinePositioning2(const YAML::Node& node, std::string& type);
}
