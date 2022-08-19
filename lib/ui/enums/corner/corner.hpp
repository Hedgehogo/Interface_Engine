#pragma once
#include "../../../yaml/yamlWithSfml/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	enum class Corner {
		upRight,
		upLeft,
		downRight,
		downLeft
	};
	
	Corner createCornerFromYaml(const YAML::Node &node);
}
