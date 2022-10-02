#pragma once
#include "../../../yaml/yamlWithSfml/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	enum class Corner {
		upRight,
		upLeft,
		downRight,
		downLeft
	};
	
	template<>
	bool convert(const YAML::Node &node, Corner &corner);
	
	Corner createCornerFromYaml(const YAML::Node &node);
}
