#pragma once
#include "../location/location.hpp"

namespace ui {
	enum class Location2 {
		  upLeft,     up,   upRight,
		    left, center,     right,
		downLeft,   down, downRight
	};
	
	Location getVerticalLocation(Location2 location2);
	
	Location getHorizontalLocation(Location2 location2);
	
	Location2 makeLocation2(Location vertical, Location horizontal);
	
	
	
	template<>
	struct Decode<Location2> {
		static bool decode(const YAML::Node &node, Location2 &location2);
	};
}
