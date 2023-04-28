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
	
	template<>
	struct Decode<Side> {
		static bool decode(const YAML::Node &node, Side &side);
	};
}
