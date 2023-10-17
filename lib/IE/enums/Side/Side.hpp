#pragma once

#include "IE/modules/yaml-cpp/yaml-builder/yaml-builder.hpp"

namespace ie {
	enum class Side {
		Up,
		Down,
		Right,
		Left
	};
	
	template<>
	struct Decode<Side> {
		static bool decode(const YAML::Node& node, Side& side);
	};
}