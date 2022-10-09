#pragma once
#include "../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	enum class Corner {
		upRight,
		upLeft,
		downRight,
		downLeft
	};
	
	template<>
	bool convert(const YAML::Node &node, Corner &corner);
}
