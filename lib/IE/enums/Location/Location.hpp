#pragma once

#include "../../Modules/yaml-cpp/yaml.hpp"

namespace ie {
	enum class Location {
		Origin,
		Center,
		End
	};
	
	template<>
	struct Decode<Location> {
		static bool decode(const YAML::Node& node, Location& location);
	};
}
