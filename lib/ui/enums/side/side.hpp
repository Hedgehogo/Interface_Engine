#pragma once
#include "../../../yaml/yamlWithSfml/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	enum class Side {
		up,
		down,
		right,
		left
	};
	
	Side createSideFromYaml(const YAML::Node &node);
}
