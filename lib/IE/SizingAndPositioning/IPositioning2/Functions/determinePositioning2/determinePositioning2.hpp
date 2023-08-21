#pragma once

#include "../../Positioning2/Positioning2.hpp"
#include "../../../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	bool determinePositioning2(const YAML::Node& node, std::string& type);
}
