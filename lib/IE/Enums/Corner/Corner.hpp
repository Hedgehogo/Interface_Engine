#pragma once

#include "../../Modules/yaml-cpp/yaml.hpp"

namespace ie {
	enum class Corner {
		UpRight,
		UpLeft,
		DownRight,
		DownLeft
	};
	
	template<>
	struct Decode<Corner> {
		static bool decode(const YAML::Node& node, Corner& corner);
	};
}
