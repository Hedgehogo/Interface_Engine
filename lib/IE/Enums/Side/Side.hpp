#pragma once

#include "../../Modules/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ie {
	enum class Side {
		up,
		down,
		right,
		left
	};
	
	template<>
	struct Decode<Side> {
		static bool decode(const YAML::Node& node, Side& side);
	};
}
