#pragma once

#include "../Location/Location.hpp"

namespace ie {
	enum class Location2 {
		UpLeft, Up, UpRight,
		Left, Center, Right,
		DownLeft, Down, DownRight
	};
	
	Location getVerticalLocation(Location2 location2);
	
	Location getHorizontalLocation(Location2 location2);
	
	Location2 makeLocation2(Location vertical, Location horizontal);
	
	template<>
	struct Decode<Location2> {
		static bool decode(const YAML::Node& node, Location2& location2);
	};
}
