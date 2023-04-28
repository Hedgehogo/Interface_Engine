#pragma once
#include "../../../modules/appendix/yaml-cpp/yaml.hpp"

namespace ui {
	enum class Corner {
		upRight,
		upLeft,
		downRight,
		downLeft
	};
	
	
	
	template<>
	struct Decode<Corner> {
		static bool decode(const YAML::Node &node, Corner &corner);
	};
}
