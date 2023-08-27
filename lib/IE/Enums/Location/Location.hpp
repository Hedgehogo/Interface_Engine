#pragma once

#include "../../Modules/yaml-cpp/yaml.hpp"

namespace ie {
	enum class Location {
		origin,
		center,
		end
	};
	
	template<>
	struct Decode<Location> {
		static bool decode(const YAML::Node& node, Location& location);
	};
}
