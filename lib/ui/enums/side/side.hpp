#pragma once
#include "../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	enum class Side {
		up,
		down,
		right,
		left
	};
	
	template<>
	bool convert(const YAML::Node &node, Side &side);
	
	Side createSideFromYaml(const YAML::Node &node);
}
