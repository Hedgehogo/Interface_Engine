#pragma once

#include "IE/modules/yaml-cpp/yaml.hpp"

namespace ie {
	enum class Side {
		Up,
		Down,
		Right,
		Left
	};
	
	/*old_yaml_decode
	template<>
	struct Decode<Side> {
		static bool decode(const YAML::Node& node, Side& side);
	};
	*/
}