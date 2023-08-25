#pragma once

#include "../../../modules/appendix/yaml-cpp/yaml.hpp"

namespace ui {
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